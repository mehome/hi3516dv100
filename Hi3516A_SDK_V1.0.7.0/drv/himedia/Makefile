# Create by liucan,2012/12/26

ifeq ($(PARAM_FILE), )
    PARAM_FILE:=../../mpp/Makefile.param
    include $(PARAM_FILE)
endif

EXTRA_CFLAGS +=
obj-m := hi_media.o
hi_media-y += himedia.o base.o

all:
	@echo -e "\e[0;32;1m--Compiling 'hi_media'...\e[0;36;1m" 
	@echo -e "\e[0m" 
	@make -C $(LINUX_ROOT) M=$(PWD) modules
	@cp hi_media.ko $(REL_KO)
	@cp himedia.h $(REL_INC)

clean: 
	@make -C $(LINUX_ROOT) M=$(PWD) clean 
	@rm -rf $(REL_KO)/hi_media.ko
