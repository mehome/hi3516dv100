TOOLS_TOP_DIR ?= $(shell pwd)
TOOL_TAR_BALL := e2fsprogs-1.41.11.tar.gz
TOOL_NAME := e2fsprogs-1.41.11
TOOL_BIN := bin
OSDRV_CROSS ?= arm-hisiv300-linux
OSDRV_CROSS_CFLAGS ?= -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4

all:
	-rm $(TOOLS_TOP_DIR)/$(TOOL_NAME) -rf;
	tar -xzf $(TOOL_TAR_BALL);
	mkdir -p $(TOOLS_TOP_DIR)/$(TOOL_NAME)/$(TOOL_BIN)/;
	mkdir -p $(TOOLS_TOP_DIR)/$(TOOL_BIN)/;
	pushd $(TOOLS_TOP_DIR)/$(TOOL_NAME)/; \
		./configure --host=$(OSDRV_CROSS) CFLAGS="$(OSDRV_CROSS_CFLAGS)" \
		LDFLAGS="$(OSDRV_CROSS_CFLAGS)" --prefix=$(TOOLS_TOP_DIR)/$(TOOL_NAME)/$(TOOL_BIN) \
		--disable-tls > /dev/null; \
		make -j 20 > /dev/null; \
		make install  > /dev/null; \
		cp $(TOOL_BIN)/sbin/mkfs.ext2 $(TOOLS_TOP_DIR)/$(TOOL_BIN) -rf; \
		cp $(TOOL_BIN)/sbin/mkfs.ext3 $(TOOLS_TOP_DIR)/$(TOOL_BIN) -rf; \
		cp $(TOOL_BIN)/sbin/mkfs.ext4 $(TOOLS_TOP_DIR)/$(TOOL_BIN) -rf; \
		cp $(TOOL_BIN)/sbin/mke2fs $(TOOLS_TOP_DIR)/$(TOOL_BIN) -rf; \
	popd
.PHONY: clean

	-pushd $(TOOLS_TOP_DIR)/$(TOOL_NAME)/ &&\
	make -C $(TOOLS_TOP_DIR)/$(TOOL_NAME)/ clean && \
	popd

.PHONY: distclean
distclean:
	-rm $(TOOLS_TOP_DIR)/$(TOOL_NAME) -rf;
	-rm $(TOOLS_TOP_DIR)/$(TOOL_BIN) -rf;

