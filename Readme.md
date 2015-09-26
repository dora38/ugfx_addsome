# ugfx_addsome

a fork and some extension of µGFX.

## Description

µGFX is an embedded library for Displays and Touchscreens.  
ugfx_addsome is a fork of that for my extension, adding some other display drivers.

Upstream's Web site: [http://ugfx.org/](http://ugfx.org/)  
Upstream's Git repository: [https://bitbucket.org/Tectu/ugfx](https://bitbucket.org/Tectu/ugfx)

## Added display drivers

* 1.44' SPI 128*128 V1.1 LCD -- ILI9163
    Sample program runs on STM32 NUCLEO-F401RE + 1.44 inch 128x128 color LCD panel.  
    For more detail, see [/boards/base/ST-NUCLEO-F401RE-ILI9163/Readme.md](boards/base/ST-NUCLEO-F401RE-ILI9163/Readme.md).

    Running in another Cortex-M0 board, STM32F030F4-V2.00.  
    For more detail, see [/boards/base/STM32F030F4_V2.00-ILI9163/Readme.md](boards/base/STM32F030F4_V2.00-ILI9163/Readme.md).

* 2.4" TFT LCD SHIELD -- ILI9341
    Sample program runs on STM32 NUCLEO-F401RE + 2.4 inch 240x320 color LCD panel.
    For more detail, see [/boards/base/ST-NUCLEO-F401RE-ILI9341/Readme.md](boards/base/ST-NUCLEO-F401RE-ILI9341/Readme.md).

## Author

dora38 [https://github.com/dora38](https://github.com/dora38)

## License

Upstream's license is applied for Upstream's codes.  
µGFX's license: [http://ugfx.org/license.html](http://ugfx.org/license.html)

MIT license is applied for my extension.  
MIT license: [http://opensource.org/licenses/MIT](http://opensource.org/licenses/MIT)

Sample programs run on ChibiOS v3.  
Some source modules derived from ChibiOS are also added here.

ChibiOS: [http://www.chibios.org](http://www.chibios.org)  
ChibiOS's license: [http://www.chibios.org/dokuwiki/doku.php?id=chibios:licensing:start](http://www.chibios.org/dokuwiki/doku.php?id=chibios:licensing:start)

Copyright (c) 2015 dora38
