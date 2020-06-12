ifeq ($(PARAM_FILE), )
        PARAM_FILE:=../../../mpp/Makefile.param
        include $(PARAM_FILE)
endif

ifeq ($(KERNELRELEASE),)
export CIPHER_SRC_BASE=$(PWD)
endif

EXTRA_CFLAGS += -I$(CIPHER_SRC_BASE)
EXTRA_CFLAGS += -I$(CIPHER_SRC_BASE)/../include
EXTRA_CFLAGS += -I$(MMZ_DIR)

EXTRA_CFLAGS += -D$(HI_FPGA)

obj-m := hi_cipher.o
hi_cipher-y += ./drv_cipher.o ./hal_cipher.o ./cipher_intf.o

TEST=n

ifeq ($(TEST),y)
hi_cipher-y += ./test_cipher.o
EXTRA_CFLAGS += -DTEST_CIPHER
endif

all: 
	make -C $(LINUX_ROOT) M=$(PWD) modules
	$(CC) $(EXTRA_CFLAGS) -shared -o hi_unf_cipher.so hi_unf_cipher.c
	$(CC) $(EXTRA_CFLAGS) -c hi_unf_cipher.c -Wall
	$(AR) -rv libhi_cipher.a hi_unf_cipher.o

clean: 
	make -C $(LINUX_ROOT) M=$(PWD) clean
	rm *.so -f
