/*
* Automatic low moiture detection with Capacitive Soil Moiture Sensor v1.2.
* If a plant needs water, the certain pump (simple 5V pump with 240 mA) turns on for 5 seconds.
* NOTE: This pump is powered by a 9V battery block.
*
* Used board: Muizei development board (similar to an Arduino Uno Rev 3).
*
* NOTE: The used Capacitive Soil Moiture Sensor v1.2 comes with a detection
*       range between 500 - 200. The lower the value, the more moiture has been detected.
* NOTE: On an another micro controller or an other used capacitive soil moiture sensor, even with
*       version 1.2 an another range can be appear.
*
* After scanning the data the device is going to sleep for one hour.
* To realize this the library "Low-Power by Rocket Scream Electronics" is in use.
* NOTE: Only available for certain micro controller boards, like Arduino Uno.
*
* created:    September 11th, 2025
* updated:    December 13th, 2025
* author:     ITWorks4U
* version:    1.1.11
*/

#include "moiture_data.h"
#include "pin_settings.h"

static int moiture_data_a0 = -1;
static unsigned long _max_wait_duration = 0;

void setup() {
  Serial.begin(115200);

  pinMode(PIN_MOSFET, OUTPUT);
  pinMode(PIN_MOITURE_SENSOR, INPUT);

  //  on some boards this certain pin
  //  may be HIGH by default
  digitalWrite(PIN_MOSFET, LOW);

  pinMode(PIN_MOITURE_POWER, OUTPUT);
}

void loop() {
  //  run every one day
  if (millis() - _max_wait_duration > SLEEP_TIME_MS) {
    _max_wait_duration = millis();
    trigger_moiture_sensor();

    if (moiture_data_a0 > THRESHOLD_MOITURE) {
      digitalWrite(PIN_MOSFET, HIGH);
      delay(DELAY_MS);
      digitalWrite(PIN_MOSFET, LOW);
    }

    digitalWrite(PIN_MOITURE_POWER, LOW);
    pinMode(PIN_MOITURE_SENSOR, INPUT);           // avoid leakage
  }
}

void trigger_moiture_sensor(void) {
  delay(SENSOR_READ_DELAY);
  digitalWrite(PIN_MOITURE_POWER, HIGH);
  delay(SENSOR_READ_DELAY);

  moiture_data_a0 = analogRead(PIN_MOITURE_SENSOR);
  Serial.println("data value after " + String(millis() / 1000) + " s: " + String(moiture_data_a0));
  digitalWrite(PIN_MOITURE_POWER, LOW);
}