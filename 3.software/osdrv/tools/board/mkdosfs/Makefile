export CROSS_COMPILE
export CFLAGS
export LDFLAGS
TOOL_BIN := bin
OSDRV_CROSS ?= arm-hisiv300-linux
CROSS_COMPILE := $(OSDRV_CROSS)
TOOL_NAME := dosfstools-3.0.26
TOOL_TAR_BALL := dosfstools-3.0.26.tar.gz
TOOL_DIR := $(shell pwd)
OSDRV_CROSS_CFLAGS ?= -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4
CFLAGS=$(OSDRV_CROSS_CFLAGS)
LDFLAGS=$(OSDRV_CROSS_CFLAGS)

all:
	rm $(TOOL_NAME) -rf;
	tar -zxf $(TOOL_TAR_BALL);
	mkdir -p $(TOOL_BIN)/;
	pushd $(TOOL_NAME)/;\
		make;\
		make install;\
	popd
	mv $(TOOL_NAME)/usr/local/sbin/mkfs.fat $(TOOL_BIN)
	mv $(TOOL_NAME)/usr/local/sbin/mkfs.vfat $(TOOL_BIN)
	mv $(TOOL_NAME)/usr/local/sbin/mkdosfs $(TOOL_BIN)

clean:
	rm $(TOOL_NAME) -rf;
	rm $(TOOL_BIN) -rf;

distclean: clean
