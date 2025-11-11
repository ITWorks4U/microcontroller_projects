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
* updated:    November 11th, 2025
* author:     ITWorks4U
* version:    1.1.10
*/

#ifndef PIN_SETTINGS_H
#define PIN_SETTINGS_H

#define PIN_MOSFET          2         //  MOSFET (IRLZ44N)
#define PIN_MOITURE_SENSOR  A0        //  moiture data
#define PIN_MOITURE_POWER   8         //  moiture power

#endif