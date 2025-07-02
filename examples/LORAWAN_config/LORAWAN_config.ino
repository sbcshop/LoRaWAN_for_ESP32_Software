#define RAK_SERIAL Serial1
#define RAK_BAUD   115200

#define RAK_TX 17  // ESP32 TX -> RAK3172 RX
#define RAK_RX 18  // ESP32 RX <- RAK3172 TX

#define LPWAN_RST 4
#define LPWAN_BOOT 6

String DEVEUI_ = "";
String APPEUI_ = "";
String APPKEY_ = "";

void module_reset() {
  pinMode(LPWAN_RST, OUTPUT);
  digitalWrite(LPWAN_RST, HIGH);
  delay(200);
  digitalWrite(LPWAN_RST, LOW);
  delay(200);
  digitalWrite(LPWAN_RST, HIGH);
  Serial.println("Module Reset Done!");
  delay(1000);
}

void module_boot() {
  pinMode(LPWAN_BOOT, OUTPUT);
  digitalWrite(LPWAN_BOOT, LOW); // Normal boot
  delay(200);
}

void send_command(const char* command) {
  RAK_SERIAL.print(command);
  RAK_SERIAL.print("\r\n");
  delay(200);
}

void module_response_check() {
  while (RAK_SERIAL.available()) {
    String response = RAK_SERIAL.readStringUntil('\n');
    response.trim();
    if (response.length() > 0) {
      Serial.println("Module Response: " + response);

      if (response.startsWith("AT+DEVEUI=")) {
        DEVEUI_ = response.substring(response.indexOf('=') + 1);
      } else if (response.startsWith("AT+APPEUI=")) {
        APPEUI_ = response.substring(response.indexOf('=') + 1);
      } else if (response.startsWith("AT+APPKEY=")) {
        APPKEY_ = response.substring(response.indexOf('=') + 1);
      }
    }
  }
}

void get_IDkey() {
  send_command("AT+DEVEUI=?");
  delay(100);
  module_response_check();

  send_command("AT+APPEUI=?");
  delay(100);
  module_response_check();

  send_command("AT+APPKEY=?");
  delay(100);
  module_response_check();

  Serial.println("\n========== LoRaWAN Node Credentials ==========");
  Serial.println("DEVEUI  : " + DEVEUI_);
  Serial.println("APPEUI  : " + APPEUI_);
  Serial.println("APPKEY  : " + APPKEY_);
  Serial.println("==============================================");
}

void set_IDkey(const String& deveui, const String& appeui, const String& appkey) {
  send_command(("AT+DEVEUI=" + deveui).c_str());
  delay(200);

  send_command(("AT+APPEUI=" + appeui).c_str());
  delay(200);

  send_command(("AT+APPKEY=" + appkey).c_str());
  delay(200);
}

void setup() {
  Serial.begin(115200);
  RAK_SERIAL.begin(RAK_BAUD, SERIAL_8N1, RAK_RX, RAK_TX);

  module_reset();
  module_boot();

  send_command("AT");
  delay(200);
  module_response_check();

  send_command("AT+NWM=1");  // LoRaWAN mode
  delay(200);
  module_response_check();

  get_IDkey();
  
  // Uncomment to set new credentials
  /*
  String new_deveui = "AC1F09FFFE1238CA";
  String new_appeui = "AC1F09FFF9153172";
  String new_appkey = "AC1F09FFFE1238CAAC1F09FFF9153172";
  set_IDkey(new_deveui, new_appeui, new_appkey);

  get_IDkey(); // Verify
  */
  
}

void loop() {
  // Do nothing
}
