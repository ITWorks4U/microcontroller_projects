#   Arduino plant moisture checker

| general |
| - |
| created: September 11th, 2025 |
| updated: May 14th, 2026 |
| author: ITWorks4U |
| version: 2.0.2 |

##  description

-   automatic low moisture detection with Capacitive Soil Moisture Sensor v1.2
-   if a plant needs water, an used certain pump (5V, 240 mA) turns on for 5 seconds
    -   this setup is planned to use for up to four sensors and pumps
-   an additional external potentiometer (10 kΩ) controls the time span between 3 and 24 hours, if available, otherwise a fixed time amount for each 24 hours checks, if a plant needs water

### hardware

| hardware | description |
| - | - |
| [Capacitive Soil Moisture Sensor v1.2](https://www.amazon.de/dp/B07FLR13FS?ref=ppx_yo2ov_dt_b_fed_asin_title) | comes with a scan range between 400 - 2000 |
| [IRLZ44N MOSFET (N-Channel)](https://www.amazon.de/dp/B0CBKH4XGL?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1) | controlled by the arduino board |
| [simple pump](https://www.amazon.de/dp/B0FC245QMP?ref=ppx_yo2ov_dt_b_fed_asin_title) | 5V, 240 mA |
| [Arduino Uno Rev 3](https://www.amazon.de/Rev3-Development-Entwicklungsboard-kompatibel-Aruduino/dp/B0FMNCC4YC/ref=sr_1_6?crid=3N11HCSEW184F&dib=eyJ2IjoiMSJ9._671WvdwBREGkVtl-BiUMUaBCcaP0FGvKUyWFtvXxDeG0IvJ6qeKC0nO_WF4ks2D4o97npuo8ho-PXZ8H4oxWMn40PxyNn29bWvRjitvm2k0L8_rSZTStHXV9QW60BkNgBulPly0cSWjbchAPJ9idDMz85ib2Pi6UAi8tfziWcmXujE_5g6yUYk288L3XLjDRdr1fC3E2hZcXca_MOMiQcLaf8ZQpAKlKIm0sIVGxxWXtZOLJw-ZEzJUJPIH59Fj7HL2A1YSIz6vGnv-qKNzaafUq8-BhsgBXlEZ5ieB76k.hpQFAt_yxYXREQBwtgSaTEkRlXH6HfgmAvt-WjQRKvg&dib_tag=se&keywords=arduino%2Buno&qid=1778764894&s=industrial&sprefix=arduin%2Cindustrial%2C117&sr=1-6&th=1) | the used board |
| [10 kΩ potentiometer](https://www.amazon.de/Aussel-Potentiometer-Drehpotentiometer-Kappenmuttern-Unterlegscheibe/dp/B0734K6WYP/ref=sr_1_8?crid=2WYAFO1DFXAWY&dib=eyJ2IjoiMSJ9.bHWlfozohQIKw-ermoCjjYmeznZ1ggCN06DDlZPRIrzSytwloGsBez1Fg7gJXqk9mIJQd2_6d2QyDS8XsjkrQxbnJ2UKduXVpWmXKbwqIewo57zzCN_FaFMnwm_yZJt2bbBhsfKTQ8MsR-y5CJGW0HXBVC913-x1BwxyImS1dtvqf-vLlDqmeFTayOyKzf5tWzer7nVBSGUlHEZBChjV12G0KAc17CTR8x3e-XUA0L2Cs7tLSjCZI_btYZAB37FV5TIa2LdCejVIe4PQfouQ-98nglqTYHemU-WAiFhn5sM.YwzO0yZbGCkgzjgyUkK4EbMCjuyI1_S6NmzB5lzGpR0&dib_tag=se&keywords=potentiometer+10k&qid=1776347764&sprefix=potentiometer+10%2Caps%2C129&sr=8-8) | to control the timespan between 3 and 24 hours |

>   **NOTE**:   The analog output for a *Capacitive Soil Moisture Sensor* is set up to 2.1V (when dry). On a wet state the output is set to 440mV. These can also be used for an ESP32, which operates with 3.3V.

####    workflow
1.  scan for required hardware
    -   at least one Capacitive Soil Moisture Sensor must exist and works fine
    -   on each analog pin an additional 10kΩ resistor to GND exists to prevent any random value
    -   if no sensor has been found, the internal LED blinks each 500ms forever
2.  check each second, if the given timespan has been reached
3.  if the measured value exceeds the threshold value (set to 2000), the certain pump turns on
4.  repeat

### used board pins

| pin | used for |
| - | - |
| `{8, 9, 10, 11}` | addresses for  moisture sensor power supply |
| `{A1, A2, A3, A4}` | addresses for moisture sensor analog value |
| `{2, 3, 4, 5}` | addresses for MOSFET gate |
| `{A0} (14)` | address for the potentiometer |