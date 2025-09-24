/*
* Automatic low moiture detection with Capacitive Soil Moiture Sensor v1.2.
* If a plant needs water, the certain pump (simple 5V pump with 240 mA) turns on for 5 seconds.
* NOTE: Those pumps are powered by a 9V battery block.
*
* Used board: Muizei development board (similar to an Arduino Uno Rev 3).
*
* NOTE: The used Capacitive Soil Moiture Sensor v1.2 comes with a detection
* range between 500 - 200. The lower the value, the more moiture has been detected.
*
* created:    September 11th, 2025
* updated:    September 23rd, 2025
* author:     ITWorks4U
* version:    1.0.4
*/

#include "moiture_data.h"

//  --------------
//  global data
//  --------------
static int moiture_data_a0 = -1;
static int moiture_data_a1 = -1;

//  --------------
//  functions
//  --------------
void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(PIN_MOSFET_0, OUTPUT);
  pinMode(PIN_MOSFET_1, OUTPUT);
  pinMode(PIN_SENSOR_0, OUTPUT);
  pinMode(PIN_SENSOR_1, OUTPUT);

  //  permanently turn on the sensors
  digitalWrite(PIN_SENSOR_0, HIGH);
  digitalWrite(PIN_SENSOR_1, HIGH);
}

void loop() {
  moiture_data_a0 = analogRead(MOITURE_SENSOR_A0);
  moiture_data_a1 = analogRead(MOITURE_SENSOR_A1);

  Serial.println("A0: " + String(moiture_data_a0));
  Serial.println("A1: " + String(moiture_data_a1));

  //  if A0 returns a high value, then turn on MOFSET on pin 2
  if (moiture_data_a0 > THRESHOLD_MOITURE) {
    digitalWrite(PIN_MOSFET_0, HIGH);
  } else {
    digitalWrite(PIN_MOSFET_0, LOW);
  }

  //  same procedure for A1 => MOFSET on pin 3
  if (moiture_data_a1 > THRESHOLD_MOITURE) {
    digitalWrite(PIN_MOSFET_1, HIGH);
  } else {
    digitalWrite(PIN_MOSFET_1, LOW);
  }

  //  wait one second
  delay(DELAY_FOR_REPEAT);
}