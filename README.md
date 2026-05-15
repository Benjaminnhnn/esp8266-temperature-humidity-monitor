# ESP8266 Temperature & Humidity Monitoring System

[![Platform](https://img.shields.io/badge/platform-ESP8266-blue)](#)
[![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D)](#)

## Overview

This repository contains the source code and project report for an IoT-based temperature and humidity monitoring system using the ESP8266 NodeMCU.

The system reads temperature and humidity data from a DHT11 sensor, displays real-time values on an OLED screen, sends sensor data to ThingSpeak, and controls a 5V fan through a relay when the temperature exceeds the configured threshold.

This project was developed as part of the **Embedded Wireless Network System** course.

## Features

- Read temperature and humidity values using the DHT11 sensor
- Connect ESP8266 NodeMCU to Wi-Fi
- Upload temperature, humidity, and relay status to ThingSpeak
- Display real-time data on an OLED screen
- Automatically control a 5V fan through a relay module
- Support remote monitoring through an IoT cloud platform
- Include full project report and demo video reference

## System Architecture

The system is built around the ESP8266 NodeMCU as the main controller. The DHT11 sensor collects environmental data, while the relay module controls the fan based on the temperature threshold. ThingSpeak is used for cloud data storage and visualization.

```text
DHT11 Sensor
     |
     v
ESP8266 NodeMCU  --->  OLED Display
     |
     +----------->  Relay Module  --->  5V Fan
     |
     +----------->  Wi-Fi  --->  ThingSpeak Cloud
```

## Hardware Components

| Component | Description |
|---|---|
| ESP8266 NodeMCU | Main microcontroller with Wi-Fi capability |
| DHT11 Sensor | Measures temperature and humidity |
| 5V Relay Module | Controls the fan circuit |
| 5V Fan | Cooling device controlled by relay |
| OLED Display | Displays temperature and humidity locally |
| Power Supply | Provides power to the ESP8266 and fan circuit |

## Software and Services

| Tool / Service | Purpose |
|---|---|
| Arduino IDE | Used to write, compile, and upload code to ESP8266 |
| ThingSpeak | Stores and visualizes IoT sensor data |
| Supabase | Stores user and device information in the full system design |
| .NET Framework | Used for the desktop user interface in the full project implementation |

## Repository Structure

```text
esp8266-temperature-humidity-monitor/
│
├── README.md
├── .gitignore
│
├── report/
│   └── NT131_Nhom14_Report.pdf
│
└── arduino/
    └── GIAM_SAT_NHIET_DO_DO_AM/
        ├── GIAM_SAT_NHIET_DO_DO_AM.ino
        ├── BlynkEdgent.h
        ├── BlynkState.h
        ├── ConfigMode.h.example
        ├── ConfigStore.h
        ├── Console.h
        ├── Indicator.h
        ├── OTA.h
        ├── ResetButton.h
        └── Settings.h
```

## Wiring Summary

| ESP8266 NodeMCU | Connected Component |
|---|---|
| 3V3 | DHT11 VCC |
| D0 / GPIO16 | DHT11 Data |
| GND | DHT11 GND |
| VIN | Relay VCC |
| D5 / GPIO14 | Relay IN |
| GND | Relay GND |

## Arduino Setup

### 1. Install Arduino IDE

Download and install Arduino IDE from the official Arduino website.

### 2. Install ESP8266 Board Package

Open Arduino IDE and add the ESP8266 board manager URL:

```text
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

Then install the ESP8266 board package from **Boards Manager**.

### 3. Install Required Libraries

Install the following libraries in Arduino IDE:

- ESP8266WiFi
- ThingSpeak
- DHTesp
- Wire
- Adafruit GFX
- Adafruit SSD1306

### 4. Configure Credentials

This repository uses an example configuration file to avoid exposing private credentials.

Copy:

```text
ConfigMode.h.example
```

Rename it to:

```text
ConfigMode.h
```

Then update the following values with your own information:

```cpp
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define THINGSPEAK_CHANNEL_ID 0000000
#define THINGSPEAK_WRITE_API_KEY "YOUR_THINGSPEAK_WRITE_API_KEY"
```

> Do not commit real Wi-Fi passwords, API keys, database connection strings, or email credentials to GitHub.

### 5. Upload Code to ESP8266

In Arduino IDE, select:

```text
Board: NodeMCU 1.0 (ESP-12E Module)
Port: Your ESP8266 COM Port
```

Then open the file:

```text
arduino/GIAM_SAT_NHIET_DO_DO_AM/GIAM_SAT_NHIET_DO_DO_AM.ino
```

Click **Upload** to flash the code to the ESP8266.

## Data Fields on ThingSpeak

| Field | Data |
|---|---|
| Field 1 | Temperature |
| Field 2 | Humidity |
| Field 3 | Relay / Fan Status |

## Demo Video

The demo video is hosted on Google Drive.

[Watch Demo Video](https://drive.google.com/drive/folders/1MJmVwwYzH-KYlTbX0ja_X93nqAHEek35?usp=sharing)

## Project Report

The full project report is available in the `report/` folder:

```text
report/NT131_Nhom14_Report.pdf
```

## Team Members

| Student ID | Name |
|---|---|
| 23520541 | Trần Nguyễn Việt Hoàng |
| 23521572 | Lê Quang Tiến |
| 23521778 | Lê Hoàng Việt |

## Future Improvements

- Replace DHT11 with DHT22 or SHT31 for better accuracy
- Add email, mobile push notification, or Telegram alert
- Send sensor data directly to the backend instead of depending only on ThingSpeak
- Improve the desktop user interface
- Add historical data analysis and AI-based environmental recommendations
- Add better security for authentication and device management

## Security Notes

Before publishing this repository, make sure the following private information is removed:

- Wi-Fi SSID and password
- ThingSpeak API keys
- Supabase database connection string
- SMTP email and app password
- Any private access token or secret key


