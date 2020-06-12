# hi3516dv100

#### 介绍
开源海思学习的过程，分享所有的软件和硬件资料。

#### 文件说明

1.  官方的SDK因为存在大的压缩包，传不上git，现在git中是有删减的
2.  获取官方的原始SDK可以加群下载，受后期项目的推进影响，官方资源可能不会适用于开源的硬件

#### 编译说明
uboot编译：
1.  进入文件夹：your_addr/hi3516dv100/3.software_source_code/osdrv/opensource/uboot/u-boot-2010.06
	make ARCH=arm CROSS_COMPILE=arm-hisivXXX-linux- hi3516a_config 
	或者
	make ARCH=arm CROSS_COMPILE=arm-hisivXXX-linux- hi3516a_spinand_config 
	编译成功后，将在U-boot目录下生成u-boot.bin。
	其中 hi3516a_config 为支持 SPI Flash 和 Nand Flash 的配置，hi3516a_spinand_config 为支持
	SPI-Nand Flash 的配置。
2.  编译U-boot：make ARCH=arm CROSS_COMPILE=arm-hisivXXX-linux-
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

kernel编译：
1.  进入文件夹：your_addr/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y
2.  配置内核：make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- menuconfig
	编译内核时需要在 make 后添加两个参数：ARCH=arm CROSS_COMPILE=arm-hisiXXX-linux-，其中 CROSS_COMPILE 表示工具链。
	文档中统一以 CROSS_COMPILE=arm-hisiXXX-linux-来表示两种情况。
	z Hi3516A_V100R001C01SPCxxx 对应 uclibc，使用 uclibc 工具链时，CROSS_COMPILE= arm-hisiv300-linux -。 z Hi3516A_V100R001C02SPCxxx 对应 glibc，使用 glibc 工具链时，CROSS_COMPILE=arm-hisiv400-linux-。
3.  编译内核：make ARCH=arm CROSS_COMPILE=arm-hisiv300-linux- uImage -j4
	如果编译过程中出现错误，按顺序执行以下命令：
	make ARCH=arm CROSS_COMPILE=arm-hisiXXX-linux- clean 
	make ARCH=arm CROSS_COMPILE=arm-hisiXXX-linux- menuconfig 
	make ARCH=arm CROSS_COMPILE=arm-hisiXXX-linux- uImage

#### 交流学习
为海思专门创建的群【嵌入式交流】：https://jq.qq.com/?_wv=1027&k=K73tilmc
另一个交流群，看情况，可能会加不进去【嵌入式交流】：https://jq.qq.com/?_wv=1027&k=3bKuC7nh


