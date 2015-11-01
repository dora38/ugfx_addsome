/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

// Resolution and Accuracy Settings
#define GMOUSE_ADS7843_PEN_CALIBRATE_ERROR		8
#define GMOUSE_ADS7843_PEN_CLICK_ERROR			6
#define GMOUSE_ADS7843_PEN_MOVE_ERROR			4
#define GMOUSE_ADS7843_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_ADS7843_FINGER_CLICK_ERROR		18
#define GMOUSE_ADS7843_FINGER_MOVE_ERROR		14

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_ADS7843_BOARD_DATA_SIZE			0

static const SPIConfig spicfg = {
    0,		// callback
	GPIOB, 	// cs group
	GPIOB_LCDTP_CS,		// cs port
    /* SPI_CR1_BR_2 |*/ SPI_CR1_BR_1 | SPI_CR1_BR_0,	// cr1 register. baud rate=4.5MHz (72MHz/16)
};

static bool_t init_board(GMouse* m, unsigned driverinstance)
{
	(void)m;
	switch (driverinstance) {
	case 0:
		spiStart(&SPID1, &spicfg);
		break;
	}
	return TRUE;
}

static inline bool_t getpin_pressed(GMouse* m)
{
	(void)m;
	return (!palReadPad(GPIOB, GPIOB_LCDTP_IRQ));
}

static inline void aquire_bus(GMouse* m)
{
	(void)m;
	spiAcquireBus(&SPID1);
	spiSelect(&SPID1);
}

static inline void release_bus(GMouse* m)
{
	(void)m;
	spiUnselect(&SPID1);
	spiReleaseBus(&SPID1);
}

static inline uint16_t read_value(GMouse* m, uint16_t port)
{
	(void)m;
    static uint8_t txbuf[3] = {0};
    static uint8_t rxbuf[3] = {0};
    uint16_t ret;

    txbuf[0] = port;

    spiExchange(&SPID1, 3, txbuf, rxbuf);

    ret = (rxbuf[1] << 5) | (rxbuf[2] >> 3);

	return ret;
}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */

