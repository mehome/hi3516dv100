################################################################################
#    ./udev/Makefile
#    Create By CaiZhiYong
#    2011.06.19
################################################################################
# PREFIX        - rootfs path
# OSDRV_CROSS - cross compile tools
################################################################################
PREFIX         ?= $(shell pwd)/rootfs
OSDRV_CROSS ?= arm-hisiv300-linux
OSDRV_CROSS_CFLAGS ?=-mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4
#CONFIG_MINI_ROOTFS    ?= n

#
#  define   - package statically linked.
#  undefine - package default linked.
#
STATIC_LINKED   =
################################################################################
BUILD_DIR      := $(shell pwd)/tmp
HOST           := $(patsubst %-,%,$(OSDRV_CROSS))
STRIP          := $(OSDRV_CROSS)strip
UDEV           := udev-164
TARGETS        := udevd udevadm

################################################################################
all: $(addprefix $(PREFIX)/bin/,$(TARGETS)) \
    $(PREFIX)/etc/udev/udev.conf

$(PREFIX)/bin/%: $(BUILD_DIR)/$(UDEV)/%
	@test -d $(@D) || mkdir -p $(@D)
	@install -v -t $(@D) $<

$(PREFIX)/etc/udev/udev.conf:
	tar -xjf rootfs.tar.bz2 -C $(patsubst %/rootfs,%,$(PREFIX))

$(addprefix $(BUILD_DIR)/$(UDEV)/,$(TARGETS)): $(BUILD_DIR)/$(UDEV)/tar
	cd $(BUILD_DIR)/$(UDEV) && ./configure --prefix=/ --host=$(HOST) CFLAGS="$(OSDRV_CROSS_CFLAGS)"\
		LDFLAGS="$(OSDRV_CROSS_CFLAGS)" --disable-extras --disable-introspection &>/dev/null; 
	make -C $(BUILD_DIR)/$(UDEV) \
		USE_STATIC=$(if $(STATIC_LINKED),true,false)\
		OSDRV_CROSS=${OSDRV_CROSS} &>/dev/null
	@cp $(BUILD_DIR)/$(UDEV)/udev/udevd $(BUILD_DIR)/$(UDEV)
	@cp $(BUILD_DIR)/$(UDEV)/udev/udevadm $(BUILD_DIR)/$(UDEV)

################################################################################

$(BUILD_DIR)/%/tar:
	test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	@touch $@

################################################################################

clean:
	@test ! -d $(BUILD_DIR) || rm -rf $(BUILD_DIR)
	@(for ix in $(TARGETS); do \
		test ! -e $(PREFIX)/bin/$$ix || rm -rf $(PREFIX)/bin/$$ix; \
		test ! -e $(PREFIX) || rm -rf $(PREFIX); \
	done)

menuconfig:
	@echo "not support"

distclean: clean

install:
	@echo "not support"

################################################################################
.PHONY: clean menuconfig distclean install
################################################################################
