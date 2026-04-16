#   Arduino plant moiture checker

| general |
| - |
| created: September 11th, 2025 |
| updated: April 16th, 2026 |
| author: ITWorks4U |
| version: 2.0.0 |

##  description

-   automatic low moiture detection with Capacitive Soil Moiture Sensor v1.2
-   if a plant needs water, the certain pump (simple 5V pump with 240 mA) turns on for 5 seconds
    -   can be used for up to four sensors and pumps
-   an external potentiometer (10 kOhms) controls the time span between 3 and 24 hours

### hardware

| hardware | description |
| - | - |
| [Capacitive Soil Moiture Sensor v1.2](https://www.amazon.de/dp/B07FLR13FS?ref=ppx_yo2ov_dt_b_fed_asin_title) | comes with a scan range between 500 - 200; the lower the value, the more moiture has been detected => "feature" of this sensor |
| [IRLZ44N MOSFET (N-Channel)](https://www.amazon.de/dp/B0CBKH4XGL?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1) | controlled by the arduino board |
| [simple pump](https://www.amazon.de/dp/B0FC245QMP?ref=ppx_yo2ov_dt_b_fed_asin_title) | 5V, 240 mA; external powered |
| Muizei development board | similar to an Arduino Uno Rev 3 |
| [10 kOhm potentiometer](https://www.amazon.de/Aussel-Potentiometer-Drehpotentiometer-Kappenmuttern-Unterlegscheibe/dp/B0734K6WYP/ref=sr_1_8?crid=2WYAFO1DFXAWY&dib=eyJ2IjoiMSJ9.bHWlfozohQIKw-ermoCjjYmeznZ1ggCN06DDlZPRIrzSytwloGsBez1Fg7gJXqk9mIJQd2_6d2QyDS8XsjkrQxbnJ2UKduXVpWmXKbwqIewo57zzCN_FaFMnwm_yZJt2bbBhsfKTQ8MsR-y5CJGW0HXBVC913-x1BwxyImS1dtvqf-vLlDqmeFTayOyKzf5tWzer7nVBSGUlHEZBChjV12G0KAc17CTR8x3e-XUA0L2Cs7tLSjCZI_btYZAB37FV5TIa2LdCejVIe4PQfouQ-98nglqTYHemU-WAiFhn5sM.YwzO0yZbGCkgzjgyUkK4EbMCjuyI1_S6NmzB5lzGpR0&dib_tag=se&keywords=potentiometer+10k&qid=1776347764&sprefix=potentiometer+10%2Caps%2C129&sr=8-8) | to control the timespan between 3 and 24 hours

####    workflow
1.  scan for required hardware
    1.  if no required hardware has been found, the internal LED blinks each 500ms forever
2.  check each second, if the given timespan has been reached (controlled by the potentiometer)
3.  if the measured value has been exceeded the threshold value (425), the pump is active for 5 seconds
4.  repeat

### used board pins

| pin | used for |
| - | - |
| `{8, 9, 10, 11}` | addresses for  moiture sensor power supply |
| `{A1, A2, A3, A4}` | addresses for moiture sensor analog value |
| `{2, 3, 4, 5}` | addresses for MOSFET gate |