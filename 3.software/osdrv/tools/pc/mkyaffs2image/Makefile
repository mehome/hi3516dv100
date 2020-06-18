################################################################################
#    x86/src/mkyaffs2image
#    Create By 
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
BUILD_DIR      := $(PREFIX)/mkyaffs2image
STRIP          := strip

MKYAFFS2IMAGE  := mkyaffs2image610 mkyaffs2image400
################################################################################

all: \
    $(BUILD_DIR)/tar
	cd $(BUILD_DIR) && \
		make && \
	cd -
	mkdir -p $(PREFIX)/bin
	cp $(BUILD_DIR)/mkyaffs2image610 $(PREFIX)/bin
	cp $(BUILD_DIR)/mkyaffs2image400 $(PREFIX)/bin

################################################################################

clean:
	@test ! -d $(BUILD_DIR) || rm -rfv $(BUILD_DIR)
	rm $(PREFIX)/bin -rf;

distclean: clean

$(BUILD_DIR)/tar:
	@test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(PREFIX)
	@touch $@

################################################################################
.PHONY: clean distclean all
################################################################################
