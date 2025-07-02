#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// UART config for RAK3172
#define RAK_SERIAL Serial1
#define RAK_BAUD   115200
#define RAK_RX     18
#define RAK_TX     17

// RAK3172 control pins
#define LPWAN_BOOTBTN 6
#define LPWAN_RSTBTN  4

// ST7789 Display pins
#define TFT_CS    10
#define TFT_RST   14
#define TFT_DC    13
#define TFT_MOSI  11
#define TFT_SCLK  12
#define BACK_LIGHT 5

// User Boot Button
#define BOOT_BTN 0

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


unsigned long lastDisplayUpdate = 0;

// ----------------------------------------------
// Send AT Command to RAK3172 and show response  |
// ----------------------------------------------
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

// -------------------------------------
// RAK Module Reset       
// -------------------------------------
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

// -------------------------------------
// Setup
// -------------------------------------
void setup() {
  pinMode(LPWAN_RSTBTN, OUTPUT);
  pinMode(LPWAN_BOOTBTN, OUTPUT);
  digitalWrite(LPWAN_BOOTBTN, LOW);

  pinMode(BACK_LIGHT, OUTPUT);
  digitalWrite(BACK_LIGHT, HIGH);

  pinMode(BOOT_BTN, INPUT_PULLUP);

  Serial.begin(115200);
  RAK_SERIAL.begin(RAK_BAUD, SERIAL_8N1, RAK_RX, RAK_TX);

  tft.init(135, 240);
  tft.setRotation(3);
  tft.setTextWrap(false);
  tft.setTextSize(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setCursor(10, 50);
  tft.setTextSize(3);
  tft.print("P2P Transmit");

  tft.setCursor(80, 90);
  tft.setTextSize(2);
  tft.print("Demo");
  delay(1000);

  module_reset();

  // Initial Configuration
  sendATCommand("AT");
  sendATCommand("AT+NWM=0");                           // Set to P2P mode
  sendATCommand("AT+PRECV=0");                         // Cancel any RX
  sendATCommand("AT+P2P=903000000:7:0:0:14:5");        // Set P2P params
}

// -------------------------------------
// Loop
// -------------------------------------
void loop() {
  // Check boot button press
  if (digitalRead(BOOT_BTN) == LOW ) {
    Serial.println("Boot Button Pressed");
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10, 30);
    tft.setTextColor(ST77XX_YELLOW);
    tft.setTextSize(2);
    tft.println("Sending Data...");
    sendATCommand("AT+PSEND=5678");     // random payload send 

    tft.setCursor(10, 70);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(2);
    tft.println("Sent: 5678");
  }

  // Update screen with prompt every 5s
  if (millis() - lastDisplayUpdate > 5000) {
    lastDisplayUpdate = millis();
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(20, 40);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.println("Press BOOT to Tx");
  }

  delay(10);
}
