GFXINC  += $(GFXLIB)/boards/base/FZ0620-STM32F103ZET6-ILI9325
GFXSRC  +=
GFXDEFS += -DGFX_USE_OS_CHIBIOS=TRUE
include $(GFXLIB)/boards/base/FZ0620-STM32F103ZET6-ILI9325/chibios_board/board.mk
include $(GFXLIB)/drivers/gdisp/ILI93xx/driver.mk
include $(GFXLIB)/drivers/ginput/touch/ADS7843/driver.mk
