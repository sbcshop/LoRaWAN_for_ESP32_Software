/* Simple Data Send on TTN Server

To Register Setup and Register Gateway on TTN Server :
https://github.com/sbcshop/LoRaWAN_Gateway_HAT_Software

To create application & register endnode on TTN Server checkout instructions:
https://github.com/sbcshop/LoRaWAN_Breakout_Software/tree/main/lorawan_application_TTN

To get/set LoRaWAN Endnode credentials using code => 
https://github.com/sbcshop/LoRaWAN_for_ESP32_Software/tree/main/examples/LORAWAN_config 
*/

// UART config for RAK3172
#define RAK_SERIAL Serial1
#define RAK_BAUD   115200
#define RAK_RX     18
#define RAK_TX     17

// RAK3172 control pins
#define LPWAN_BOOTBTN 6
#define LPWAN_RSTBTN  4

bool isJoined = false;

// ------------------------
// RAK3172 Reset
// ------------------------
void module_reset() {
  digitalWrite(LPWAN_RSTBTN, HIGH);
  delay(200);
  digitalWrite(LPWAN_RSTBTN, LOW);
  delay(200);
  digitalWrite(LPWAN_RSTBTN, HIGH);
  delay(500);
  Serial.println("Module Reset Done.");
}

void module_boot(bool enableBootMode) {
  digitalWrite(LPWAN_BOOTBTN, enableBootMode ? HIGH : LOW);
  Serial.println(enableBootMode ? "Boot Mode ENABLED" : "Boot Mode DISABLED");
}

void sendATCommand(const char *command, uint16_t wait = 300, bool verbose = true) {
  RAK_SERIAL.println(command);
  delay(wait);

  if (verbose) {
    Serial.print(">> ");
    Serial.println(command);
    while (RAK_SERIAL.available()) {
      Serial.write(RAK_SERIAL.read());
    }
    Serial.println("----------------------");
  }
}

bool checkJoinStatus(uint32_t timeout = 5000) {
  sendATCommand("AT+NJS=?", 300, false);
  uint32_t startTime = millis();
  String resp = "";

  while (millis() - startTime < timeout) {
    while (RAK_SERIAL.available()) {
      char c = RAK_SERIAL.read();
      resp += c;
    }

    if (resp.indexOf("AT+NJS=1") >= 0 || resp.indexOf("+EVT:JOINED") >= 0) {
      Serial.println("Already connected to network!");
      return true;
    }

    delay(200);
  }

  Serial.println("Join status: NOT JOINED");
  return false;
}

void joinNetwork() {
  Serial.println("Trying to Join Network...");
  sendATCommand("AT+JOIN=1:0:10:8");
  delay(1000);

  uint32_t attemptStart = millis();
  while (millis() - attemptStart < 20000) {
    String resp = "";
    while (RAK_SERIAL.available()) {
      char c = RAK_SERIAL.read();
      resp += c;
    }

    if (resp.indexOf("+EVT:JOINED") >= 0 || resp.indexOf("AT+NJS=1") >= 0) {
      Serial.println("Connected to Network!");
      isJoined = true;
      return;
    }

    delay(500);
  }

  Serial.println("Join Failed. Restarting...");
  while (1);  // halt
}

void sendData(int port, const String &data) {
  String payload = data;
  if (payload.length() % 2 != 0) payload = "0" + payload; // must be even

  String cmd = "AT+SEND=" + String(port) + ":" + payload;
  if (isJoined) {
    sendATCommand(cmd.c_str(), 300);
    Serial.println("Data Sent: " + payload);
  } else {
    Serial.println("Not connected. Cannot send.");
  }
}

// ------------------------
// Setup
// ------------------------
void setup() {
  pinMode(LPWAN_RSTBTN, OUTPUT);
  pinMode(LPWAN_BOOTBTN, OUTPUT);

  Serial.begin(115200);
  RAK_SERIAL.begin(RAK_BAUD, SERIAL_8N1, RAK_RX, RAK_TX);

  module_boot(false);
  delay(500);
  //module_reset(); // required only once if having rak3172 module response issue or connection issue with server

  sendATCommand("AT");
  sendATCommand("AT+NWM=1"); // LoRaWAN Mode
  delay(500);

  isJoined = checkJoinStatus();
  if (!isJoined) {
    joinNetwork();
  }
}

// ------------------------
// Loop
// ------------------------
void loop() {
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 20000) {
    lastSend = millis();
    sendData(1, "34");  // Replace with actual payload
  }

  delay(100);
}
