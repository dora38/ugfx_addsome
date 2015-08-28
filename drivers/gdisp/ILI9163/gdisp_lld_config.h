/*
 * Copyright (c) 2015 dora38
 *
 * MIT License: http://opensource.org/licenses/MIT
 *
 */

#ifndef _GDISP_LLD_CONFIG_H
#define _GDISP_LLD_CONFIG_H

#if GFX_USE_GDISP

/*===========================================================================*/
/* Driver hardware support.                                                  */
/*===========================================================================*/

#define GDISP_HARDWARE_STREAM_WRITE		TRUE

#define GDISP_LLD_PIXELFORMAT			GDISP_PIXELFORMAT_RGB565

#endif	/* GFX_USE_GDISP */

#endif	/* _GDISP_LLD_CONFIG_H */
