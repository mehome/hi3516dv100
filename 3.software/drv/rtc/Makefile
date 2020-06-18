#Create by liucan, 2012/12/26

ifeq ($(PARAM_FILE), )
    PARAM_FILE:=../../mpp/Makefile.param
    include $(PARAM_FILE)
endif

CC=$(CROSS)gcc

#EXTRA_CFLAGS += -DHIDEBUG
EXTRA_CFLAGS += -D$(HI_FPGA)

obj-m := hi_rtc.o
hirtc-y := hi_rtc.o

.PHONY: all clean

all: ko test

ko:
	@echo -e "\e[0;32;1m--Compiling 'rtc'...\e[0;36;1m"
	@@echo -e "\e[0m" 
	@make -C $(LINUX_ROOT) M=$(PWD) modules
	@cp hi_rtc.ko $(REL_KO)

test: rtc_test.o
	@$(CC) -o $@ $^

clean: test_clean
	@make -C $(LINUX_ROOT) M=$(PWD) clean
	@rm -rf $(REL_KO)/hi_rtc.ko

test_clean:
	@rm -rf test *.o 
