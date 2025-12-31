// -------- WEATHER STATION WITH BUZZER ALERTS --------

#define BLYNK_TEMPLATE_ID "TMPL6WXLnq93z"
#define BLYNK_TEMPLATE_NAME "Weather Monitoring System"
#define BLYNK_AUTH_TOKEN "ktg_aWnGamz4Zttf6R7uOtd2F5fScA1_"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>

// ------------------- WIFI -------------------
char ssid[] = "Second Home";
char pass[] = "12345670";

// ------------------- SENSORS -------------------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;

#define MQ135_PIN 35
#define RAIN_PIN 34

// ------------------- LCD -------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

// ------------------- BUZZER -------------------
#define BUZZER_PIN 14

// Fallback values for stability
float lastTemp = 25;
float lastAltitude = 20;


// ===========================================================
// SENSOR FUNCTION (RUNS EVERY 2 SECONDS)
// ===========================================================
void sendSensor() {

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || temp < 5 || temp > 50) temp = lastTemp;
  else lastTemp = temp;

  if (isnan(hum)) hum = 0;

  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude(101325);

  if (altitude < -5 || altitude > 500) altitude = lastAltitude;
  else lastAltitude = altitude;

  int airRaw = analogRead(MQ135_PIN);
  int rainRaw = analogRead(RAIN_PIN);

  // Air quality text
  String airLevel =
      (airRaw < 200) ? "Fresh" :
      (airRaw < 400) ? "Moderate" :
      (airRaw < 700) ? "Polluted" : "Bad";

  String rainStatus = (rainRaw < 3500) ? "Rain" : "No Rain";


  // =======================================================
  // BUZZER ALERT LOGIC
  // =======================================================
  bool alertRain = (rainRaw < 3500);
  bool alertTemp = (temp > 40);
  bool alertAir  = (airRaw > 1500);

  if (alertRain || alertTemp || alertAir) {
    digitalWrite(BUZZER_PIN, HIGH);   // BUZZ ON
  } else {
    digitalWrite(BUZZER_PIN, LOW);    // BUZZ OFF
  }


  // =======================================================
  // SERIAL MONITOR OUTPUT
  // =======================================================
  Serial.println("=================================");
  Serial.printf("Temp: %.1f °C\n", temp);
  Serial.printf("Humidity: %.0f %%\n", hum);
  Serial.printf("Pressure: %.1f hPa\n", pressure / 100.0);
  Serial.printf("Altitude: %.1f m\n", altitude);
  Serial.printf("Air Quality: %d (%s)\n", airRaw, airLevel.c_str());
  Serial.printf("Rain Sensor: %d (%s)\n", rainRaw, rainStatus.c_str());
  Serial.printf("Buzzer: %s\n", (alertRain || alertTemp || alertAir) ? "ON" : "OFF");
  Serial.println("=================================\n");


  // =======================================================
  // LCD DISPLAY
  // =======================================================
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print(" H:");
  lcd.print(hum, 0);

  lcd.setCursor(0, 1);
  lcd.print("AQ:");
  lcd.print(airRaw);
  lcd.print(" ");
  lcd.print(rainStatus);


  // =======================================================
  // BLYNK DATA PUSH
  // =======================================================
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, pressure / 100.0);
  Blynk.virtualWrite(V3, altitude);
  Blynk.virtualWrite(V4, airRaw);
  Blynk.virtualWrite(V5, airLevel);
  Blynk.virtualWrite(V6, rainRaw);
  Blynk.virtualWrite(V7, rainStatus);
}


// ===========================================================
// SETUP
// ===========================================================
void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();

  dht.begin();
  lcd.init();
  lcd.backlight();

  if (!bmp.begin()) {
    lcd.print("BMP180 ERROR");
    while (1);
  }

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  timer.setInterval(2000L, sendSensor);
}


// ===========================================================
// LOOP
// ===========================================================
void loop() {
  Blynk.run();
  timer.run();
}
