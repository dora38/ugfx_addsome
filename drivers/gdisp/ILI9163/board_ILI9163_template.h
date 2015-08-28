/*
 * Copyright (c) 2015 dora38
 *
 * MIT License: http://opensource.org/licenses/MIT
 *
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#define GDISP_SCREEN_WIDTH					128
#define GDISP_SCREEN_HEIGHT					160
#define GDISP_LLD_ILI9163_HEIGHT_OFFSET		0
#define GDISP_LLD_ILI9163_BGR_PANEL			FALSE

static inline void init_board(GDisplay *g) {
	(void) g;
}

static inline void post_init_board(GDisplay *g) {
	(void) g;
}

static inline void setpin_reset(GDisplay *g, bool_t state) {
	(void) g;
	(void) state;
}

static inline void set_backlight(GDisplay *g, uint8_t percent) {
	(void) g;
	(void) percent;
}

static inline void acquire_bus(GDisplay *g) {
	(void) g;
}

static inline void release_bus(GDisplay *g) {
	(void) g;
}

static inline void write_cmd(GDisplay *g, uint8_t cmd) {
	(void) g;
	(void) cmd;
}

static inline void write_data(GDisplay *g, uint8_t data) {
	(void) g;
	(void) data;
}

static inline void write_ndata(GDisplay *g, size_t n, uint8_t *p) {
	(void) g;
	(void) n;
	(void) p;
}

static inline uint16_t to_spiform16(uint16_t n) {
	// ILI9163 requires big endian byte order.
	return n;
}

#endif /* _GDISP_LLD_BOARD_H */
