#   ESP32 Sleep / Wakeup Player

| general |
| - |
| author: ITWorks4U |
| created: December 7th, 2025 |
| updated: April 15th, 2026 |
| version: 0.0.4 |

-   offers to play music in a certain time span and shows a certain ambient color
    -   the time span comes with a fixed setting
        -   morning: 6am - 7am
        -   evening: 9pm - 10pm
    -   a button can stops the music and turns the light off, when the event is active
-   used modules:
    -   [Espressif ESP32 (Node MCU)](https://www.amazon.de/-/en/NodeMCU-Development-QIQIAZI-Bluetooth-Dual-Cores/dp/B0DHRV7784/ref=sr_1_7?crid=UWQBS036BN0B&dib=eyJ2IjoiMSJ9.bGditLJxm3WfgHqaQL4RI-e41AHMgaFUOGRpMaTkSJ4XjKmPtZLnuUkd0MZCUfnd1LO1BhIfNywPv2TvNJtI1WprNKhDk37NmrYOxBBaq0MM7gripNw0S_feKs6OtYfcpIBiROWEMKUjXSP72GS3MdgnVCAECDDpZOFudZenKqZ7ouA8D7EfkA0RFC8sPuhp9fmfesTZQ07ueup6DwPeM2lc7tIshavJn5RkTwpJArElrdA7nXAoGcWs3skzczyr2ATXRRbO8wT4sElXM1WYe8BPFaTf1CXUtgW5Fz9Ftes.6QSzS9wUPMtEbHwSfgUsxQOlHyoILmOTXnIj_flMCT0&dib_tag=se&keywords=ESp32&qid=1776228440&sprefix=esp32%2Caps%2C112&sr=8-7)
    -   [DS1302 RTC](https://www.amazon.de/AZDelivery-DS1302-Compatible-Arduino-Raspberry/dp/B07WWCQDBZ/ref=sr_1_5_sspa?crid=26EHQIS92XVVX&dib=eyJ2IjoiMSJ9.oAajQ150gFStCzNp7tD49NII8cyOTF82qvg9rg1qMY1mjJekDhHEQGwyl7QhpTjK.DEzQtyxAbT9NZ-1VI6vorNWsDmqxM-pB9TWlsjhBJNM&dib_tag=se&keywords=ds1302rtc&qid=1776228335&sprefix=ds1302%2Brtc%2Caps%2C105&sr=8-5-spons&aref=11e5oeK8zD&sp_csd=d2lkZ2V0TmFtZT1zcF9tdGY&th=1)
    -   [WS2812B LED stripe (144 LEDs)](https://www.amazon.de/-/en/Jun-Saxifragelec-Individually-Addressable-Flexible-Waterproof/dp/B0B8N4V9HW/ref=sr_1_8?crid=1DDCJXY97NXQ5&dib=eyJ2IjoiMSJ9.N3Wr0sduVQN96Icgq719EcCx0NWDeXiT5c9Kw8IUUekM4CoOcsPx82xwTNdnJFUatuUKztYLlNEoDWvcEKrQJ6fQmeF0xle2t0PXzcm8Q8Gl9d91PxEFh77wZzFAJMte81Cts-2sF0MSvoYYVRo0ztV6Fgixhx72jhbiIH--As-A3oQGFnKjrj19Tl6ksISB916HuWJLKFqBan6YxVMyg6NUYyL2XXAonsDAiFAWMpfhiObSsuk_9MrpZI6hbLP6CZsoz3yOkxNve_-TrBLQHSWGo7tM7AAaUxMlJaV7Fns.-tBNR7aP6xx8Rm_IpId968auE93NvYD7u-Lf6McPoVs&dib_tag=se&keywords=ws2812b%2Bled%2Bstrip&qid=1776228377&sprefix=ws2812b%2Caps%2C103&sr=8-8&th=1)
    -   [MP3-TF-16P](https://www.amazon.de/-/en/AZDelivery-MP3-Player-Compatible-Arduino/dp/B07Z5D1TX8/ref=sr_1_1?crid=2BUGUYU5DWK52&dib=eyJ2IjoiMSJ9.qkBJpcGCjayy17SMhLB0FX4Vlt99y8PArp3668hWKGuPRe2ektbsxVX6M6K5OygnFHm-ws2DmaTuUu1z0uYyaGlksVHFU9bLlkFVMv0J4-p6mTRx41H6qWDiVMHjEj1xZ-GdIZKfvQqDnHBVIiyHJqeQwrO6ijZBnQvubchwpAx7w2gh_YLYMLhhfXwgNKo1MkvBJptdFFXAaBKyPRvwUD6wz5hKY8pvN3DRxfUSX3hII6U8Ka5zshfQ9YPGt8z8c37yVYPANpy-Hyc3XjOJ9g.CAC7eDun_8A1e4lJ67hPlkHWPYtMUjDtLxXdW8azD5s&dib_tag=se&keywords=MP3-TF-16P&qid=1776228412&sprefix=mp3-tf-16p%2Caps%2C102&sr=8-1&th=1)

##  libraries
-   this project doesn't come with the used libraries

| module | library | reference | version |
| - | - | - | - |
| DS1302 RTC | RTCDS1302 | https://github.com/Makuna/Rtc?tab=LGPL-3.0-1-ov-file | 2.5.0 |
| WS2812B LED stripe | FastLED | https://github.com/FastLED/FastLED | 3.10.3 |
| MP3-TF-16P | DFRobotDFPlayerMini | https://github.com/DFRobot/DFRobotDFPlayerMini | 1.0.6 |

### ambience
-   depending on morning or evening music a certain ambience is given by:
    -   smooth coloring
    -   music for wake up / sleep

-   up to all 144 LEDs can be triggered

| routine | light |
| - | - |
| morning | orange-yellow |
| evening | light blue-violet |

####    LED stripe
-   WS2812B
-   144 LEDs
-   length of 1m
-   DC 5V
-   up to 0.3 W / LED => 43,2W total

>   **NOTE**:    *An external [5V power supply](https://www.amazon.de/ZUOKENZU-Adapters-Converter-Inverter-Transformer-DC5V-2A/dp/B09KNFD38L/ref=sxin_15_pa_sp_search_thematic_sspa?content-id=amzn1.sym.54b8112d-c98a-4e2f-ba6b-72a4ca0ff5c2%3Aamzn1.sym.54b8112d-c98a-4e2f-ba6b-72a4ca0ff5c2&crid=2XHRVQZK371XZ&cv_ct_cx=5v%2Bnetzteil%2Bmodul&keywords=5v%2Bpower%2Bsupply%2Bmodule&pd_rd_i=B09KNFD38L&pd_rd_r=335dd8f6-2fd7-4e07-80ef-6da4ff529d0d&pd_rd_w=IRxRt&pd_rd_wg=5co0P&pf_rd_p=54b8112d-c98a-4e2f-ba6b-72a4ca0ff5c2&pf_rd_r=HAAGQZ4YYF1VQVDZ6BFD&qid=1776228680&sbo=RZvfv%2F%2FHxDF%2BO5021pAnSA%3D%3D&sprefix=5v%2Bpower%2Bsupply%2Caps%2C124&sr=1-5-6e6ea531-5af4-4866-af75-1ef299d1c279-spons&aref=ZaogySWknI&sp_csd=d2lkZ2V0TmFtZT1zcF9zZWFyY2hfdGhlbWF0aWM&th=1) is recommended, because the microcontroller may be unable to handle enough power to control the LED stripe, MP3 module, RTC module, etc. at the same time.*

### error codes
-   in case of an error instead of serial communication the built in LED is in use
-   this LED shows a certain code to display a detected possible error
    -   S := short time (50ms)
    -   L := long time (250ms)
        -   a break between two or more codes is given with a delay of 25ms

| event | code | spent time in ms | is critical | internal fix attempt |
| - | - | - | - | - |
| everything is fine | S | 50 | no | --- |
| update time on init | SL | 325 | no | only, if the time setup is active |
| initialized date time invalid | SLS | 400 | no | yes, if the time setup is active |
| RTC write protected | SLLS | 650 | no | yes, if the time setup is active |
| RTC not running | SLLLS | 825 | no | yes, if the time setup is active |
| date time on runtime invalid | SS | 125 | no | no |
| MP3 module error | LSSS | 475 | yes | no |