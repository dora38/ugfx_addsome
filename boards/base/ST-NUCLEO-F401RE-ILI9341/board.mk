BOARDBASE= $(GFXLIB)/boards/base/ST-NUCLEO-F401RE-ILI9341
GFXINC  += $(BOARDBASE)
GFXSRC  += $(BOARDBASE)/bus_mutex.c
GFXDEFS += -DGFX_USE_OS_CHIBIOS=TRUE
include $(BOARDBASE)/chibios_board/board.mk
include $(GFXLIB)/drivers/gdisp/ILI9341/driver.mk
include $(GFXLIB)/drivers/ginput/touch/MCU/driver.mk
