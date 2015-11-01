/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_TOGGLE_BOARD_H
#define _GDISP_LLD_TOGGLE_BOARD_H

#define GINPUT_TOGGLE_POLL_PERIOD		100

#define GINPUT_TOGGLE_NUM_PORTS			2			// The total number of toggle inputs
#define GINPUT_TOGGLE_CONFIG_ENTRIES	1			// The total number of GToggleConfig entries

#define GINPUT_TOGGLE_KEY1			0				// Key 1
#define GINPUT_TOGGLE_KEY2			1				// Key 2

#define GINPUT_TOGGLE_DECLARE_STRUCTURE()											\
	static const IOBus IOBUS_GPIOB = { GPIOB, 0xffff, 0 };							\
	const GToggleConfig GInputToggleConfigTable[GINPUT_TOGGLE_CONFIG_ENTRIES] = {	\
		{(void *)&IOBUS_GPIOB,				/* Key 1 and Key 2 */					\
			PAL_PORT_BIT(GPIOB_KEY1) | PAL_PORT_BIT(GPIOB_KEY2),					\
			PAL_PORT_BIT(GPIOB_KEY1) | PAL_PORT_BIT(GPIOB_KEY2),					\
			PAL_MODE_INPUT_PULLUP},													\
	}

#endif /* _GDISP_LLD_TOGGLE_BOARD_H */
