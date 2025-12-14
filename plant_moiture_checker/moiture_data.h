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

#ifndef MOITURE_DATA_H
#define MOITURE_DATA_H

#define THRESHOLD_MOITURE   425       //  the limitation, when the pump shall start
// #define SLEEP_CYCLES        4500      //  sleep time for one hour (for 8s => enum period_t with SLEEP_8S)
                                      //  8s * 4,500 = 36,000s
#define SLEEP_TIME_MS       8640000   //  8,640,000 ms => 86,400s => one day


#define DELAY_MS            5000      //  5s active duration for pump
#define SENSOR_READ_DELAY   100       //  100ms delay before reading the next data

//  misc
#define BAUD_RATE           115200    //  for debug

//  function prototypes

//  Trigger the moiture sensor and receive
//  the current moiture data.
void trigger_moiture_sensor(void);

#endif