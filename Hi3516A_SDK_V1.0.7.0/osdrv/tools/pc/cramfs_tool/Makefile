###############################################################################
#    x86/src/cramfs
#    Create By CaiZhiYong
#    2011.01.16
###############################################################################
# parameter
PREFIX         ?= $(shell pwd)

###############################################################################
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
ZLIB           := $(shell pwd)/../zlib
ZLIB_INSTALL   := $(PREFIX)/../zlib
ZLIB_DIR       := $(ZLIB_INSTALL)/tmp
STRIP          := strip
CRAMFS         := util-linux-2.22-rc2
###############################################################################

all: $(PREFIX)/mkfs.cramfs

$(PREFIX)/mkfs.cramfs: $(BUILD_DIR)/sbin/mkfs.cramfs
	@test -d $(@D) || mkdir -p $(@D)
	install -vs -t $(PREFIX) $<

$(BUILD_DIR)/sbin/mkfs.cramfs: \
    $(ZLIB_DIR)/lib/libz.a \
    $(BUILD_DIR)/$(CRAMFS)/tar
	cd $(BUILD_DIR)/$(CRAMFS) && \
		./configure --prefix="$(BUILD_DIR)" \
		 --disable-libuuid --disable-libblkid --disable-libmount \
		 --disable-mount --disable-losetup --disable-fsck \
		 --disable-partx --disable-uuidd --disable-mountpoint \
		 --disable-fallocate --disable-unshare --disable-eject \
		 --disable-agetty --disable-switch_root --disable-pivot_root \
		 --disable-kill --disable-utmpdump --disable-rename \
		 --disable-login --disable-sulogin --disable-su \
		 --disable-schedutils --disable-wall && \
		make -j 16 && \
		make install && \
	cd -

$(ZLIB_DIR)/lib/libz.a:
	@test -f $(ZLIB_DIR)/lib/libz.a || \
	make -C $(ZLIB) PREFIX=$(ZLIB_INSTALL)

###############################################################################

clean: zlib_clean
	@test ! -d $(BUILD_DIR) || rm -rfv $(BUILD_DIR)
	@test ! -e $(PREFIX)/mkfs.cramfs || rm -rfv $(PREFIX)/mkfs.cramfs

zlib_clean:
	@test ! -d $(ZLIB_DIR) || \
	make -C $(ZLIB) PREFIX=$(ZLIB_INSTALL) distclean

distclean: clean

$(BUILD_DIR)/%/tar:
	@test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	@touch $@

###############################################################################
.PHONY: clean distclean all
###############################################################################
