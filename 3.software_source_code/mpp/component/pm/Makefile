##########################################################################
#                   makefile for pm@l00165163.hisilicon                  #
##########################################################################
ifeq ($(PARAM_FILE), )
        PARAM_FILE:=../../Makefile.param
        include $(PARAM_FILE)
endif

include $(PWD)/Makefile.param

CODE_ROOT := $(SDK_PATH)/mpp/code
ARCH_ROOT := $(CODE_ROOT)/arch/$(ARCH_DIR)
			
CFG_INC += -I$(REL_INC)

EXTRA_CFLAGS += $(CFG_INC) 
EXTRA_CFLAGS += -Wall -D$(HIARCH) -DHICHIP=$(HICHIP) -D$(HIDBG) -D$(HI_FPGA)


include $(PWD)/base/Makefile
include $(PWD)/opp/Makefile
include $(PWD)/dvfs/Makefile
include $(PWD)/regulator/Makefile
include $(PWD)/dev/Makefile

ifeq ($(CPU_EN), y)
    EXTRA_CFLAGS += -DCPU_PM
    ifeq ($(CPU_VOLTAGE_MODE),PWM)
        EXTRA_CFLAGS += -DCPU_PWM
    endif
    
    ifeq ($(CPU_AVS_EN), y)
        EXTRA_CFLAGS += -DCPU_AVS
	include $(PWD)/avs/Makefile
    
        ifeq ($(CPU_AVS_HPM), y)
        EXTRA_CFLAGS += -DCPU_AVS_HPM
        endif

        ifeq ($(CPU_AVS_HW), y)
        EXTRA_CFLAGS += -DCPU_AVS_HW
        endif
   endif
endif

ifeq ($(MEDIA_EN), y)
    EXTRA_CFLAGS += -DMEDIA_PM
    ifeq ($(MEDIA_VOLTAGE_MODE), PWM)
        EXTRA_CFLAGS += -DMEDIA_PWM
    endif
    
    ifeq ($(MEDIA_AVS_EN), y)
	EXTRA_CFLAGS += -DMEDIA_AVS
        include $(PWD)/avs/Makefile
    
        ifeq ($(MEDIA_AVS_HPM), y)
        EXTRA_CFLAGS += -DMEDIA_AVS_HPM
        endif

        ifeq ($(MEDIA_AVS_HW), y)
        EXTRA_CFLAGS += -DMEDIA_AVS_HW
        endif
   endif
endif

EXTRA_CFLAGS += -I$(PWD)/include
EXTRA_CFLAGS += -I$(PWD)/dev/cpu/include
EXTRA_CFLAGS += -I$(PWD)/dev/media/include
 
obj-m := $(HIARCH)_pm.o
$(HIARCH)_pm-objs := $(PM_SRC:%.c=%.o) 


default:
	@make -C $(LINUX_ROOT) M=$(PWD) modules 
	cp -rf $(HIARCH)_pm.ko $(REL_KO)
	
clean: 
	@make -C $(LINUX_ROOT) M=$(PWD) clean
	rm -rf  $(REL_KO)/$(HIARCH)_pm.ko
