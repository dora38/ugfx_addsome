# Possible Targets:	all clean Debug cleanDebug Release cleanRelease

##############################################################################################
# Settings
#

# General settings
	# See $(GFXLIB)/tools/gmake_scripts/readme.txt for the list of variables
	OPT_OS					= chibios
	OPT_THUMB				= yes
	OPT_LINK_OPTIMIZE		= yes
	OPT_CPU					= stm32m0

# uGFX settings
	# See $(GFXLIB)/tools/gmake_scripts/library_ugfx.mk for the list of variables
	GFXLIB					= /path/to/ugfx
	GFXBOARD				= STM32F030F4_V2.00-ILI9163
	GFXDEMO					= modules/gdisp/circles
#	GFXDEMO					= modules/gdisp/polygons

# ChibiOS settings
ifeq ($(OPT_OS),chibios)
	# See $(GFXLIB)/tools/gmake_scripts/os_chibios_x.mk for the list of variables
	CHIBIOS					= /path/to/ChibiOS3
	CHIBIOS_VERSION			= 3
	CHIBIOS_CPUCLASS    	= ARMCMx
	CHIBIOS_PLATFORM		= STM32
	CHIBIOS_DEVICE_FAMILY	= STM32F0xx
	CHIBIOS_STARTUP			= startup_stm32f0xx
	CHIBIOS_PORT			= v6m
	CHIBIOS_LDSCRIPT		= STM32F030x4.ld
	# We define a non standard board script as this is not a standard ChibiOS supported board
	include $(GFXLIB)/boards/base/$(GFXBOARD)/ChibiOS_Board/board.mk
endif

##############################################################################################
# Set these for your project
#

ARCH     = arm-none-eabi-
SRCFLAGS = -ggdb -Os
CFLAGS   =
CXXFLAGS = -fno-rtti
ASFLAGS  =
LDFLAGS  =

SRC      =
OBJS     =
DEFS     =
LIBS     =
INCPATH  = $(GFXLIB)/boards/base/$(GFXBOARD)/example_chibios_3.x
LIBPATH  =
LDSCRIPT =

##############################################################################################
# These should be at the end
#

include $(GFXLIB)/tools/gmake_scripts/library_ugfx.mk
include $(GFXLIB)/tools/gmake_scripts/os_$(OPT_OS).mk
include $(GFXLIB)/tools/gmake_scripts/compiler_gcc.mk
# *** EOF ***
