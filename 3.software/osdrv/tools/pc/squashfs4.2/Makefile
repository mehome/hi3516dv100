################################################################################
#    x86/src/squashfs
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
BUILD_DIR      := $(shell pwd)/tmp
STRIP          := strip
SQUASHFS       := squashfs4.2
XZ             := xz-5.0.4
ZLIB           := zlib-1.2.7
################################################################################

all: $(PREFIX)/mksquashfs

$(PREFIX)/mksquashfs: $(BUILD_DIR)/bin/mksquashfs
	@test -d $(@D) || mkdir -p $(@D)
	install -vs -t $(PREFIX) --strip-program=$(STRIP) $<

$(BUILD_DIR)/bin/mksquashfs: \
    $(BUILD_DIR)/lib/liblzma.a \
    $(BUILD_DIR)/lib/libz.a    \
    $(BUILD_DIR)/$(SQUASHFS)/tar
	cd $(BUILD_DIR)/$(SQUASHFS) && \
		make EXTRA_CFLAGS="-I$(BUILD_DIR)/include" \
			LDFLAGS="-L$(BUILD_DIR)/lib -static" -j 16 && \
		make INSTALL_DIR=$(BUILD_DIR)/bin install && \
	cd -

$(BUILD_DIR)/lib/liblzma.a: \
    $(BUILD_DIR)/$(XZ)/tar
	cd $(BUILD_DIR)/$(XZ) && \
		./configure --prefix="$(BUILD_DIR)" && \
		make -j 16 && \
		make install && \
	cd -

$(BUILD_DIR)/lib/libz.a: \
    $(BUILD_DIR)/$(ZLIB)/tar
	cd $(BUILD_DIR)/$(ZLIB) && \
		./configure --prefix="$(BUILD_DIR)" --static && \
		make -j 16 && \
		make install && \
	cd -

################################################################################

clean:
	@test ! -d $(BUILD_DIR) || rm -rfv $(BUILD_DIR)
	@test ! -e $(PREFIX)/mksquashfs || rm -rfv $(PREFIX)/mksquashfs

distclean: clean

$(BUILD_DIR)/%/tar:
	@test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	@touch $@

################################################################################
.PHONY: clean distclean all
################################################################################
