PROJECT = flipdot-driver
BUILD_DIR = bin

V=1

#SHARED_DIR = ../my-common-code
CFILES = main.c delay.c
#CFILES += api.c
#AFILES += api-asm.S

DEVICE=stm32f103c8tx
OOCD_INTERFACE = /usr/share/openocd/scripts/interface/stlink-v2.cfg
OOCD_FILE = stm32f103.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=./libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ./rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
