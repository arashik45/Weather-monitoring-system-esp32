
# 🌦️ Weather Monitoring System with Buzzer Alerts (ESP32 + Blynk)

A complete IoT-based **Weather Station** using **ESP32**, multiple environmental sensors, **LCD display**, **Blynk IoT dashboard**, and **automatic buzzer alerts** for critical conditions.

This project is designed to be **plug-and-play**, stable, and future-ready.


## 🔧 Hardware Components Required

| Component                           | Quantity    |
| ----------------------------------- | ----------- |
| ESP32 Dev Module                    | 1           |
| DHT11 Temperature & Humidity Sensor | 1           |
| BMP180 / BMP085 Pressure Sensor     | 1           |
| MQ135 Air Quality Sensor            | 1           |
| Rain Sensor Module (Analog)         | 1           |
| 16×2 LCD with I2C Module            | 1           |
| Active Buzzer                       | 1           |
| Breadboard + Jumper Wires           | As required |
| 5V Power Source / USB Cable         | 1           |


## 🔌 Pin Connections (VERY IMPORTANT)

### ✅ ESP32 Pin Mapping

| Module           | Pin Name | ESP32 GPIO  |
| ---------------- | -------- | ----------- |
| **DHT11**        | DATA     | GPIO **4**  |
|                  | VCC      | 3.3V / 5V   |
|                  | GND      | GND         |
| **BMP180 (I2C)** | SDA      | GPIO **21** |
|                  | SCL      | GPIO **22** |
|                  | VCC      | 3.3V        |
|                  | GND      | GND         |
| **LCD I2C**      | SDA      | GPIO **21** |
|                  | SCL      | GPIO **22** |
|                  | VCC      | 5V          |
|                  | GND      | GND         |
| **MQ135**        | AO       | GPIO **35** |
|                  | VCC      | 5V          |
|                  | GND      | GND         |
| **Rain Sensor**  | AO       | GPIO **34** |
|                  | VCC      | 5V          |
|                  | GND      | GND         |
| **Buzzer**       | +        | GPIO **14** |
|                  | −        | GND         |

⚠️ **Note:** GPIO 34 & 35 are **input-only**, perfect for analog sensors.


## 📲 Blynk Dashboard Setup

### Required Widgets & Virtual Pins

| Data               | Widget Type   | Virtual Pin |
| ------------------ | ------------- | ----------- |
| Temperature        | Gauge / Label | V0          |
| Humidity           | Gauge / Label | V1          |
| Pressure (hPa)     | Label         | V2          |
| Altitude (m)       | Label         | V3          |
| Air Quality Raw    | Gauge         | V4          |
| Air Quality Status | Label         | V5          |
| Rain Raw Value     | Gauge         | V6          |
| Rain Status        | Label         | V7          |

📌 **Template Info (Already in Code)**

```cpp
#define BLYNK_TEMPLATE_ID "TMPL6WXLnq93z"
#define BLYNK_TEMPLATE_NAME "Weather Monitoring System"
```


## 🚨 Buzzer Alert Logic

The buzzer automatically turns **ON** when **ANY** of the following conditions occur:

| Condition        | Trigger            |
| ---------------- | ------------------ |
| Heavy Rain       | Rain sensor < 3500 |
| High Temperature | Temperature > 40°C |
| Poor Air Quality | MQ135 value > 1500 |

🔕 Automatically turns **OFF** when conditions return to normal.



## 🖥️ LCD Display Format

**Line 1:**

```
T:25.4 H:60
```

**Line 2:**

```
AQ:420 Rain
```

Displays real-time data refreshed every **2 seconds**.

---

## 📡 Data Update Interval

* Sensor reading interval: **2 seconds**
* Blynk update: **Real-time**
* LCD refresh: **Every cycle**

Handled using `BlynkTimer` (non-blocking).

---

## 📚 Required Arduino Libraries

Install all from **Arduino Library Manager**:

* `Blynk`
* `DHT sensor library`
* `Adafruit Unified Sensor`
* `Adafruit BMP085`
* `LiquidCrystal I2C`
* `Wire`
* `WiFi (ESP32 core)`

---

## ⚙️ Board & Upload Settings (Arduino IDE)

| Setting          | Value                             |
| ---------------- | --------------------------------- |
| Board            | ESP32 Dev Module                  |
| Upload Speed     | 921600                            |
| CPU Frequency    | 240MHz                            |
| Flash Mode       | QIO                               |
| Partition Scheme | Default                           |
| Port             | COM / ttyUSB (Select Correct One) |

---

## 🔐 WiFi Configuration

Update inside code:

```cpp
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";
```

---

## 🧠 Stability Features (Why This Code Is Reliable)

* ✔ Sensor fallback values prevent crashes
* ✔ Invalid readings filtered
* ✔ Non-blocking timer (no `delay()`)
* ✔ ESP32-safe GPIO selection
* ✔ Modular alert logic

---

## 🧪 Tested On

* ESP32 Dev Module
* Arduino IDE 2.x
* Blynk IoT New Platform
* Windows 10 / 11

---

## 🚀 Future Improvements (Optional)

* Add SD Card data logging
* Push notification alerts via Blynk
* Replace DHT11 with DHT22
* Calibrate MQ135 using ppm formula
* Add weather prediction logic

---

## 👤 Author

**Ashik**
Department of ICE
Daffodil International University
Project Type: *IoT / Embedded Systems*
