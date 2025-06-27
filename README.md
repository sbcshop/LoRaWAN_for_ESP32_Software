# LoRaWAN_for_ESP32_Software
<!--
<img src="https://github.com/sbcshop/LoRaWAN_Breakout_Software/blob/main/images/feature_banner.png" width="" height="">
-->

Powered by ESP32 S3 Wroom-1 microcontroller in conjunction with the RAK3172 module, offers a convenient and versatile solution for accelerating your IoT development projects with LoRaWAN networks. You can easily switch onboard module into **LoRaWAN Mode** for connecting with server platforms like The Things Network (TTN), Chirpstack, Actility, etc. or **P2P Mode** to implement your own customized long-range LoRa network quickly. Module complies with Classes A, B, and C of the LoRaWAN 1.0.3 specifications.

This github offers getting started instructions to work with LoRaWAN for ESP32 development board.

### **_Features:_**
- Powered by ESP32-S3 Wroom-1 microcontroller 
- The board is equipped with a RAK3172 Module supporting LoRaWAN protocol for IoT-based applications 
- Multiple wireless technologies on single board Wi-Fi, BLE, and LoRaWAN 
- 1.14” TFT display for visual interactions with a resolution of 240x135 pixels
- Type C interface for programming and powering board
- Header Selection for standalone access to LPWAN Module for configuring and setup
- Boot and reset buttons for ESP32 programming purposes
- Onboard Battery connector and charge management for portable use 
- Power and Charging status LED indicator
- ESP32 GPIOs breakout for additional hardware interfacing 
- Breadboard compatible board and easy programming using Arduino IDE 

### Specifications:
- **Microcontroller**  : ESP32-S3 series of SoCs having Xtensa® dual-core 32-bit LX7 microprocessor
- **LoRaWAN Module** : RAK3172
- **Wireless Connectivity** : 2.4 GHz Wi-Fi (802.11 b/g/n), Bluetooth® 5 (LE), LoRa
- **Memory** : Flash up to 16 MB, PSRAM up to 8 MB
- **Working mode** : Support STA/AP/STA+AP 
- **Supply Voltage:** 5V
- **Operating Pin:** 3.3V ~ 5V
- **Display Size**: 1.14"
- **Display Resolution**: 135x240 pixel
- **Display Driver**: ST7789
- **Display Appearance**: RGB
- **Display Colors**: 65K/262K
- **Communication Interface:** SPI (UART), Type C
- **Antenna port:** 1 port ,SMA

**RAK3172 LoRaWAN Module Specifications:**
- RAK3172 is based on STM32WLE5CCU6 chip
- Complies with Class A, B, & C of LoRaWAN 1.0.3 specifications, ensuring interoperability and compliance with industry standards.
- Module Available with Supported bands: EU433, CN470, IN865, EU868, AU915, US915, KR920, RU864, and AS923-1/2/3/4
- LoRaWAN activation by OTAA/ABP
- LoRa Point-to-Point (P2P) communication to build your own LoRa Network
- Easy-to-use AT command set via UART interface
- Long-range - around 15 km* with optimized antenna

### 📑 Table of Contents
1. [Hardware Overview]()
    * [Pinout]()
    * [Interfacing Details]()
3. [Getting Started with LoRaWAN Breakout]()
    * [Configure and Setup Development Environment]()
    * [Installing Libraries]()
    * [Testing Code]()
    * [P2P Mode](https://github.com/sbcshop/LoRaWAN_Breakout_Software?tab=readme-ov-file#p2p-mode) 
    * [LoRaWAN Mode](https://github.com/sbcshop/LoRaWAN_Breakout_Software?tab=readme-ov-file#lorawan-mode)
 5. [Resources]()
 6. [Related Products]()

## Hardware Overview
### Pinout
<img src="" width="" height="">

### Interfacing Details

 - _**LoRaWAN RAK3172 Module with ESP32**_
   
   | ESP32 | RAK3172 Module | Description | 
   |---|---|---|
   | IO17/U1TXD | RX2 | Serial UART communication pin |
   | IO18/U1RXD | TX2 | Serial UART communication pin |
   | IO4        | Reset | RAK3172 Module Reset Pin  |
   | IO6        | Boot  | RAK3172 Module Boot Pin  |
   
- _**Display Interfacing with ESP32**_

   | ESP32 | Display | Function |
   |---|---|---|
   | IO12 | LCD_CLK | Clock pin of SPI interface for Display|
   | IO11 | LCD_DIN | MOSI (Master OUT Slave IN) pin of SPI interface|
   | IO10 | LCD_CS | Chip Select pin of SPI interface|
   | IO13 | LCD_DC| Data/Command (MISO) pin of SPI interface|
   | IO14 | LCD_RST | Display Reset pin |
   | IO5  | BL | Backlight of display|

- _**Breakout Pins**_
  
  Breakout 1
  | ESP32 | Type* | Multi-Function (_**Bold-Italic**_ default Function) |
  |---|---|---|
  |GND  | P     | Supply Ground |
  |3V3  | P     | Positive Supply, 3.3V |
  |5V   | P     | Positive Supply, 5V |
  |GP1  | I/O/T | RTC_GPIO1, _**GPIO1**_, TOUCH1, ADC1_CH0  |
  |GP2  | I/O/T | RTC_GPIO2, _**GPIO2**_, TOUCH2, ADC1_CH1  |
  |GP43/TXD0 | I/O/T | _**U0TXD**_ , GPIO43, CLK_OUT1 |
  |GP44/RXD0 | I/O/T | _**U0RXD**_ , GPIO44, CLK_OUT2  |
  |GP42 | I/O/T | _**MTMS**_ , GPIO42  |
  |GP41 | I/O/T | _**MTDI**_ , GPIO41, CLK_OUT1 |
  |GP40 | I/O/T | _**MTDO**_ , GPIO40, CLK_OUT2 |
  |GP39 | I/O/T | _**MTCK**_ , GPIO39, CLK_OUT3, SUBSPICS1 |
  |GP38 | I/O/T | _**GPIO38**_ , FSPIWP, SUBSPIWP  |
  |GP45 | I/O/T | _**GPIO45**_  |

  Breakout 2
  | ESP32 | Type* | Multi-Function (_**Bold-Italic**_ default Function) |
  |---|---|---|
  |GND  | P     | Supply Ground |
  |3V3  | P     | Positive Supply, 3.3V |
  |5V   | P     | Positive Supply, 5V |
  |EN   | I     | Enable pin, HIGH - Chip on, LOW - Chip off |
  |GP15 | I/O/T | RTC_GPIO15, _**GPIO15**_ , U0RTS, ADC2_CH4, XTAL_32K_P  |
  |GP16 | I/O/T | RTC_GPIO16, _**GPIO16**_ , U0CTS, ADC2_CH5, XTAL_32K_N |
  |GP8  | I/O/T | RTC_GPIO8, _**GPIO8**_ , TOUCH8, ADC1_CH7, SUBSPICS1  |
  |GP19 | I/O/T | RTC_GPIO19, GPIO19, U1RTS, ADC2_CH8, CLK_OUT2, _**USB_D-**_ |
  |GP20 | I/O/T | RTC_GPIO20, GPIO20, U1CTS, ADC2_CH9, CLK_OUT1, _**USB_D+**_ |
  |GP3  | I/O/T | RTC_GPIO3, **_GPIO3_**, TOUCH3, ADC1_CH2  |
  |GP46 | I/O/T | GPIO46 |
  |GP9  | I/O/T | RTC_GPIO9, _**GPIO9**_ , TOUCH9, ADC1_CH8, FSPIHD, SUBSPIHD |
  |GP21 | I/O/T | RTC_GPIO21, _**GPIO21**_ |

  *I-INPUT, O-OUTPUT, P-POWER & T-HIGH IMPEDENCE

## Getting Started with LoRaWAN for ESP32
### 1. Configure and Setup Development Environment
   - Download Arduino IDE from [official site](https://www.arduino.cc/en/software) and install into your system. We have use Arduino IDE 1.8.19
   - Once installation done will add ESP32 S3 board support into IDE, for this first you need to add below link into preference:
     
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
     Select File > Preference, and add link as show in below image,

     <img src= "https://github.com/sbcshop/3.2_Touchsy_ESP-32_Resistive_Software/blob/main/images/preference_board.gif" />
      
   - Now will install ESP32 based boards as shown in below image,

     <img src= "https://github.com/sbcshop/3.2_Touchsy_ESP-32_Resistive_Software/blob/main/images/install_ESP32boards.gif" />

   - Once done, keeping default settings select the ESP32S3 Dev Module with suitable COM PORT (may be different in your case) as shown below,

     <img src="https://github.com/sbcshop/3.2_Touchsy_ESP-32_Resistive_Software/blob/main/images/select_esp32_with_comport.gif">

     You can view assigned COM port through Device Manager,

     <img src="https://github.com/sbcshop/2x2_Display_ESP32_Software/blob/main/images/UART_com_port.jpg" width="582" height="421">   
     
        
### 2. Installing Libraries
   - When compiling sample codes there are some dependency on external libraries sometime which you can add as shown here.
   - For example installing library, for display select Sketch > Include Library > Manage Libraries. We need ST7789 (1.10.3 version) and GFX library (1.11.7 version) for 1.14" TFT Display,

     <img src= "https://github.com/sbcshop/EnkFi_7.5_Software/blob/main/images/Lib_install.png" />

     <img src= "https://github.com/sbcshop/Rainy_UHF_ESP32_Software/blob/main/images/st7789_lib.png" width="589" height="228" />
     <img src= "https://github.com/sbcshop/Rainy_UHF_ESP32_Software/blob/main/images/GFX_lib.png" width="588" height="217" />

   - Similarly you can add more libraries if needed, make sure to install correct version. 


### 3. Testing Code
   - At this step you are all set to test codes, for easy getting started we have provided various demo [example codes]() in github which you can download and try. 
   - Open one example code in Arduino and make sure you have selected correct board with suitable com port, click on upload button to transfer code on board.
     <img src="https://github.com/sbcshop/StackyFi_Software/blob/main/images/upload_code.gif">
   - Checkout other more examples [here]() and build your own custom program codes using those references.

## RAK3172 Module Standalone
* You can access RAK3172 module directly using USB-TTL device. For this remove jumper and make connection as shown below,
  
  <img src="" width="" height="">

* Now you can follow steps mentioned [here]() to use RAK3172 module standalone like breakout for changing configuration or [Firmware update]().
  

## Resources
  * [Schematic](https://github.com/sbcshop/LoRaWAN_for_ESP32_Hardware/blob/main/Design%20Data/LoRaWAN%20for%20ESP32%20SCH.PDF)
  * [Hardware Files](https://github.com/sbcshop/LoRaWAN_for_ESP32_Hardware)
  * [RAK3172 AT Command Reference ](https://docs.rakwireless.com/product-categories/software-apis-and-libraries/rui3/at-command-manual/)
  * [Arduino IDE 1 overview](https://docs.arduino.cc/software/ide-v1/tutorials/Environment)
    
## Related Products  

  * [LoRaWAN for Raspberry Pi Pico](https://shop.sb-components.co.uk/products/lorawan-for-raspberry-pi-pico)
  
  * [LoRaWAN RP2040 USB Dongle](https://shop.sb-components.co.uk/products/lorawan-rp2040-usb-dongle)

  * [LoRaWAN Breakout Board](https://shop.sb-components.co.uk/products/lorawan-breakout)
  
  * [LoRaWAN HAT for Raspberry Pi](https://shop.sb-components.co.uk/products/lorawan-hat-for-raspberry-pi)
  
  * [LoRaWAN Gateway HAT for Raspberry Pi](https://shop.sb-components.co.uk/products/lorawan-gateway-hat)
   

## Product License

This is ***open source*** product. Kindly check LICENSE.md file for more information.

Please contact support@sb-components.co.uk for technical support.
<p align="center">
  <img width="360" height="100" src="https://cdn.shopify.com/s/files/1/1217/2104/files/Logo_sb_component_3.png?v=1666086771&width=300">
</p>
