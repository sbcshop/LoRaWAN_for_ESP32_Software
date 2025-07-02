#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// UART for RAK3172
#define RAK_SERIAL Serial1
#define RAK_BAUD   115200
#define RAK_RX     18
#define RAK_TX     17

// RAK3172 control
#define LPWAN_BOOTBTN 6
#define LPWAN_RSTBTN  4

// ST7789 Display Pins
#define TFT_CS     10
#define TFT_RST    14
#define TFT_DC     13
#define TFT_MOSI   11
#define TFT_SCLK   12
#define BACK_LIGHT 5

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

unsigned long lastDisplayUpdate = 0;

// ------------------------
// Setup RAK3172
// ------------------------
void module_reset() {
  Serial.println("Resetting RAK3172...");
  digitalWrite(LPWAN_RSTBTN, HIGH);
  delay(200);
  digitalWrite(LPWAN_RSTBTN, LOW);
  delay(200);
  digitalWrite(LPWAN_RSTBTN, HIGH);
  delay(100);
  Serial.println("Reset Done.");
}

void module_boot(bool enableBootMode) {
  digitalWrite(LPWAN_BOOTBTN, enableBootMode ? HIGH : LOW);
  Serial.print("Boot Mode: ");
  Serial.println(enableBootMode ? "ENABLED" : "DISABLED");
}

void sendATCommand(const char *command, uint16_t waitTime = 300) {
  Serial.print("Sending: ");
  Serial.println(command);
  RAK_SERIAL.println(command);
  delay(waitTime);

  while (RAK_SERIAL.available()) {
    char c = RAK_SERIAL.read();
    Serial.write(c);
  }

  Serial.println("\n----------------------");
}

// ------------------------
// Display Functions
// ------------------------
void displayMessage(const String& data, const String& rssi) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 30);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.print("Data: ");
  tft.println(data);
  tft.setCursor(10, 70);
  tft.setTextColor(ST77XX_GREEN);
  tft.print("RSSI: ");
  tft.print(rssi);
  tft.println(" dBm");
}

// ------------------------
// Setup
// ------------------------
void setup() {
  pinMode(LPWAN_RSTBTN, OUTPUT);
  pinMode(LPWAN_BOOTBTN, OUTPUT);
  pinMode(BACK_LIGHT, OUTPUT);
  digitalWrite(BACK_LIGHT, HIGH);

  module_boot(false); // normal mode

  Serial.begin(115200);
  RAK_SERIAL.begin(RAK_BAUD, SERIAL_8N1, RAK_RX, RAK_TX);

  tft.init(135, 240);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 50);
  tft.setTextColor(ST77XX_YELLOW);
  tft.println("P2P RX Ready");

  delay(500);
  module_reset();
  delay(500);

  sendATCommand("AT");
  sendATCommand("AT+NWM=0");
  sendATCommand("AT+PRECV=65535"); // Continuous Rx until packet received
}

// ------------------------
// Loop
// ------------------------
void loop() {
  static String buffer = "";

  while (RAK_SERIAL.available()) {
    char c = RAK_SERIAL.read();
    buffer += c;
    if (c == '\n') {
      buffer.trim();

      // Debug
      Serial.println("Recv: " + buffer);

      // Check for +EVT:RXP2P
      if (buffer.startsWith("+EVT:RXP2P")) {
        // Example: +EVT:RXP2P:-80:12:1234
        int first = buffer.indexOf(':');
        int second = buffer.indexOf(':', first + 1);
        int third = buffer.indexOf(':', second + 1);

        String rssi = buffer.substring(second + 1, third);
        String data = buffer.substring(third + 4);

        displayMessage(data, rssi);

        delay(1000); // Wait before enabling RX again
        sendATCommand("AT+PRECV=65535", 500);
      }

      buffer = ""; // clear for next line
    }
  }

  // Update screen with prompt every 5s
  if (millis() - lastDisplayUpdate > 5000) {
    lastDisplayUpdate = millis();
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(20, 40);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.println("Waiting..!");
  }
}
