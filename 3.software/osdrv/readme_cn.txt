1.osdrv 顶层 Makefile 使用说明
本目录下的编译脚本支持选用下文提到的两种工具链中的任何一种进行编译，因此编译时需要带上一个编译参数以指定对应的工具链 -- arm-hisiv300-linux 和 arm-hisiv400-linux。其中，arm-hisiv300-linux工具链对应uclibc库，arm-hisiv400-linux工具链对应glibc库。具体命令如下

(1)编译整个osdrv目录：
	make OSDRV_CROSS=arm-hisiv300-linux all
	或者
	make OSDRV_CROSS=arm-hisiv400-linux all

	/* 如果单板使用spi接口nand flash作为存储介质，请在编译整个目录时传入如下FLASH_TYPE参数 */
	make OSDRV_CROSS=arm-hisiv300-linux all FLASH_TYPE=spinand
	或者
	make OSDRV_CROSS=arm-hisiv400-linux all FLASH_TYPE=spinand

(2)清除整个osdrv目录的编译文件：
	make OSDRV_CROSS=arm-hisiv300-linux clean
	或者
	make OSDRV_CROSS=arm-hisiv400-linux clean
(3)彻底清除整个osdrv目录的编译文件，除清除编译文件外，还删除已编译好的镜像：
	make OSDRV_CROSS=arm-hisiv300-linux distclean
	或者
	make OSDRV_CROSS=arm-hisiv400-linux distclean

(4)单独编译kernel：
	待进入内核源代码目录后，执行以下操作
	cp arch/arm/configs/hi3516a_full_defconfig  .config
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- menuconfig
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- uImage
	或者
	cp arch/arm/configs/hi3516a_full_defconfig  .config
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux- menuconfig
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux- uImage
(5)单独编译模块：
	待进入内核源代码目录后，执行以下操作
	cp arch/arm/configs/hi3516a_full_defconfig  .config
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- menuconfig
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- modules
	或者
	cp arch/arm/configs/hi3516a_full_defconfig  .config
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux- menuconfig
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux- modules
(6)单独编译uboot：
	待进入boot源代码目录后，执行以下操作
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- hi3516a_config 
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux-
	将生成的u-boot.bin 复制到osdrv/tools/pc/uboot_tools/目录下
	运行./mkboot.sh reg_info.bin u-boot-ok.bin
	生成的u-boot-ok.bin即为可用的u-boot镜像
	或者
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux- hi3516a_config 
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux-
	将生成的u-boot.bin 复制到osdrv/tools/pc/uboot_tools/目录下
	运行./mkboot.sh reg_info.bin u-boot-ok.bin
	生成的u-boot-ok.bin即为可用的u-boot镜像
(7)制作文件系统镜像：
在osdrv/pub/中有已经编译好的文件系统，因此无需再重复编译文件系统，只需要根据单板上flash的规格型号制作文件系统镜像即可。

	spi flash使用jffs2格式的镜像，制作jffs2镜像时，需要用到spi flash的块大小。这些信息会在uboot启动时会打印出来。建议使用时先直接运行mkfs.jffs2工具，根据打印信息填写相关参数。下面以块大小为256KB为例：
	osdrv/pub/bin/pc/mkfs.jffs2 -d osdrv/pub/rootfs_uclibc -l -e 0x40000 -o osdrv/pub/rootfs_uclibc_256k.jffs2
	或者
	osdrv/pub/bin/pc/mkfs.jffs2 -d osdrv/pub/rootfs_glibc -l -e 0x40000 -o osdrv/pub/rootfs_glibc_256k.jffs2

	nand flash使用yaffs2格式的镜像，制作yaffs2镜像时，需要用到nand flash的pagesize和ecc。这些信息会在uboot启动时会打印出来。建议使用时先直接运行mkyaffs2image工具，根据打印信息填写相关参数。下面以2KB pagesize、4bit ecc为例：
	osdrv/pub/bin/pc/mkyaffs2image610 osdrv/pub/rootfs_uclibc osdrv/pub/rootfs_uclibc_2k_4bit.yaffs2 1 2
	或者
	osdrv/pub/bin/pc/mkyaffs2image610 osdrv/pub/rootfs_glibc osdrv/pub/rootfs_glibc_2k_4bit.yaffs2 1 2


2. 镜像存放目录说明
编译完的image，rootfs等存放在osdrv/pub目录下
pub
│  rootfs_uclibc.tgz ------------------------------------------ hisiv300编译出的rootfs文件系统
│  rootfs_glibc.tgz ------------------------------------------- hisiv400编译出的rootfs文件系统
│
├─image_glibc ------------------------------------------------- hisiv400编译出的镜像文件
│      uImage_hi3516a ----------------------------------------- kernel镜像
│      u-boot-hi3516a.bin ------------------------------------- u-boot镜像
│      rootfs_hi3516a_64k.jffs2 ------------------------------- 64K jffs2 文件系统镜像
│      rootfs_hi3516a_128k.jffs2 ------------------------------ 128K jffs2 文件系统镜像
│      rootfs_hi3516a_256k.jffs2 ------------------------------ 256K jffs2 文件系统镜像
│      rootfs_hi3516a_2k_4bit.yaffs2 -------------------------- yaffs2 文件系统镜像
│      rootfs_hi3516a_2k_128k_32M.img ----------------------ubifs文件系统镜像
│
├─image_uclibc ------------------------------------------------ hisiv300编译出的镜像文件
│      uImage_hi3516a ----------------------------------------- kernel镜像
│      u-boot-hi3516a.bin ------------------------------------- u-boot镜像(其中xxx表示AXI总线频率)
│      rootfs_hi3516a_64k.jffs2 ------------------------------- 64K jffs2 文件系统镜像
│      rootfs_hi3516a_128k.jffs2 ------------------------------ 128K jffs2 文件系统镜像
│      rootfs_hi3516a_256k.jffs2 ------------------------------ 256K jffs2 文件系统镜像
│      rootfs_hi3516a_2k_4bit.yaffs2 -------------------------- yaffs2 文件系统镜像
│      rootfs_hi3516a_2k_128k_32M.img ----------------------ubifs文件系统镜像
│
└─bin
    ├─pc
    │      mkfs.jffs2
    │      mkfs.ubifs
    │      ubinize
    │      mkimage
    │      mkfs.cramfs
    │      mkyaffs2image610
    │      mksquashfs
    │      lzma
    │
    ├─board_glibc -------------------------------------------- hisiv400编译出的单板用工具
    │   ├─hifat ---------------------------------------------- hifat 工具
    │   │    ├─shared
    │   │    │     himount
    │   │    ├─static
    │   │    │     libhimount_api.a
    │   │    │     himount
    │   │    ├─static
    │   │    │     hifat-1.0-glibc.tgz
    │   │    ├─himount_api.h
    │   │    ├─how_to_use_[chs].txt
    │   │    └─how_to_use_[en].txt
    │   ethtool
    │   flash_erase
    │   flash_otp_dump
    │   flash_otp_info
    │   sumtool
    │   mtd_debug
    │   flashcp
    │   nandtest
    │   nanddump
    │   nandwrite
    │   gdb-arm-hisiv400-linux
    │
    └─board_uclibc ------------------------------------------- hisiv300编译出的单板用工具
          ├─hifat -------------------------------------------- hifat 工具
          │    ├─shared
          │    │     himount
          │    ├─static
          │    │     libhimount_api.a
          │    │     himount
          │    ├─static
          │    │     hifat-1.0-uclibc.tgz
          │    ├─himount_api.h
          │    ├─how_to_use_[chs].txt
          │    └─how_to_use_[en].txt
          ethtool
          flash_erase
          flash_otp_dump
          flash_otp_info
          sumtool
          mtd_debug
          flashcp
          nandtest
          nanddump
          nandwrite
          gdb-arm-hisiv300-linux

3.osdrv目录结构说明：
osdrv
├─Makefile -------------------------------------- osdrv目录编译脚本
├─tools ----------------------------------------- 存放各种工具的目录
│  ├─board -------------------------------------- 各种单板上使用工具
│  │  ├─reg-tools-1.0.0 ------------------------- 寄存器读写工具
│  │  ├─hifat --- ------------------------------- FAT文件系统制作工具
│  │  ├─udev-164 -------------------------------- udev工具集
│  │  ├─mkdosfs --------------------------------- mkdosfs工具
│  │  ├─mtd-utils ------------------------------- flash裸读写工具集
│  │  ├─gdb ------------------------------------- gdb工具
│  │  ├─ethtools -------------------------------- ethtools工具
│  │  └─e2fsprogs ------------------------------- mkfs工具集
│  └─pc ----------------------------------------- 各种pc上使用工具
│      ├─jffs2_tool------------------------------ jffs2文件系统制作工具
│      ├─ubifs_config---------------------------- ubifs文件系统配置文件
│      ├─cramfs_tool ---------------------------- cramfs文件系统制作工具
│      ├─squashfs4.2 ---------------------------- squashfs文件系统制作工具
│      ├─mkimage_tool --------------------------- uImage制作工具
│      ├─nand_production ------------------------ nand量产工具
│      ├─lzma_tool ------------------------------ lzma压缩工具
│      ├─mkyaffs2image -- ----------------------- yaffs2文件系统制作工具
│      └─uboot_tools ---------------------------- uboot镜像制作工具、xls文件及ddr初始化脚本、Fastboot工具
├─pub ------------------------------------------- 存放各种镜像的目录
│  ├─image_uclibc ------------------------------- 基于hisiv300工具链编译，可供FLASH烧写的映像文件，包括uboot、内核、文件系统
│  ├─image_glibc -------------------------------- 基于hisiv400工具链编译，可供FLASH烧写的映像文件，包括uboot、内核、文件系统
│  ├─bin ---------------------------------------- 各种未放入根文件系统的工具
│  │  ├─pc -------------------------------------- 在pc上执行的工具
│  │  ├─board_uclibc ---------------------------- 基于hisiv300工具链编译，在单板上执行的工具
│  │  └─board_glibc ----------------------------- 基于hisiv400工具链编译，在单板上执行的工具
│  ├─rootfs_uclibc.tgz -------------------------- 基于hisiv300工具链编译的根文件系统
│  └─rootfs_glibc.tgz --------------------------- 基于hisiv400工具链编译的根文件系统
├─opensource------------------------------------- 存放各种开源源码目录
│  ├─toolchain ---------------------------------- 存放工具链的目录
│  ├─busybox ------------------------------------ 存放busybox源代码的目录
│  ├─uboot -------------------------------------- 存放uboot源代码的目录
│  └─kernel ------------------------------------- 存放kernel源代码的目录
└─rootfs_scripts -------------------------------- 存放根文件系统制作脚本的目录

4.注意事项
(1)在windows下复制源码包时，linux下的可执行文件可能变为非可执行文件，导致无法编译使用；u-boot或内核下编译后，会有很多符号链接文件，在windows下复制这些源码包, 会使源码包变的巨大，因为linux下的符号链接文件变为windows下实实在在的文件，因此源码包膨胀。因此使用时请注意不要在windows下复制源代码包。
(2)使用某一工具链编译后，如果需要更换工具链，请先将原工具链编译文件清除，然后再更换工具链编译。
(3)编译板端软件
    a.Hi3516A具有浮点运算单元和neon。文件系统中的库是采用软浮点和neon编译而成，因此请用户注意，所有Hi3516A板端代码编译时需要在Makefile里面添加选项-mcpu=cortex-a7、-mfloat-abi=softfp和-mfpu=neon-vfpv4。
    b.v300和v400工具链都是基于GCC4.8的。从GCC4.7开始，在编译基于ARMv6 (除了ARMv6-M), ARMv7-A, ARMv7-R, or ARMv7-M的代码时，为了支持以地址非对齐方式访问内存，默认激活了-munaligned-access选项，但这需要系统的内核支持这种访问方式。Hi3516A不支持地址非对齐的内存访问方式，所以板端代码在编译的时候需要显式加上选项-mno-unaligned-access。(http://gcc.gnu.org/gcc-4.7/changes.html)
    c.GCC4.8使用了更激进的循环上界分析策略，这有可能导致一些不相容的程序运行出错。建议板端代码在编译的时候使用-fno-aggressive-loop-optimizations关闭此优化选项，以避免代码运行时出现奇怪的错误。(http://gcc.gnu.org/gcc-4.8/changes.html)
如：
    CFLAGS += -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations
    CXXFlAGS +=-mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations
其中CXXFlAGS中的XX根据用户Makefile中所使用宏的具体名称来确定，e.g:CPPFLAGS。