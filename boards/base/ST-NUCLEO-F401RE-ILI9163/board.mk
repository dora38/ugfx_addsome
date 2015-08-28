GFXINC  += $(GFXLIB)/boards/base/ST-NUCLEO-F401RE-ILI9163
GFXSRC  +=
GFXDEFS += -DGFX_USE_OS_CHIBIOS=TRUE
include $(GFXLIB)/boards/base/ST-NUCLEO-F401RE-ILI9163/chibios_board/board.mk
include $(GFXLIB)/drivers/gdisp/ILI9163/driver.mk
