cmd_arch/arm/mach-hi3516a/swsusp.o := arm-hisiv300-linux-gcc -Wp,-MD,arch/arm/mach-hi3516a/.swsusp.o.d  -nostdinc -isystem /opt/hisi-linux/x86-arm/arm-hisiv300-linux/bin/../lib/gcc/arm-hisiv300-linux-uclibcgnueabi/4.8.3/include -I/home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-hi3516a/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -include asm/unified.h -Wa,-mfpu=softvfp+vfp        -c -o arch/arm/mach-hi3516a/swsusp.o arch/arm/mach-hi3516a/swsusp.S

source_arch/arm/mach-hi3516a/swsusp.o := arch/arm/mach-hi3516a/swsusp.S

deps_arch/arm/mach-hi3516a/swsusp.o := \
    $(wildcard include/config/debug/ll.h) \
    $(wildcard include/config/hisi/snapshot/boot.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/linkage.h \

arch/arm/mach-hi3516a/swsusp.o: $(deps_arch/arm/mach-hi3516a/swsusp.o)

$(deps_arch/arm/mach-hi3516a/swsusp.o):
