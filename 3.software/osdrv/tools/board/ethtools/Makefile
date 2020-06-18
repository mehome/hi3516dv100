TOOLS_TOP_DIR ?= $(shell pwd)
TOOL_TAR_BALL := ethtool_6.orig.tar.gz
TOOL_NAME := ethtool-6
TOOL_BIN := bin
OSDRV_CROSS ?= arm-hisiv300-linux
OSDRV_CROSS_CFLAGS ?= -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4

all:
	-rm $(TOOLS_TOP_DIR)/$(TOOL_NAME) -rf;
	tar -zxf $(TOOL_TAR_BALL);
	mkdir -p $(TOOLS_TOP_DIR)/$(TOOL_BIN)/;
	mkdir -p $(TOOLS_TOP_DIR)/$(TOOL_NAME)/$(TOOL_BIN)/;
	
	pushd $(TOOLS_TOP_DIR)/$(TOOL_NAME)/; \
		./configure --host=$(OSDRV_CROSS) CFLAGS="$(OSDRV_CROSS_CFLAGS)" \
		--enable-static --disable-shared \
		--prefix=$(TOOLS_TOP_DIR)/$(TOOL_NAME)/$(TOOL_BIN) > /dev/null; \
		make -j 20 > /dev/null; \
		make install > /dev/null; \
		cp $(TOOL_BIN)/* $(TOOLS_TOP_DIR)/$(TOOL_BIN) -rf; \
	popd

.PHONY: clean

	-pushd $(TOOLS_TOP_DIR)/$(TOOL_NAME)/ &&\
	make -C $(TOOLS_TOP_DIR)/$(TOOL_NAME)/ clean && \
	popd

.PHONY: distclean
distclean:
	-rm $(TOOLS_TOP_DIR)/$(TOOL_NAME) -rf;
	-rm $(TOOLS_TOP_DIR)/$(TOOL_BIN) -rf;

