# Possible Targets:	all clean Debug cleanDebug Release cleanRelease

##############################################################################################
# Settings
#

# General settings
	# See $(GFXLIB)/tools/gmake_scripts/readme.txt for the list of variables
	OPT_OS					= chibios
	OPT_THUMB				= yes
	OPT_LINK_OPTIMIZE		= yes
	OPT_CPU					= stm32m4

# uGFX settings
	# See $(GFXLIB)/tools/gmake_scripts/library_ugfx.mk for the list of variables
	GFXLIB					= /path/to/ugfx_addsome
	GFXBOARD				= ST-NUCLEO-F401RE-ILI9163
	GFXDEMO					= modules/gdisp/circles

# ChibiOS settings
ifeq ($(OPT_OS),chibios)
	# See $(GFXLIB)/tools/gmake_scripts/os_chibios.mk for the list of variables
	CHIBIOS				= /path/to/ChibiOS3
	CHIBIOS_VERSION		= 3
	CHIBIOS_BOARD		= 
	CHIBIOS_CPUCLASS    = ARMCMx
	CHIBIOS_PLATFORM	= STM32/STM32F4xx
	CHIBIOS_PORT		= v7m
	CHIBIOS_LDSCRIPT	= STM32F401xE.ld
	# We define a non standard board script as this is not a standard ChibiOS supported board
	include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/startup_stm32f4xx.mk
	include $(GFXLIB)/boards/base/$(GFXBOARD)/ChibiOS_Board/board.mk
endif

##############################################################################################
# Set these for your project
#

ARCH     = arm-none-eabi-
SRCFLAGS = -ggdb -O2
CFLAGS   =
CXXFLAGS = -fno-rtti
ASFLAGS  =
LDFLAGS  =

SRC      = $(STARTUPSRC) $(STARTUPASM)
OBJS     =
DEFS     =
LIBS     =
INCPATH  = $(STARTUPINC)
LIBPATH  =
LDSCRIPT = $(STARTUPLD)/$(CHIBIOS_LDSCRIPT)

##############################################################################################
# These should be at the end
#

include $(GFXLIB)/tools/gmake_scripts/library_ugfx.mk
include $(GFXLIB)/tools/gmake_scripts/os_$(OPT_OS).mk
include $(GFXLIB)/tools/gmake_scripts/compiler_gcc.mk
# *** EOF ***
