
ifeq ($(PARAM_FILE), )
		PARAM_FILE:=../../mpp/Makefile.param
		include $(PARAM_FILE)
endif

obj-m := hi_ir.o
hi_ir-y += hiir.o

#EXTRA_CFLAGS += -D$(HI_FPGA)
#EXTRA_CFLAGS+=-I$(PWD)/../gpio-i2c

default:
	@echo -e "\e[0;32;1m--Compiling 'hi_ir'...\e[0;36;1m"
	@@echo -e "\e[0m" 
	@make -C $(LINUX_ROOT) M=$(PWD) modules 
clean: 
	@make -C $(LINUX_ROOT) M=$(PWD) clean 



