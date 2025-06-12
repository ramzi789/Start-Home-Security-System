/* File: SmartHomeSecurity.ino */

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

/*=== User Configuration ===*/
char const* WIFI_SSID = "YOUR_SSID";
char const* WIFI_PASS = "YOUR_PASS";
char const* BLYNK_AUTH = "YOUR_AUTH_TOKEN";

/*=== Pin Definitions ===*/
const uint8_t PIN_PIR    = D5;
const uint8_t PIN_REED   = D6;
const uint8_t PIN_LED    = D7;
const uint8_t PIN_BUZZER = D8;
const uint8_t PIN_MQ2    = A0;

/*=== Alarm Thresholds ===*/
const int GAS_THRESHOLD = 300;  // adjust via MQ‐2 onboard pot

/*=== State Flags ===*/
bool pirTriggered  = false;
bool reedTriggered = false;
bool gasTriggered  = false;

BlynkTimer timer;

void setup() {
  // Serial for debug
  Serial.begin(115200);

  // Initialize pins
  pinMode(PIN_PIR,    INPUT);
  pinMode(PIN_REED,   INPUT_PULLUP);
  pinMode(PIN_LED,    OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  // Connect to Wi-Fi & Blynk
  Blynk.begin(BLYNK_AUTH, WIFI_SSID, WIFI_PASS);

  // Check sensors every 500 ms
  timer.setInterval(500L, checkSensors);
}

void loop() {
  Blynk.run();
  timer.run();
}

// Check each sensor and trigger alarm/notification
void checkSensors() {
  // Read sensors
  bool pirState  = digitalRead(PIN_PIR);
  bool reedState = digitalRead(PIN_REED) == LOW;  // LOW = closed ➔ no intrusion
  int  gasValue  = analogRead(PIN_MQ2);

  // PIR Motion
  if(pirState && !pirTriggered) {
    alarm("Motion detected!");
    pirTriggered = true;
  }

  // Reed Switch (door/window)
  if(reedState && !reedTriggered) {
    alarm("Door/window opened!");
    reedTriggered = true;
  }

  // Gas leak
  if(gasValue > GAS_THRESHOLD && !gasTriggered) {
    alarm("Gas leak detected!");
    gasTriggered = true;
  }
}

// Activate buzzer, LED & push notification
void alarm(const char* message) {
  Serial.println(message);
  // Push notification
  Blynk.notify(message);
  // Flash LED & buzzer beep
  for(int i=0; i<5; i++){
    digitalWrite(PIN_LED, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
    delay(200);
    digitalWrite(PIN_LED, LOW);
    digitalWrite(PIN_BUZZER, LOW);
    delay(200);
  }
}
