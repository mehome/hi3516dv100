################################################################################
#    x86/src/zlib
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
BUILD_DIR      := $(PREFIX)/tmp
STRIP          := strip
ZLIB           := zlib-1.2.7
################################################################################

all: $(BUILD_DIR)/lib/libz.a

$(BUILD_DIR)/lib/libz.a: \
    $(BUILD_DIR)/$(ZLIB)/tar
	cd $(BUILD_DIR)/$(ZLIB) && \
		./configure --prefix="$(BUILD_DIR)" && \
		make -j 16 CC=gcc && \
		make install CC=gcc && \
	cd -

################################################################################

clean:
	@test ! -d $(BUILD_DIR) || rm -rfv $(BUILD_DIR)

distclean: clean

$(BUILD_DIR)/%/tar:
	@test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	@touch $@

################################################################################
.PHONY: clean distclean all
################################################################################
