ifeq ($(PARAM_FILE), )
    PARAM_FILE:=../../mpp/Makefile.param
    include $(PARAM_FILE)
endif

CC=$(CROSS)gcc

EXTRA_CFLAGS += $(DRV_CFLAGS)

EXTRA_CFLAGS += -I$(DRV_ROOT)/himedia/
#EXTRA_CFLAGS += -DHI_MIPI_DEBUG
EXTRA_CFLAGS += -D$(HI_FPGA)

obj-m := hi_mipi.o
hi_mipi-y = mipi.o mipi_hal.o

.PHONY: all clean

all: ko mipi_test

ko:
	@echo -e "\e[0;32;1m--Compiling 'mipi'...\e[0;36;1m"
	@@echo -e "\e[0m" 
	@make -C $(LINUX_ROOT) M=$(PWD) modules
	@cp hi_mipi.ko $(REL_KO);cp hi_mipi.h $(REL_INC)

mipi_test: mipi_test.o
	@$(CC) -o $@ $^

clean: test_clean
	@make -C $(LINUX_ROOT) M=$(PWD) clean
	@rm -rf $(REL_KO)/hi_mipi.ko

test_clean:
	@rm -rf test *.o 
	@rm -rf mipi_test 
