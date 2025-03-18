# MECHANIZED LED Lighting with ESP32

## Overview
This project implements an interactive **MECHANIZED** LED lighting system controlled via a web interface hosted on an **ESP32** server. The system allows users to toggle LEDs representing letters in "MECHANIZED" using a **responsive web page**. When a letter is toggled, the corresponding LED blinks before staying ON.

## Features
- **ESP32 Web Server:** Hosts an HTML page to control LED toggling.
- **Interactive UI:** Users can click on buttons to light up individual letters.
- **Blink Effect:** Each LED blinks in a pattern before turning ON.
- **WiFi Connectivity:** ESP32 connects to a WiFi network to serve the webpage.
- **Optimized for Performance:** Uses efficient handling of GPIO pins and asynchronous requests.

## Hardware Requirements
- **ESP32 Development Board**
- **10 LEDs** (Each representing a letter in "MECHANIZED")
- **Resistors (220Ω - 330Ω)**
- **Breadboard & Jumper Wires**
- **Power Supply (5V via USB or Battery Pack)**

## Software Requirements
- **Arduino IDE** 
- **ESP32 Board Package** (Install via Arduino Board Manager)
- **WiFi Library** (Built-in for ESP32)
- **WebServer Library** (Built-in for ESP32)

## Installation & Setup
### 1. Clone the Repository
```sh
git clone https://github.com/Thejasvenan/Mechanized_IoT.git
cd Mechanized_IoT
```

### 2. Configure WiFi Credentials
Update the following lines in the **Arduino sketch** (`MechanizedLED.ino`):
```cpp
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
```

### 3. Upload Code to ESP32
- Open the project in **Arduino IDE**.
- Select **ESP32 Dev Module** in **Tools → Board**.
- Connect ESP32 and upload the sketch.

### 4. Access the Web Interface
- After uploading, open the **Serial Monitor** at **115200 baud**.
- Note the **ESP32's IP Address** from the Serial output.
- Open a browser and go to:
  ```
  http://<ESP32-IP-Address>
  ```
- Click on the letters to toggle the LEDs!

## File Structure
```
/Mechanized_IoT
│── images.png         # UI button images
│── MechanizedLED.ino  # ESP32 Code
│── README.md          # Project Documentation
```

## Future Improvements
- Add **animations** for a better lighting effect.
- Implement **MQTT support** for remote control.
- Enhance **UI with animations and sounds**.

🚀 **Enjoy controlling LEDs wirelessly with ESP32!** 🚀
