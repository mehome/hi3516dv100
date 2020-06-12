TOOLS_TOP_DIR := $(shell pwd)
TOOL_TAR_BALL := gdb-7.6.tar.bz2
TOOL_TAR_BALL2 := ncurses-5.9.tar.gz
TOOL_NAME := gdb-7.6
TOOL_NAME2 := ncurses-5.9
TOOL_BIN := inst
TOOL_BIN2 := bin
OSDRV_CROSS ?= arm-hisiv300-linux
OSDRV_CROSS_CFLAGS ?= -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4
all:
	-rm $(TOOLS_TOP_DIR)/$(TOOL_NAME) -rf;
	-rm $(TOOLS_TOP_DIR)/$(TOOL_NAME2) -rf;
	tar -xf $(TOOL_TAR_BALL2);
	mkdir -p $(TOOLS_TOP_DIR)/$(TOOL_BIN)/;
	pushd $(TOOLS_TOP_DIR)/$(TOOL_NAME2)/; \
		./configure --host=$(OSDRV_CROSS) CFLAGS="$(OSDRV_CROSS_CFLAGS)" \
		LDFLAGS="$(OSDRV_CROSS_CFLAGS)" --prefix=$(TOOLS_TOP_DIR)/$(TOOL_BIN)/; \
		make -j > /dev/null; \
		make install;\
	popd;
	tar -xf $(TOOL_TAR_BALL);
	mkdir -p $(TOOLS_TOP_DIR)/$(TOOL_BIN)/;
	pushd $(TOOLS_TOP_DIR)/$(TOOL_NAME)/; \
		./configure --host=$(OSDRV_CROSS) CFLAGS="$(OSDRV_CROSS_CFLAGS)" \
		LDFLAGS="$(OSDRV_CROSS_CFLAGS)" --disable-tui \
		LDFLAGS=-L$(TOOLS_TOP_DIR)/$(TOOL_BIN)/lib --prefix=$(TOOLS_TOP_DIR)/$(TOOL_BIN2); \
		make -j > /dev/null; \
		make install;\
	popd;
	cp $(TOOLS_TOP_DIR)/$(TOOL_NAME)/gdb/gdb $(TOOLS_TOP_DIR)/gdb-$(OSDRV_CROSS) -rf; \

.PHONY: clean
clean:
	-pushd $(TOOLS_TOP_DIR)/$(TOOL_NAME)/ &&\
	make -C $(TOOLS_TOP_DIR)/$(TOOL_NAME)/ clean && \
	popd
	-pushd $(TOOLS_TOP_DIR)/$(TOOL_NAME2)/ &&\
	make -C $(TOOLS_TOP_DIR)/$(TOOL_NAME2)/ clean && \
	popd

.PHONY: distclean
distclean:
	-rm $(TOOLS_TOP_DIR)/$(TOOL_NAME) -rf;
	-rm $(TOOLS_TOP_DIR)/$(TOOL_NAME2) -rf;
	-rm $(TOOLS_TOP_DIR)/$(TOOL_BIN) -rf;
	-rm $(TOOLS_TOP_DIR)/$(TOOL_BIN2) -rf;
	-rm $(TOOLS_TOP_DIR)/gdb-$(OSDRV_CROSS) -rf;

