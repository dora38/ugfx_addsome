/*
 * Copyright (c) 2015 dora38
 *
 * MIT License: http://opensource.org/licenses/MIT
 *
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#define GDISP_SCREEN_WIDTH					128
#define GDISP_SCREEN_HEIGHT					128
#define GDISP_LLD_ILI9163_HEIGHT_OFFSET		32
#define GDISP_LLD_ILI9163_BGR_PANEL			TRUE

#define LCD_PORT	GPIOA
#define LCD_NSS		GPIOA_PIN4
#define LCD_DATA	GPIOA_PIN2
#define LCD_NRESET	GPIOA_PIN3

/**
 * SPI configuration structure.
 * SPI clock = 48MHz / 4 = 12MHz
 */
static const SPIConfig spi1cfg = {
		NULL,
		LCD_PORT,
		LCD_NSS,
		SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_0,
		SPI_CR2_FRXTH | SPI_CR2_SSOE | SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0
};

static inline void init_board(GDisplay *g) {
	g->board = 0;
	spiStart(&SPID1, &spi1cfg);
}

static inline void post_init_board(GDisplay *g) {
	(void) g;
}

static inline void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;
	if (state) {
		palClearPad(LCD_PORT, LCD_NRESET);
	} else {
		palSetPad(LCD_PORT, LCD_NRESET);
	}
}

static inline void set_backlight(GDisplay *g, uint8_t percent) {
	(void) g;
	(void) percent;
}

static inline void acquire_bus(GDisplay *g) {
	(void) g;
	spiSelect(&SPID1);
}

static inline void release_bus(GDisplay *g) {
	(void) g;
	spiUnselect(&SPID1);
}

static inline void write_cmd(GDisplay *g, uint8_t cmd) {
	(void) g;
	palClearPad(LCD_PORT, LCD_DATA);
	spiSend(&SPID1, 1, &cmd);
	palSetPad(LCD_PORT, LCD_DATA);
}

static inline void write_data(GDisplay *g, uint8_t data) {
	(void) g;
	spiSend(&SPID1, 1, &data);
}

static inline void write_ndata(GDisplay *g, size_t n, uint8_t *p) {
	(void) g;
	spiSend(&SPID1, n, p);
}

static inline uint16_t to_spiform16(uint16_t n) {
	// ILI9163 requires big endian byte order. STM32 is in little endian.
	return (n << 8) | (n >> 8);
}

#endif /* _GDISP_LLD_BOARD_H */
