################################################################################
#    x86/src/squashfs
#    Create By CaiZhiYong
#    2011.01.16
################################################################################
# parameter
PREFIX         ?= $(shell pwd)
################################################################################
#
#  options below should be redefined here, don't use definitions in Makefile 
#  in SDK top dir.
#
CC=gcc
OBJDUMP=objdump
HOST=
CPP=
LD=
NM=

###############################################################################
BUILD_DIR      := $(PREFIX)/fastboot
STRIP          := strip
################################################################################

all: $(PREFIX)/mkimage

$(PREFIX)/mkimage: $(BUILD_DIR)/mkimage
	@test -d $(@D) || mkdir -p $(@D)
	-cp -rvf $(BUILD_DIR)/tools/mkimage $(PREFIX)

$(BUILD_DIR)/mkimage: \
    $(BUILD_DIR)/tar
	cd $(BUILD_DIR)/ && \
		make tools && \
	cd -

################################################################################

clean:
	@test ! -d $(BUILD_DIR) || rm -rfv $(BUILD_DIR)
	@test ! -e $(PREFIX)/mkimage || rm -rfv $(PREFIX)/mkimage

distclean: clean

$(BUILD_DIR)/tar:
	@test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(PREFIX)
	@touch $@

################################################################################
.PHONY: clean distclean all
################################################################################
