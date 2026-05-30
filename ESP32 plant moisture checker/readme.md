#   ESP32 plant moisture checker

| general |
| - |
| created: May 21st, 2026 |
| updated: May 22nd, 2026 |
| author: ITWorks4U |
| version: 1.0.0 |
| framework: Arduino* |

>   *No need to use ESP-IDF, because this would be too elaborate for this simple project.

##  description

>   Similar workflow to the [Arduino plant moisture checker project](https://github.com/ITWorks4U/microcontroller_projects/tree/main/plant%20moisture%20checker).

-   automatic low moisture detection with Capacitive Soil Moisture Sensor v1.2
-   if a plant needs water, an used certain pump (5V, 240 mA) turns on
    -   this setup is planned to use for up to four sensors and pumps
-   check each 24 hours, if a plant needs water

### hardware

| hardware | description |
| - | - |
| [Capacitive Soil Moisture Sensor v1.2](https://www.amazon.de/dp/B07FLR13FS?ref=ppx_yo2ov_dt_b_fed_asin_title) | comes with a scan range between 400 - 2,220* |
| [IRLZ44N MOSFET (N-Channel)](https://www.amazon.de/dp/B0CBKH4XGL?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1) | controlled by the arduino board |
| [simple pump](https://www.amazon.de/dp/B0FC245QMP?ref=ppx_yo2ov_dt_b_fed_asin_title) | 5V, 240 mA |
| [NoceMCU ESP32](https://www.amazon.de/Entwicklungsplatine-QIQIAZI-ESP32-WROOM-32-Bluetooth-Dual-Cores/dp/B0DHRV7784/ref=sr_1_6?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=2G913ZOU76QQJ&dib=eyJ2IjoiMSJ9.0HQysaHgEqFjRs7m20z3kJrI_4wHjZlp7x6K1Czwy4iWQr7bQfz4u1YCzqsbju7MI6dTYrN7nEKxJcDBT7dvsfnXaAIBtA1CzQ9p-dZCTkNejFTq_nuEOGWgJi80QYfKA7OW-84RM5igOU8joE1jnsPrWq-BI-eVUeeqT4lsSELZCrBARjo2OU8hBfoYqqmjtA5LuW77t_t7AUY4SCHEZX5UEt2V_UzZG5xFhw46R9xO8hJ-i5iWP7ud7H77YEM0kRS1nXsDorpLf18EdNh9fkAv6fiEVrSNwxTN-8hnnWU.Kv55C2EuV5xTjKVMktxhQ7TPKtgS5FDa6sUhnAurMCQ&dib_tag=se&keywords=ESP32&qid=1775036191&sprefix=esp32%2Caps%2C117&sr=8-6) | the used board |

>   *Depends on the used micro controller. For an Arduino Uno the scan range lies between `[20..120]`.

>   **NOTE**:   For an **ESP32**, the analog output for a *Capacitive Soil Moisture Sensor* is set up to 2.1V (when dry). On a wet state the output is set to 440mV.

####    workflow
1.  scan for required hardware
    -   at least one Capacitive Soil Moisture Sensor must exist and works fine
    -   on each analog pin an additional 10kΩ resistor to GND exists to prevent any random value
    -   if no sensor has been found, the internal LED blinks each 500ms forever
2.  check each second, if the given timespan has been reached
3.  if the measured value exceeds the threshold value, the certain pump turns on
4.  repeat

### used board pins

| pin | used for |
| - | - |
| `{32, 33, 34, 35}` | addresses for moisture sensor analog value |
| `{4, 16, 17, 5}` | addresses for MOSFET gate |