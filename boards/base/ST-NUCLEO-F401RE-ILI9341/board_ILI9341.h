/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#define ILI9341_MAGIC_SETTING		FALSE
#define ILI9341_POWERCTL1_PARAM		0x23
#define ILI9341_POWERCTL2_PARAM		0x10
#define ILI9341_VCOMCTL1_PARAM		0x2b2b
#define ILI9341_VCOMCTL2_PARAM		0xc0
#define ILI9341_MEMACCESS_PARAM		0x48	// MX, BGR
#define ILI9341_PIXFORMATSET_PARAM	0x55	// RGB565
#define ILI9341_DISPLAY_INVERSION	TRUE
#define ILI9341_3GAMMA_SETTING		FALSE

#define SET_RST   palSetPad(GPIOC, GPIOC_LCD_RST)
#define CLR_RST   palClearPad(GPIOC, GPIOC_LCD_RST)
#define SET_CS    palSetPad(GPIOB, GPIOB_LCD_CS)
#define CLR_CS    palClearPad(GPIOB, GPIOB_LCD_CS)
#define SET_RS    palSetPad(GPIOA, GPIOA_LCD_RS)
#define CLR_RS    palClearPad(GPIOA, GPIOA_LCD_RS)
#define SET_WR    palSetPad(GPIOA, GPIOA_LCD_WR)
#define CLR_WR    palClearPad(GPIOA, GPIOA_LCD_WR)
#define SET_RD    palSetPad(GPIOA, GPIOA_LCD_RD)
#define CLR_RD    palClearPad(GPIOA, GPIOA_LCD_RD)

extern gfxMutex bus_mutex;

static inline void init_board(GDisplay *g) {
	g->board = 0;
	gfxMutexInit(&bus_mutex);
}

static inline void post_init_board(GDisplay *g) {
	(void) g;
}

static inline void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;
	if(state) {
		CLR_RST;
	} else {
		SET_RST;
	}
}

static inline void set_backlight(GDisplay *g, uint8_t percent) {
	(void) g;
	(void) percent;
}

static inline void acquire_bus(GDisplay *g) {
	(void) g;
	gfxMutexEnter(&bus_mutex);
	CLR_CS;
}

static inline void release_bus(GDisplay *g) {
	(void) g;
	SET_CS;
	gfxMutexExit(&bus_mutex);
}

/**
 * @brief   Short delay
 *
 * @param[in] dly		Length of delay
 *
 * @notapi
 */
static inline void ili9341_delay(uint16_t dly) {
  static uint16_t i;
  for(i = 0; i < dly; i++)
    asm("nop");
}

static inline void write_data(GDisplay *g, uint16_t data) {
	(void) g;
	CLR_WR;
	palWritePad(GPIOA, GPIOA_LCD_D0, (data & 0x01) != 0);
	palWritePad(GPIOC, GPIOC_LCD_D1, (data & 0x02) != 0);
	palWritePad(GPIOA, GPIOA_LCD_D2, (data & 0x04) != 0);
	palWritePad(GPIOB, GPIOB_LCD_D3, (data & 0x08) != 0);
	palWritePad(GPIOB, GPIOB_LCD_D4, (data & 0x10) != 0);
	palWritePad(GPIOB, GPIOB_LCD_D5, (data & 0x20) != 0);
	palWritePad(GPIOB, GPIOB_LCD_D6, (data & 0x40) != 0);
	palWritePad(GPIOA, GPIOA_LCD_D7, (data & 0x80) != 0);
	//ili9341_delay(5);
	SET_WR;
	//ili9341_delay(5);
}

static inline void write_index(GDisplay *g, uint16_t index) {
	(void) g;
	CLR_RS;
	write_data(g, index);
	SET_RS;
}

static inline void setreadmode(GDisplay *g) {
	(void) g;
	palSetGroupMode(GPIOA, PAL_PORT_BIT(8) | PAL_PORT_BIT(9) | PAL_PORT_BIT(10), 0, PAL_MODE_INPUT | PAL_STM32_OSPEED_HIGHEST);
	palSetGroupMode(GPIOB, PAL_PORT_BIT(3) | PAL_PORT_BIT(4) | PAL_PORT_BIT(5) | PAL_PORT_BIT(10), 0, PAL_MODE_INPUT | PAL_STM32_OSPEED_HIGHEST);
	palSetGroupMode(GPIOC, PAL_PORT_BIT(7), 0, PAL_MODE_INPUT | PAL_STM32_OSPEED_HIGHEST);
}

static inline void setwritemode(GDisplay *g) {
	(void) g;
	palSetGroupMode(GPIOA, PAL_PORT_BIT(8) | PAL_PORT_BIT(9) | PAL_PORT_BIT(10), 0, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetGroupMode(GPIOB, PAL_PORT_BIT(3) | PAL_PORT_BIT(4) | PAL_PORT_BIT(5) | PAL_PORT_BIT(10), 0, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetGroupMode(GPIOC, PAL_PORT_BIT(7), 0, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
}

static inline uint16_t read_data(GDisplay *g) {
	uint16_t	value = 0;
	uint16_t	porta, portb, portc;
	(void) g;
	CLR_RD;
	ili9341_delay(20);
	porta = palReadPort(GPIOA);
	portb = palReadPort(GPIOB);
	portc = palReadPort(GPIOC);
	SET_RD;

	if (porta & PAL_PORT_BIT(GPIOA_LCD_D0)) {
		value |= 0x01;
	}
	if (portc & PAL_PORT_BIT(GPIOC_LCD_D1)) {
		value |= 0x02;
	}
	if (porta & PAL_PORT_BIT(GPIOA_LCD_D2)) {
		value |= 0x04;
	}
	if (portb & PAL_PORT_BIT(GPIOB_LCD_D3)) {
		value |= 0x08;
	}
	if (portb & PAL_PORT_BIT(GPIOB_LCD_D4)) {
		value |= 0x10;
	}
	if (portb & PAL_PORT_BIT(GPIOB_LCD_D5)) {
		value |= 0x20;
	}
	if (portb & PAL_PORT_BIT(GPIOB_LCD_D6)) {
		value |= 0x40;
	}
	if (porta & PAL_PORT_BIT(GPIOA_LCD_D7)) {
		value |= 0x80;
	}
	return value;
}

#endif /* _GDISP_LLD_BOARD_H */
