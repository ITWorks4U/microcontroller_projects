#   Plant moiture checker

####    general

| . | . |
| - | - |
| created | September 11th, 2025 |
| updated | November 11th, 2025 |
| author | ITWorks4U |
| version | 1.1.10 |

####    description
-   check, if a plant needs water by using:
    -   Capacitive Soil Moiture Sensor v1.2
        -   comes with a scan range between 500 - 200
        -   the lower the value, the more moiture has been detected
            -   *depends on the used sensor, used micro controller, ...*
    -   MOSFET (N-Channel)
        -   IRLZ44N
    -   simple pump
        -   5V, 240 mA
        -   powered by an external 9V battery and connected to the MOSFET
    -   Muizei development board
        -   similar to an Arduino Uno Rev 3
        -   control the gate for MOSFET

####    workflow
1.  the moiture sensors are powered by the micro controller for 100ms
2.  if the measured value has been exceeded the threshold value (425), the pump is active for 5 seconds
3.  deep sleep for one hour

### Miuzei board

| pin | used for |
| - | - |
| A0 | analog input for moiture sensor |
| 2 | digial output for IRLZ44N MOSFET |
| 8 | digital output for moiture sensor power supply |