GFXINC  += $(GFXLIB)/boards/base/STM32F030F4_V2.00-ILI9163
GFXSRC  +=
GFXDEFS += -DGFX_USE_OS_CHIBIOS=TRUE
include $(GFXLIB)/boards/base/STM32F030F4_V2.00-ILI9163/chibios_board/board.mk
include $(GFXLIB)/drivers/gdisp/ILI9163/driver.mk
