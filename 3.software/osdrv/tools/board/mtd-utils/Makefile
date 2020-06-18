TOOL_BIN := bin
OSDRV_CROSS ?=arm-hisiv300-linux
TOOL_NAME :=mtd-utils-1.5.0
TOOL_TAR_BALL := mtd-utils-1.5.0.tar.bz2
TOOL_DIR := $(shell pwd)

all:
	rm $(TOOL_NAME) -rf;
	tar -xf $(TOOL_TAR_BALL);
	mkdir -p $(TOOL_BIN)/;
	pushd $(TOOL_NAME)/;\
		make CROSS=$(OSDRV_CROSS)- CFLAGS=--static; \
	popd
	cp $(TOOL_NAME)/$(OSDRV_CROSS)/* $(TOOL_BIN) -rf
	rm -rf $(TOOL_BIN)/*.o
	rm -rf $(TOOL_BIN)/ubi-utils/*.a
	rm -rf $(TOOL_BIN)/ubi-utils/*.o
	mv $(TOOL_BIN)/ubi-utils/* $(TOOL_BIN)
	rm -rf $(TOOL_BIN)/ubi-utils
	rm -rf $(TOOL_BIN)/mkfs.ubifs
	rm -rf $(TOOL_BIN)/lib
	rm -rf $(TOOL_BIN)/include
	$(OSDRV_CROSS)-strip  $(TOOL_BIN)/*

clean:
	rm $(TOOL_NAME) -rf;
	rm $(TOOL_BIN) -rf;

distclean: clean
