# hi3516dv100
git上传命令
1.  git add .
2.  git commit -m "xxxx"
3.  git push origin master

#### 介绍
开源海思学习的过程，分享所有的软件和硬件资料。
github开源地址：https://github.com/Jun1172/hi3516dv100.git
gitee开源地址：https://github.com/Jun1172/hi3516dv100.git

#### 文件说明

1.  官方的SDK因为存在大的压缩包，传不上git，现在git中是有删减的
2.  获取官方的原始SDK可以加群下载，受后期项目的推进影响，官方资源可能不会适用于开源的硬件

#### 编译说明
##### uboot编译：
1.  进入文件夹：your_addr/hi3516dv100/3.software_source_code/osdrv/opensource/uboot/u-boot-2010.06
	make clean	
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- hi3516a_config 
	或者
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- hi3516a_spinand_config 
	编译成功后，将在U-boot目录下生成u-boot.bin。
	其中 hi3516a_config 为支持 SPI Flash 和 Nand Flash 的配置，hi3516a_spinand_config 为支持
	SPI-Nand Flash 的配置。
2.  编译U-boot：make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux-
	其中 CROSS_COMPILE 表示工具链。文档中统一以 CROSS_COMPILE=arm-hisiXXX-linux-来
	表示两种情况。
	z Hi3516A_V100R001C01SPCxxx 对应 uclibc，使用 uclibc 工具链时，CROSS_COMPILE=arm-hisiv300-linux-。 z Hi3516A_V100R001C02SPCxxx 对应 glibc，使用 glibc 工具链时，CROSS_COMPILE=arm-hisiv400-linux-。
	这一步生成的 u-boot.bin 只是一个中间件，并不是最终在单板上执行的 U-boot 镜像。
3.   配置 DDR 存储器
在 Windows 下打开 SDK 中的“osdrv/ tools/pc/uboot_tools/”目录下的配置表格。当选
用不同的 DDR SDRAM 时，需要针对不同器件的特性，对配置工作表中的标签页
【mddrc_dmc1】、【mddrc_dmc2】和【mddrc_phy】进行修改。
4.   配置管脚复用
如果管脚复用有变化，还需要对配置表格中的标签页【muxctrl_reg】进行修改。
5.  生成最终使用的 U-boot 镜像
完成配置表格的修改后，保存表格。单击表格第一个标签页上的按钮【Generage reg 
bin file】(只能点此按钮)，生成临时文件 reg_info.bin。
将临时文件 reg_info.bin 和编译 u-boot 得到的 u-boot.bin 都拷贝到 SDK 中的
“osdrv/tools/pc/uboot_tools/”目录下，执行命令：
mkboot.sh reg_info_hi3516a.bin u-boot-hi3516a.bin
其中 u-boot-hi3516a.bin 就是能够在单板上运行的 U-boot 镜像。

##### kernel编译：
1.  进入文件夹：your_addr/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y
2.  配置内核：make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- menuconfig
	编译内核时需要在 make 后添加两个参数：ARCH=arm CROSS_COMPILE=arm-hisiXXX-linux-，其中 CROSS_COMPILE 表示工具链。
	文档中统一以 CROSS_COMPILE=arm-hisiXXX-linux-来表示两种情况。
	z Hi3516A_V100R001C01SPCxxx 对应 uclibc，使用 uclibc 工具链时，CROSS_COMPILE= arm-hisiv300-linux -。 z Hi3516A_V100R001C02SPCxxx 对应 glibc，使用 glibc 工具链时，CROSS_COMPILE=arm-hisiv400-linux-。
3.  编译内核：make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- uImage -j4
	如果编译过程中出现错误，按顺序执行以下命令：
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- clean 
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- menuconfig 
	make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- uImage

##### 文件系统编译
1.  进入文件夹：/home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/busybox/busybox-1.20.2

2.  编译和安装 busybox
	编译和安装 busybox 的具体操作如下：
	hisilicon$ make 
	hisilicon$ make install 
	编译并安装成功后，在 busybox 目录下的_install 目录下生成以下目录及文件：
	drwxr-xr-x 2 lnan lnan 4096 2014-05-23 14:37 bin 
	lrwxrwxrwx 1 lnan lnan 11 2014-05-23 14:37 linuxrc -> bin/busybox 
	drwxr-xr-x 2 lnan lnan 4096 2014-05-23 14:37 sbin 
	drwxr-xr-x 4 lnan lnan 4096 2014-05-23 14:37 usr 

3.  制作根文件系统
	成功安装 SDK 后，在 osdrv/pub/目录中存放已制作好的根文件系统。
	用户如有需要可在 busybox 的基础上制作根文件系统。
	制作根文件系统的具体操作步骤如下：
	步骤 1. hisilicon$mkdir rootbox 
	hisilicon$cd rootbox 
	hisilicon$cp –R packet/os/busybox-1.20.2/_intsall/* . 
	hisilicon$mkdir etc dev lib tmp var mnt home proc 
	步骤 2. 配置 etc、lib、dev 目录的必需文件。
	a. etc 目录可参考系统/etc 下的文件。其中最主要的文件包括 inittab、fstab、init.d/rcS
	文件等，这些文件最好从 busybox 的 examples 目录下拷贝过来，根据需要自行修
	改。
	b. dev 目录下的设备文件，可以直接从系统中拷贝过来或者使用 mknod 命令生成需
	要的设备文件。拷贝文件时请使用 cp –R file。
	c. lib 目录是存放应用程序所需要的库文件，请根据应用程序需要拷贝相应的库文
	件。
	完成以上两个步骤，一个完整的根文件系统就生成了。


#### 交流学习
为海思专门创建的群【嵌入式交流】：https://jq.qq.com/?_wv=1027&k=K73tilmc
另一个交流群，看情况，可能会加不进去【嵌入式交流】：https://jq.qq.com/?_wv=1027&k=3bKuC7nh


