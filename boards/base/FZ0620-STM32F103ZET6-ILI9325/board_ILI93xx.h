/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef GDISP_LLD_BOARD_H
#define GDISP_LLD_BOARD_H


#define GDISP_REG              (*((volatile uint16_t *) 0x60000000)) /* RS = 0 */
#define GDISP_RAM              (*((volatile uint16_t *) 0x60020000)) /* RS = 1 */

static GFXINLINE void init_board(GDisplay *g)
{
	(void) g;

	// As we are not using multiple displays we set g->board to NULL as we don't use it.
	g->board = 0;

	switch(g->controllerdisplay) {
	case 0:											// Set up for Display 0
		/* FSMC setup for F1 */
		rccEnableAHB(RCC_AHBENR_FSMCEN, 0);

		/* FSMC timing */
		//      access mode=B, DATAST=6HCLK, ADDSET=3HCLK
		FSMC_Bank1->BTCR[1] = FSMC_BTR1_ACCMOD_0 | (5 << 8) | (2 << 0);
		FSMC_Bank1->BTCR[0] = FSMC_BCR1_WREN | FSMC_BCR1_FACCEN | FSMC_BCR1_MWID_0 | FSMC_BCR1_MTYP_1 | FSMC_BCR1_MBKEN;
		break;
	}

}

static GFXINLINE void post_init_board(GDisplay *g)
{
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state)
{
	(void) g;

	/* NOTE: gdisp_lld_ILI93xx.c seems state TRUE/FALSE are inverted. so this setpin_reset() is fitted in. */
	if(state)
		palSetPad(GPIOE, GPIOE_TFT_RST);
	else
		palClearPad(GPIOE, GPIOE_TFT_RST);
}

static GFXINLINE void set_backlight(GDisplay *g, uint8_t percent)
{
	(void) g;

	if(percent)
		palClearPad(GPIOD, GPIOD_TFT_LIGHT);
	else
		palSetPad(GPIOD, GPIOD_TFT_LIGHT);
}

static GFXINLINE void acquire_bus(GDisplay *g)
{
	(void) g;
}

static GFXINLINE void release_bus(GDisplay *g)
{
	(void) g;
}

static GFXINLINE void write_index(GDisplay *g, uint16_t index)
{
	(void) g;

	GDISP_REG = index;
}

static GFXINLINE void write_data(GDisplay *g, uint16_t data)
{
	(void) g;

	GDISP_RAM = data;
}

static GFXINLINE void setreadmode(GDisplay *g)
{
	(void) g;
}

static GFXINLINE void setwritemode(GDisplay *g)
{
	(void) g;
}

static GFXINLINE uint16_t read_data(GDisplay *g)
{
	(void) g;

	return GDISP_RAM;
}

#endif /* GDISP_LLD_BOARD_H */
