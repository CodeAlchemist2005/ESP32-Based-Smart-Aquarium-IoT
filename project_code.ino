// --------------------------------------------------
// BLYNK TEMPLATE INFO
// --------------------------------------------------
#define BLYNK_TEMPLATE_ID    "Your template id"
#define BLYNK_TEMPLATE_NAME  "your template name"
#define BLYNK_AUTH_TOKEN     "your bynk auth token"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#include <ESP32Servo.h>

// --------------------------------------------------
// WIFI SETTINGS
// --------------------------------------------------
char ssid[] = "your wifi name";
char pass[] = "your wifi password";

// --------------------------------------------------
// DHT11 SENSOR
// --------------------------------------------------
#define DHTPIN 32
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// --------------------------------------------------
// 4-in-1 UART SENSOR (pH + Moist + Temp + Light)
// --------------------------------------------------
#define RXD2 16
#define TXD2 17

HardwareSerial SensorSerial(2);

// --------------------------------------------------
// BLYNK VIRTUAL PINS
// --------------------------------------------------
#define VP_PH     V0
#define VP_MOIST  V1
#define VP_TEMP   V2
#define VP_LIGHT  V3
#define VP_AIRT   V4
#define VP_AIRH   V5
#define VP_FEED   V6   // Manual feed button

// --------------------------------------------------
// SERVO FEEDER (SG90)
// --------------------------------------------------
#define SERVO_PIN 18

#define FEED_CLOSE_ANGLE   0     // SG90 fully closed
#define FEED_OPEN_ANGLE   180    // SG90 fully open

Servo feederServo;

// --------------------------------------------------
// AUTOMATIC FEEDING TIMING
// --------------------------------------------------
unsigned long lastFeedTime = 0;
const unsigned long FEED_INTERVAL = 12UL * 60UL * 60UL * 1000UL; // 12 hours

// --------------------------------------------------
// FUNCTION TO READ SENSOR FRAME
// --------------------------------------------------
int readFrame(uint8_t *buf, int len, int timeout = 300) {
  unsigned long t = millis();
  int idx = 0;

  while ((millis() - t) < timeout && idx < len) {
    if (SensorSerial.available()) {
      buf[idx++] = SensorSerial.read();
    }
  }
  return idx;
}

// --------------------------------------------------
// FISH FEEDING FUNCTION (USED BY AUTO + MANUAL)
// --------------------------------------------------
void dispenseFeed() {
  Serial.println("🐟 Feeding Started");

  feederServo.write(FEED_OPEN_ANGLE);   // Open flap (180°)
  delay(2000);                           // 2 second stop

  feederServo.write(FEED_CLOSE_ANGLE);  // Close flap
  delay(500);

  Serial.println("✅ Feeding Completed");
}

// --------------------------------------------------
// BLYNK MANUAL FEED BUTTON
// --------------------------------------------------
BLYNK_WRITE(VP_FEED) {
  if (param.asInt() == 1) {
    dispenseFeed();
  }
}

// --------------------------------------------------
// SETUP
// --------------------------------------------------
void setup() {
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  dht.begin();
  SensorSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Servo setup (SG90)
  feederServo.setPeriodHertz(50);
  feederServo.attach(SERVO_PIN, 500, 2400);
  feederServo.write(FEED_CLOSE_ANGLE);

  lastFeedTime = millis(); // start 12h timer after boot

  Serial.println("✅ Aquarium System Ready with Auto Feeding...");
}

// --------------------------------------------------
// LOOP
// --------------------------------------------------
void loop() {
  Blynk.run();

  // -------- AUTOMATIC FEEDING EVERY 12 HOURS --------
  if (millis() - lastFeedTime >= FEED_INTERVAL) {
    dispenseFeed();
    lastFeedTime = millis();
  }

  // -------- SENSOR DATA --------
  uint8_t req[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x44, 0x09};
  SensorSerial.write(req, 8);

  uint8_t buffer[32];
  int n = readFrame(buffer, 32);

  if (n > 9) {
    int moisture = buffer[3];
    int soilTemp = buffer[5];
    int light    = buffer[7];
    int ph       = buffer[9];

    Blynk.virtualWrite(VP_MOIST, moisture);
    Blynk.virtualWrite(VP_TEMP, soilTemp);
    Blynk.virtualWrite(VP_LIGHT, light);
    Blynk.virtualWrite(VP_PH, ph);
  }

  float aT = dht.readTemperature();
  float aH = dht.readHumidity();

  if (!isnan(aT) && !isnan(aH)) {
    Blynk.virtualWrite(VP_AIRT, aT);
    Blynk.virtualWrite(VP_AIRH, aH);
  }

  delay(1500);
}
