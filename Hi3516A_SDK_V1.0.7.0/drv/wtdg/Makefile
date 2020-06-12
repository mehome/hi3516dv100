ifeq ($(PARAM_FILE), )
		PARAM_FILE:=../../mpp/Makefile.param
		include $(PARAM_FILE)
endif

obj-m := wdt.o
wdt-y += hi_wdt.o 


EXTRA_CFLAGS+=-I$(PWD)/

default:	
	@echo -e "\e[0;32;1m--Compiling 'wtdg'... \e[0;36;1m"
	@@echo -e "\e[0m" 
	@$(MAKE) -C $(LINUX_ROOT) M=$(PWD) modules 

clean:
	@make -C $(LINUX_ROOT) M=$(PWD) clean 
	@rm -rf *.ko
