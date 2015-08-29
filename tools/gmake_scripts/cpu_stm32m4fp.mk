#
# This file is subject to the terms of the GFX License. If a copy of
# the license was not distributed with this file, you can obtain one at:
#
#             http://ugfx.org/license.html
#

#
# See readme.txt for the make API
#

# Requirements:
#
# NONE
#

SRCFLAGS += -mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -fsingle-precision-constant -falign-functions=16
LDFLAGS  += -mcpu=cortex-m4 -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -fsingle-precision-constant -falign-functions=16
DEFS     += CORTEX_USE_FPU=TRUE
LIBS     += m

