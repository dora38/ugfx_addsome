/*
 * Copyright (c) 2015 dora38
 *
 * MIT License: http://opensource.org/licenses/MIT
 *
 */

#include "gfx.h"

#if GFX_USE_GDISP

#define GDISP_DRIVER_VMT			GDISPVMT_ILI9163
#include "drivers/gdisp/ILI9163/gdisp_lld_config.h"
#include "src/gdisp/gdisp_driver.h"
#include "board_ILI9163.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_WIDTH
	#define GDISP_SCREEN_WIDTH		128
#endif
#ifndef GDISP_SCREEN_HEIGHT
	#define GDISP_SCREEN_HEIGHT		160
#endif
#ifndef GDISP_LLD_ILI9163_HEIGHT_OFFSET
	#define GDISP_LLD_ILI9163_HEIGHT_OFFSET	0
#endif
#ifndef GDISP_LLD_ILI9163_HEIGHT_OFFSET
	#define GDISP_LLD_ILI9163_HEIGHT_OFFSET	0
#endif
#if GDISP_LLD_ILI9163_BGR_PANEL
	#define GDISP_LLD_ILI9163_PANEL_MODE	0x08
#else
	#define GDISP_LLD_ILI9163_PANEL_MODE	0x00
#endif
#ifndef GDISP_INITIAL_CONTRAST
	#define GDISP_INITIAL_CONTRAST	50
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
	#define GDISP_INITIAL_BACKLIGHT	100
#endif

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static inline void write_cmd_data(GDisplay * g, uint8_t cmd, uint8_t data) {
	write_cmd(g, cmd);
	write_data(g, data);
}

static inline void set_viewport(GDisplay* g) {
	uint16_t buf[2];

	// set column address
	write_cmd(g, 0x2a);
	buf[0] = to_spiform16(g->p.x);
	buf[1] = to_spiform16(g->p.x + g->p.cx - 1);
	write_ndata(g, sizeof(buf), (uint8_t *)buf);

	// set row address
	write_cmd(g, 0x2b);
	buf[0] = to_spiform16(g->p.y + GDISP_LLD_ILI9163_HEIGHT_OFFSET);
	buf[1] = to_spiform16(g->p.y + GDISP_LLD_ILI9163_HEIGHT_OFFSET + g->p.cy - 1);
	write_ndata(g, sizeof(buf), (uint8_t *)buf);

	// memory write
	write_cmd(g, 0x2c);
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC bool_t gdisp_lld_init(GDisplay *g) {
	// No private area for this controller
	g->priv = 0;

	// Initialise the board interface
	init_board(g);

	// Hardware reset
	setpin_reset(g, TRUE);
	gfxSleepMilliseconds(2);
	setpin_reset(g, FALSE);
	gfxSleepMilliseconds(10);

	// Get the bus for the following initialisation commands
	acquire_bus(g);

	/* Start Initial Sequence ----------------------------------------------------*/
	write_cmd(g, 0x01);				// software reset
	gfxSleepMilliseconds(150);		// wait at least 120ms
	write_cmd(g, 0x11);				// exit sleep mode
	gfxSleepMilliseconds(10);		// wait at least 5ms
	write_cmd_data(g, 0x36, (GDISP_LLD_ILI9163_PANEL_MODE));	// RGB/BGR
	write_cmd_data(g, 0x3A, 0x05);	// pixel format = 16bit
	write_cmd_data(g, 0x26, 0x04);	// gamma curve = 3
	write_cmd(g, 0x13);				// enter normal mode
	write_cmd(g, 0x29);				// set display on

    // Finish Init
    post_init_board(g);

 	// Release the bus
	release_bus(g);

	/* Turn on the backlight */
	set_backlight(g, GDISP_INITIAL_BACKLIGHT);

	/* Initialise the GDISP structure */
	g->g.Width = GDISP_SCREEN_WIDTH;
	g->g.Height = GDISP_SCREEN_HEIGHT;
	g->g.Orientation = GDISP_ROTATE_0;
	g->g.Powermode = powerOn;
	g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
	g->g.Contrast = GDISP_INITIAL_CONTRAST;
	return TRUE;
}

#if GDISP_HARDWARE_STREAM_WRITE
LLDSPEC	void gdisp_lld_write_start(GDisplay *g) {
	acquire_bus(g);
	set_viewport(g);
}

LLDSPEC	void gdisp_lld_write_color(GDisplay *g) {
	uint16_t buf[1];
	buf[0] = to_spiform16(gdispColor2Native(g->p.color));
	write_ndata(g, sizeof(buf), (uint8_t *)buf);
}

LLDSPEC	void gdisp_lld_write_stop(GDisplay *g) {
	release_bus(g);
}
#endif

#endif /* GFX_USE_GDISP */
