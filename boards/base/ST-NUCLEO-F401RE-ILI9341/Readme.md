# A sample of 2.4 inch TFT LCD Shield -- ILI9341 240x320 color LCD panel

![NUCLEO-F401RE+TFT LCD Shield](http://i.imgur.com/x3UjkOP.jpg)

This sample programs runs on STM32 NUCLEO-F401RE and ChibiOS v3.

## Requirement

* STM32 NUCLEO-F401RE board
* 2.4 inch TFT LCD Shield. It seems several kinds of "LCD Sheild" are present in the world.
  This is: 
    * labeled '2.4" TFT LCD SHIELD' back on the PCB
    * labeled 'S241GF31' back on the LCD
    * ILI9341 or compatible LCD controller. (though the controller ID could not be read)
* ChibiOS v3 source code
* STM32 GCC cross-compile environment
* µGFX build knowledge

## Build

1. git clone the ugfx_addsome repository
2. Download and unzip the ChibiOS v3 source code
3. Edit /boards/base/ST-NUCLEO-F401RE-ILI9341/example_chibios_3.x/Makefile:
    * `GFXLIB` = ugfx_addsome directory path
    * `CHIBIOS` = ChibiOS v3 directory path
4. make

## Connect

Plug into the arduino connectors.

|    LCD    |    NUCLEO   |
|:---------:|:-----------:|
| LCD_RST   | PC1   |
| LCD_CS    | PB0   |
| LCD_RS/TOUCH_X- | PA4   |
| LCD_WR/TOUCH_Y+ | PA1   |
| LCD_RD    | PA0   |
|           |       |
| LCD_D2    | PA10  |
| LCD_D3    | PB3   |
| LCD_D4    | PB5   |
| LCD_D5    | PB4   |
| LCD_D6/TOUCH_X+ | PB10  |
| LCD_D7/TOUCH_Y- | PA8   |
|           |       |
| LCD_D0    | PA9   |
| LCD_D1    | PC7   |
|           |       |
| SD_SS     | PB6   |
| SD_DI     | PA7(MOSI) |
| SD_DO     | PA6(MISO) |
| SD_SCK    | PA5   |

## Considerations

* The LCD has 8080 type 8-bit parallel interface.
  GPIO emulation (slow) of the parallel interface has been made because
  the NUCLEO's arduino connector does not fit to FSMC pin assign,
  even if the NUCLEO has the FSMC feature.

* Note that touch screen's pins are shared with some LCD's pins.
  You should not use them at the same timing.
  A mutex exists for exclusive control.

* 16-bit RGB565 coloring mode is used.

* The LCD panel is BGR type.

Copyright (c) 2015 dora38
