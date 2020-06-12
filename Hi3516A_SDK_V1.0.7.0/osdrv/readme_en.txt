1.How to use Makefile of directory osdrv:
Either one of the two toolchains(arm-hisiv300-linux and arm-hisiv400-linux) could be used to compile the source code under current directory. So a parameter to specify the right toolchain should be given while compiling osdrv. The arm-hisiv300-linux toolchain is for uclibc, and the arm-hisiv400-linux toolchain for glibc. 

(1)Compile the entire osdrv directory:
	make OSDRV_CROSS=arm-hisiv300-linux all
	or:
	make OSDRV_CROSS=arm-hisiv400-linux all
	
	/* if board use nand flash with Spi interface as a storage medium, Please pass the following FLASH_TYPE parameter while compiling entire osdrv */
	make OSDRV_CROSS=arm-hisiv300-linux all FLASH_TYPE=spinand
	or:
	make OSDRV_CROSS=arm-hisiv400-linux all FLASH_TYPE=spinand
(2)Clear all compiled files under osdrv directory:
	make OSDRV_CROSS=arm-hisiv300-linux clean
	or:
	make OSDRV_CROSS=arm-hisiv400-linux clean
(3)Completely remove all compiled files under osdrv directory, and the generated images:
	make OSDRV_CROSS=arm-hisiv300-linux distclean
	or:
	make OSDRV_CROSS=arm-hisiv400-linux distclean
(4)Separately compile kernel:
	Enter the top directory the kernel source code, do the following:
	cp arch/arm/configs/hi3516a_full_defconfig  .config
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- menuconfig
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- uImage
	or:
	cp arch/arm/configs/hi3516a_full_defconfig  .config
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux- menuconfig
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux- uImage
(5)Separately compile modules:
	Enter the top directory the kernel source code, do the following:
	cp arch/arm/configs/hi3516a_full_defconfig  .config
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- menuconfig
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- modules
	or:
	cp arch/arm/configs/hi3516a_full_defconfig  .config
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux- menuconfig
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux- modules
(6)Separately compile uboot:
	Enter the top directory of boot source code, do the following:
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- hi3516a_config 
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux-
	The generated u-boot.bin is copied to osdrv/tools/pc/uboot_tools/directory
	./mkboot.sh reg_info.bin u-boot-ok.bin
	The generated u-boot-ok.bin is available for u-boot image
	or:
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux- hi3516a_config 
	make ARCH=arm CROSS_COMPILE=arm-hisiv400-linux-
	The generated u-boot.bin is copied to osdrv/tools/pc/uboot_tools/directory
	./mkboot.sh reg_info.bin u-boot-ok.bin
	The generated u-boot-ok.bin is available for u-boot image

(7)Build file system image:
        A compiled file system has already been in osdrv/pub/, so no need to re-build file system. What you need to do is to build the right file system image according to the flash specification of the single-board. 
	Filesystem images of jffs2 format is available for spi flash. While making jffs2 image or squashfs image, you need to specify the spi flash block size. flash block size will be printed when uboot runs. run mkfs.jffs2 first to get the right parameters from it's printed information. Here the block size is 256KB, for example:

	jffs2 filesystem image:
	osdrv/pub/bin/pc/mkfs.jffs2 -d osdrv/pub/rootfs_uclibc -l -e 0x40000 -o osdrv/pub/rootfs_uclibc_256k.jffs2
	or:
	osdrv/pub/bin/pc/mkfs.jffs2 -d osdrv/pub/rootfs_glibc -l -e 0x40000 -o osdrv/pub/rootfs_glibc_256k.jffs2
	
	Filesystem image of yaffs2 format is available for nand flash. While making yaffs2 image, you need to specify it's page size and ECC. This information will be printed when uboot runs. run mkyaffs2image first to get the right parameters from it's printed information. Here to 2KB pagesize, 4bit ecc, for example:
	
	osdrv/pub/bin/pc/mkyaffs2image610 osdrv/pub/rootfs_uclibc osdrv/pub/rootfs_uclibc_2k_4bit.yaffs2 1 2
	or:
	osdrv/pub/bin/pc/mkyaffs2image610 osdrv/pub/rootfs_glibc osdrv/pub/rootfs_glibc_2k_4bit.yaffs2 1 2


2. Output directory description
All compiled images, rootfs are located in directory osdrv/pub/.
pub
│  rootfs_uclibc.tgz -------------------------------------- rootfs compiled with hisiv300
│  rootfs_glibc.tgz --------------------------------------- rootfs compiled with hisiv400
│
├─image_glibc --------------------------------------------- Images compiled with hisiv400
│      uImage_hi3516a --------------------------------------------- kernel image
│      u-boot-hi3516a.bin --------------------------------- u-boot image
│      rootfs_hi3516a_64k.jffs2  ---------------------------------- jffs2 rootfs image(spi-flash blocksize = 64K)
│      rootfs_hi3516a_128k.jffs2 ---------------------------------- jffs2 rootfs image(spi-flash blocksize = 128K)
│      rootfs_hi3516a_256k.jffs2 ---------------------------------- jffs2 rootfs image(spi-flash blocksize = 256K)
│      rootfs_hi3516a_2k_4bit.yaffs2 ------------------------------ yaffs2 rootfs image(nand-flash pagesize=2K ecc=4bit)
│      rootfs_hi3516a_2k_128k_32M.img ----------------------ubifs rootfs image(nand-flash pagesize=2K blocksize = 128K)
│
├─image_uclibc -------------------------------------------- Images compiled with hisiv300
│      uImage_hi3516a --------------------------------------------- kernel image
│      u-boot-hi3516a.bin --------------------------------- u-boot image
│      rootfs_hi3516a_64k.jffs2  ---------------------------------- jffs2 rootfs image(spi-flash blocksize = 64K)
│      rootfs_hi3516a_128k.jffs2 ---------------------------------- jffs2 rootfs image(spi-flash blocksize = 128K)
│      rootfs_hi3516a_256k.jffs2 ---------------------------------- jffs2 rootfs image(spi-flash blocksize = 256K)
│      rootfs_hi3516a_2k_4bit.yaffs2 ------------------------------ yaffs2 rootfs image(nand-flash pagesize=2K ecc=4bit)
│      rootfs_hi3516a_2k_128k_32M.img ----------------------ubifs rootfs image(nand-flash pagesize=2K blocksize = 128K)
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
    ├─board_glibc ---------------------------------------- tools used on board
    │   ├─hifat ------------------------------------------ hifat tool
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
    └─board_uclibc --------------------------------------- tools used on board
        ├─hifat ------------------------------------------ hifat tools
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

3.osdrv directory structure：
osdrv
├─Makefile ---------------------------------- osdrv compile script
├─tools ------------------------------------- directory of all tools
│  ├─board ---------------------------------- A variety of single-board tools
│  │  ├─reg-tools-1.0.0 --------------------- tools for accessing memory space and io space
│  │  ├─hifat --- --------------------------- tools for making FAT file system
│  │  ├─udev-164 ---------------------------- udev toolset
│  │  ├─mkdosfs ----------------------------- tools for making DOS file system
│  │  ├─mtd-utils --------------------------- tools to read and write flash nude
│  │  ├─gdb --------------------------------- gdb tools
│  │  ├─ethtools ---------------------------- tool to query and set the parameters of NIC
│  │  └─e2fsprogs --------------------------- mkfs tools
│  └─pc ------------------------------------- tools used on PC
│      ├─jffs2_tool-------------------------- tools for making jffs2 file system
│      ├─ubifs_config------------------------ config file for ubifs file system
│      ├─cramfs_tool ------------------------ tools for making cramfs file system
│      ├─squashfs4.2 ------------------------ tools for making mksquashfs file system
│      ├─mkimage_tool ----------------------- tools for making uImage
│      ├─nand_production -------------------- nand Production tools
│      ├─lzma_tool -------------------------- lzma compress tool
│      ├─mkyaffs2image -- ------------------- tools for making yaffs2 file system
│      └─uboot_tools ------------------------ tools for creating uboot image,xls files,ddr initialization script and Fastboot
├─pub --------------------------------------- output directory
│  ├─image_uclibc --------------------------- images compiled with hisiv300: uboot,uImage and images of filesystem
│  ├─image_glibc ---------------------------- images compiled with hisiv400: uboot,uImage and images of filesystem
│  ├─bin ------------------------------------ tools not placed in the rootfs
│  │  ├─pc ---------------------------------- tools used on the PC
│  │  ├─board_uclibc ------------------------ board tools compiled with hisiv300
│  │  └─board_glibc ------------------------- board tools compiled with hisiv400
│  ├─rootfs_uclibc.tgz ---------------------- rootfs compiled with hisiv300
│  └─rootfs_glibc.tgz ----------------------- rootfs compiled with hisiv400
├─opensource--------------------------------- A variety of opensource code
│  ├─toolchain ------------------------------ directory contains toolchains
│  ├─busybox -------------------------------- busybox source code
│  ├─uboot ---------------------------------- uboot source code
│  └─kernel --------------------------------- kernel source code
└─rootfs_scripts ---------------------------- scripts to generate rootfs directory

4.Note
(1)Executable files in Linux may become non-executable after copying them to somewhere else under Windows, and result in souce code cannot be compiled. Many symbolic link files will be generated in the souce package after compiling the u-boot or the kernel. The volume of the source package will become very big, because all the symbolic link files are turning out to be real files in Windows. So, DO NOT copy source package in Windows.
(2)If a tool chain needs to be replaced by the other, remove the original compiled files compiled with the former tool chain, and then replace the compiler tool chain with the other. 
(3) compile single-board code
    a.The Hi3516A has floating-point unit and neon. The library provided by the file system is a library with hard soft floating-points and neon. Therefore, add the following options in Makefile when compiling the single-board code.
    b.The tool chain arm-hisiv300-linux- and arm-hisiv400-linux- are based on GCC4.8. From GCC4.7, when compiling for ARMv6 (but not ARMv6-M), ARMv7-A, ARMv7-R, or ARMv7-M, the new option -munaligned-access is active by default, which for some sources generates code that accesses memory on unaligned addresses. This requires the kernel of those systems to enable such accesses. Hi3516A  don't support unaligned accesses, so single-board code has to be compiled with -mno-unaligned-access. (http://gcc.gnu.org/gcc-4.7/changes.html)
    c.GCC4.8 now uses a more aggressive analysis to derive an upper bound for the number of iterations of loops. This may cause non-conforming programs to no longer work as expected. Recommended that single-board code should be compiled with -fno-aggressive-loop-optimizations to disable this aggressive analysis. (http://gcc.gnu.org/gcc-4.8/changes.html)
For example:
    CFLAGS += -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations
    CXXFlAGS +=-mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=neon-vfpv4 -mno-unaligned-access -fno-aggressive-loop-optimizations
Among these, CXXFlAGS may be different according to the specific name in user's Makefile. For example, it may be changed to CPPFLAGS.