#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the FZ0620, a board of STM32F103ZET6 with LCD.
 */

/*
 * Board identifier.
 */
#define BOARD_FZ0620_STM32_F103
#define BOARD_NAME              "FZ0620-STM32F103ZET6"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            32768
#define STM32_HSECLK            8000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_HD

/*
 * IO pins assignments.
 */

#define GPIOA_UART1_TX  9       /* USART1 TX pin */
#define GPIOA_UART1_RX  10      /* USART1 RX pin */
#define GPIOA_UART2_TX  2       /* USART2 TX pin */
#define GPIOA_UART2_RX  3       /* USART2 RX pin */

#define GPIOE_LED2      2       /* lighting on 0 */
#define GPIOE_LED3      0       /* lighting on 0 */
#define GPIOB_KEY1      10      /* GND while push. no external pull-up */
#define GPIOB_KEY2      11      /* GND while push. no external pull-up */

#define GPIOE_TFT_RST   1       /* LCD reset (active low) */
#define GPIOD_TFT_LIGHT 13      /* LCD backlight (bright while low) */

#define GPIOB_LCDTP_CS  7       /* LCD touch pad chip select */
#define GPIOB_LCDTP_IRQ 6       /* LCD touch pad interrupt request */
#define GPIOA_LCDTP_SCK 5       /* LCD touch pad SPI1 clock */
#define GPIOA_LCDTP_MISO 6      /* LCD touch pad SPI1 MISO */
#define GPIOA_LCDTP_MOSI 7      /* LCD touch pad SPI1 MOSI */

#define GPIOC_SDIO_D0   8       /* SD card D0 */
#define GPIOC_SDIO_D1   9       /* SD card D1 */
#define GPIOC_SDIO_D2   10      /* SD card D2 */
#define GPIOC_SDIO_D3   11      /* SD card D3 */
#define GPIOC_SDIO_CK   12      /* SD card CLK */
#define GPIOD_SDIO_CMD  2       /* SD card CMD */

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
 * Everything analog input except:
 * PA2  - Alternate output  (USART2 TX).
 * PA3  - Normal input w/PU (USART2 RX).
 * PA5  - Alternate P/P out (SPI1 SCK).
 * PA6  - Input floating    (SPI1 MISO).
 * PA7  - Alternate P/P out (SPI1 MOSI).
 * PA9  - Alternate output  (USART1 TX).
 * PA10 - Normal input w/PU (USART1 RX).
 */
#define VAL_GPIOACRL            0xB4B08B00      /*  PA7...PA0 (4 bits per port) */
#define VAL_GPIOACRH            0x000008B0      /* PA15...PA8 (4 bits per port) */
#define VAL_GPIOAODR            0x060c          /* PA15...PA0 (1 bit per port) */

/*
 * Port B setup.
 * Everything analog input except:
 * PB6  - Normal input w/PU (LCD TP IRQ)
 * PB7  - Push Pull output  (LCD TP CS)
 * PB10 - Normal input w/PU (KEY1).
 * PB11 - Normal input w/PU (KEY2).
 */
#define VAL_GPIOBCRL            0x38000000      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x00008800      /* PB15...PB8 */
#define VAL_GPIOBODR            0x0CC0

/*
 * Port C setup.
 * Everything analog input except:
 * PC8  - Alternate P/P out (SDIO_D0).
 * PC9  - Alternate P/P out (SDIO_D1).
 * PC10 - Alternate P/P out (SDIO_D2).
 * PC11 - Alternate P/P out (SDIO_D3).
 * PC12 - Alternate P/P out (SDIO_CK).
 */
#define VAL_GPIOCCRL            0x00000000      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x000BBBBB      /* PC15...PC8 */
#define VAL_GPIOCODR            0x0000

/*
 * Port D setup.
 * Everything analog input except:
 * PD0  - Alternate P/P out (FSMC_D2).
 * PD1  - Alternate P/P out (FSMC_D3).
 * PD2  - Alternate P/P out (SDIO_CMD).
 * PD4  - Alternate P/P out (FSMC_NOE).
 * PD5  - Alternate P/P out (FSMC_NWE).
 * PD7  - Alternate P/P out (FSMC_NE1).
 * PD8  - Alternate P/P out (FSMC_D13).
 * PD9  - Alternate P/P out (FSMC_D14).
 * PD10 - Alternate P/P out (FSMC_D15).
 * PD11 - Alternate P/P out (FSMC_A16).
 * PD13 - Open drain output (LCD backlight).
 * PD14 - Alternate P/P out (FSMC_D0).
 * PD15 - Alternate P/P out (FSMC_D1).
 */
#define VAL_GPIODCRL            0xB0BB0BBB      /*  PD7...PD0 */
#define VAL_GPIODCRH            0xBB70BBBB      /* PD15...PD8 */
#define VAL_GPIODODR            0x2000

/*
 * Port E setup.
 * Everything analog input except:
 * PE0  - Push Pull output  (LED3).
 * PE1  - Push Pull output  (LCD reset).
 * PE2  - Push Pull output  (LED2).
 * PE7  - Alternate P/P out (FSMC_D4).
 * PE8  - Alternate P/P out (FSMC_D5).
 * PE9  - Alternate P/P out (FSMC_D6).
 * PE10 - Alternate P/P out (FSMC_D7).
 * PE11 - Alternate P/P out (FSMC_D8).
 * PE12 - Alternate P/P out (FSMC_D9).
 * PE13 - Alternate P/P out (FSMC_D10).
 * PE14 - Alternate P/P out (FSMC_D11).
 * PE15 - Alternate P/P out (FSMC_D12).
 */
#define VAL_GPIOECRL            0xB0000333      /*  PE7...PE0 */
#define VAL_GPIOECRH            0xBBBBBBBB      /* PE15...PE8 */
#define VAL_GPIOEODR            0x0007

/*
 * Port F setup.
 * Everything analog input except:
 */
#define VAL_GPIOFCRL            0x00000000      /*  PF7...PF0 */
#define VAL_GPIOFCRH            0x00000000      /* PF15...PF8 */
#define VAL_GPIOFODR            0x0000

/*
 * Port G setup.
 * Everything analog input except:
 */
#define VAL_GPIOGCRL            0x00000000      /*  PG7...PG0 */
#define VAL_GPIOGCRH            0x00000000      /* PG15...PG8 */
#define VAL_GPIOGODR            0x0000

#if 0
/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp) palClearPad(GPIOC, GPIOC_USB_DISC)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp) palSetPad(GPIOC, GPIOC_USB_DISC)
#endif /* 0 */

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
