TOOLS_TOP_DIR ?= $(shell pwd)
TOOL_TAR_BALL := lzma-4.32.7.tar.gz
TOOL_NAME := lzma-4.32.7

all:
	-rm $(TOOLS_TOP_DIR)/$(TOOL_NAME) -rf;
	tar -xzf $(TOOL_TAR_BALL);
	pushd $(TOOLS_TOP_DIR)/$(TOOL_NAME)/; \
		chmod 777 ./configure; \
		./configure;\
		make; \
	popd;\
	cp $(TOOLS_TOP_DIR)/$(TOOL_NAME)/src/lzma/lzma $(TOOLS_TOP_DIR)/

.PHONY: clean
clean:
	pushd $(TOOLS_TOP_DIR)/$(TOOL_NAME)/; \
	make -C $(TOOLS_TOP_DIR)/$(TOOL_NAME)/ distclean && \
	popd

.PHONY: distclean
distclean:
	-rm $(TOOLS_TOP_DIR)/$(TOOL_NAME) -rf;
	-rm $(TOOLS_TOP_DIR)/lzma -rf;

