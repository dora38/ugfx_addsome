# A sample of ILI9163 128x128 SPI color LCD panel

![NUCLEO-F401RE+ILI9163](http://i.imgur.com/8oWQI7h.jpg)

This sample programs runs on STM32 NUCLEO-F401RE and ChibiOS v3.

## Requirement

* STM32 NUCLEO-F401RE board
* ILI9163 1.44 inch 128x128 SPI color LCD panel (I don't know the parts number. see the above photo)
* ChibiOS v3 source code
* STM32 GCC cross-compile environment
* µGFX build knowledge

## Build

1. git clone the ugfx_addsome repository
2. Download and unzip the ChibiOS v3 source code
3. Edit /boards/base/ST-NUCLEO-F401RE-ILI9163/example_chibios_3.x/Makefile:
    * `GFXLIB` = ugfx_addsome directory path
    * `CHIBIOS` = ChibiOS v3 directory path
4. make

## Connect

|    LCD     |    NUCLEO   |
|:----------:|:-----------:|
| LED        | +3v3        |
| SCK        | PA5         |
| SDA        | PA7         |
| AO         | PA0         |
| RESET      | PA1         |
| CS         | PA4         |
| GND        | GND         |
| VCC        | +5v         |

## Considerations

* Maximum SPI clock rate of ILI9163 is 15MHz.
  This sample program drives SPI1 in 10.5MHz (84MHz / 8)

* 16-bit RGB565 coloring mode is used because of performance.
  RGB666 mode can be selectable in exchange for 24-bit transfer per pixel.

* The LCD panel has 128x128 pixels, but that LCD controller is wired for 128x160 pixels.
  Top part 32-pixel area is not visible though those GRAM are writable.
  I introduced 32-pixel displacement calculation for offsetting this mismatch.

* The LCD panel is BGR type.

Copyright (c) 2015 dora38
