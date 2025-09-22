#	Plant moiture checker

-   check, if a plant needs water by using:
    -   Capacitive Soil Moiture Sensor v1.2 (2 times)
        -   comes with a scan range between 500 - 200
        -   the lower the value, the more moiture has been detected
    -   MOSFET (N-Channel, 2 times)
        -   IRF520 (yeah, I didn't had other MOSFETs °(^_^))
    -   simple pump (2 times)
        -   5V, 240 mA
        -   powered by an external 9V battery and connected to the MOSFET
    -   Muizei development board
        -   similar to an Arduino Uno Rev 3
        -   control the gate for MOSFET

### workflow
1.  the moiture sensors are permanently powered by the 9V block
2.  every one second the analog value (A0, A1) checks the detected moiture value
3.  a fixed threshold value of 350 determines the trigger point
    -   if the moiture sensor value exceeds that threshold value, the certain pump is going to activate
    -   the certain pump is still active until the value is up to 350
4.  repeat the workflow with a delay of one second

### Miuzei board

| pin | used for |
| - | - |
| A0 | analog input for moiture sensor 1 |
| A1 | analog input for moiture sensor 2 |
| 2 | digial output for IRF520 MOSFET 1 |
| 3 | digital output for IRF520 MOSFET 2 |
| GND | common ground both IRF520 MOSFETs |
| 5V | common 5V power for both IRF520 MOSFETs |