export OSDRV_CROSS

OSDRV_CROSS := arm-hisiv300-linux
#OSDRV_CROSS := arm-hisiv400-linux

PC_TOOL := pc
BD_TOOL := board
PC_TOOLS := cramfs_tool lzma_tool mkimage_tool mkyaffs2image jffs2_tool squashfs4.2
BOARD_TOOLS := e2fsprogs gdb reg-tools-1.0.0 udev-164 mkdosfs mtd-utils

BUILD_TOOLS_PC = $(patsubst %, %.pctools, $(PC_TOOLS))
BUILD_TOOLS_BD = $(patsubst %, %.bdtools, $(BOARD_TOOLS))

all: $(BUILD_TOOLS_PC) $(BUILD_TOOLS_BD)

%.pctools:
	@echo -e "\033[41;5m""===== now is build $(patsubst %.pctools,%,$@) =====""\033[00m"
	make -C $(PC_TOOL)/$(strip $(patsubst %.pctools, %, $@))
%.bdtools:
	@echo -e "\033[41;5m""===== now is build $(patsubst %.bdtools,%,$@) =====""\033[00m"
	make -C $(BD_TOOL)/$(strip $(patsubst %.bdtools, %, $@))

pctools:$(BUILD_TOOLS_PC)

boardtools: $(BUILD_TOOLS_BD)

.PHONY: clean
clean: 
	@for i in $(PC_TOOLS); do ( \
		echo -e "===== now is clean $$i ====="; \
		make -C $(PC_TOOL)/$$i  clean; \
	) done
	
	@for i in $(BOARD_TOOLS); do ( \
		echo -e "===== now is clean $$i ====="; \
		make -C $(BD_TOOL)/$$i  clean; \
	) done

.PHONY: distclean
distclean:
	@for i in $(PC_TOOLS); do ( \
		echo -e "===== now is distclean $$i ====="; \
		make -C $(PC_TOOL)/$$i distclean; \
	) done
	@for i in $(BOARD_TOOLS); do ( \
		echo -e "===== now is distclean $$i ====="; \
		make -C $(BD_TOOL)/$$i distclean; \
	) done

