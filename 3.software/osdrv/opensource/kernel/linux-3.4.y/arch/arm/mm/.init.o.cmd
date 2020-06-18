cmd_arch/arm/mm/init.o := arm-hisiv300-linux-gcc -Wp,-MD,arch/arm/mm/.init.o.d  -nostdinc -isystem /opt/hisi-linux/x86-arm/arm-hisiv300-linux/bin/../lib/gcc/arm-hisiv300-linux-uclibcgnueabi/4.8.3/include -I/home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-hi3516a/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -fno-aggressive-loop-optimizations -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(init)"  -D"KBUILD_MODNAME=KBUILD_STR(init)" -c -o arch/arm/mm/init.o arch/arm/mm/init.c

source_arch/arm/mm/init.o := arch/arm/mm/init.c

deps_arch/arm/mm/init.o := \
    $(wildcard include/config/of/flattree.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/xip/kernel.h) \
    $(wildcard include/config/blk/dev/initrd.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/sa1111.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/vectors/base.h) \
    $(wildcard include/config/mmu.h) \
  include/linux/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  include/linux/sysinfo.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/posix_types.h \
  include/asm-generic/posix_types.h \
  /opt/hisi-linux/x86-arm/arm-hisiv300-linux/lib/gcc/arm-hisiv300-linux-uclibcgnueabi/4.8.3/include/stdarg.h \
  include/linux/linkage.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/linkage.h \
  include/linux/bitops.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/bitops.h \
    $(wildcard include/config/smp.h) \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/linux/typecheck.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/irqflags.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/hwcap.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/swab.h \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/ext2-atomic-setbit.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/linux/init.h \
    $(wildcard include/config/hotplug.h) \
  include/linux/dynamic_debug.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/div64.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/compiler.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/debug/bugverbose.h) \
    $(wildcard include/config/arm/lpae.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  include/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/swap.h \
    $(wildcard include/config/migration.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr/swap.h) \
    $(wildcard include/config/swap.h) \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  include/linux/const.h \
  include/linux/stringify.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  include/linux/spinlock_types_up.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  include/linux/rwlock_types.h \
  include/linux/spinlock_up.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/hw_breakpoint.h \
  include/linux/rwlock.h \
  include/linux/spinlock_api_up.h \
  include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/atomic.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  include/asm-generic/cmpxchg-local.h \
  include/asm-generic/atomic-long.h \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/have/memblock/node.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/linux/wait.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/current.h \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/linux/seqlock.h \
  include/linux/nodemask.h \
  include/linux/bitmap.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/string.h \
  include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/glue.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/pgtable-2level-types.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
    $(wildcard include/config/hisi/snapshot/boot.h) \
  arch/arm/include/generated/asm/sizes.h \
  include/asm-generic/sizes.h \
  arch/arm/mach-hi3516a/include/mach/memory.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  include/asm-generic/getorder.h \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  include/linux/notifier.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  include/linux/mutex-debug.h \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  include/linux/rwsem-spinlock.h \
  include/linux/srcu.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/preempt/rt.h) \
  include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/linux/bug.h \
  include/linux/completion.h \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  include/linux/rcutiny.h \
  include/linux/memcontrol.h \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr/kmem.h) \
  include/linux/cgroup.h \
    $(wildcard include/config/cgroups.h) \
  include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/cfs/bandwidth.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/mm/owner.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  include/linux/capability.h \
  include/linux/timex.h \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/math64.h \
  include/linux/param.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/timex.h \
  arch/arm/mach-hi3516a/include/mach/timex.h \
  include/linux/jiffies.h \
  include/linux/rbtree.h \
  include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/have/cmpxchg/double.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
  include/linux/auxvec.h \
  arch/arm/include/generated/asm/auxvec.h \
  include/asm-generic/auxvec.h \
  include/linux/prio_tree.h \
  include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
  arch/arm/include/generated/asm/cputime.h \
  include/asm-generic/cputime.h \
  include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  include/linux/sem.h \
  include/linux/ipc.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/ipcbuf.h \
  include/asm-generic/ipcbuf.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/sembuf.h \
  include/linux/signal.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/signal.h \
  include/asm-generic/signal-defs.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/sigcontext.h \
  arch/arm/include/generated/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/linux/pid.h \
  include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/pfn.h \
  arch/arm/include/generated/asm/percpu.h \
  include/asm-generic/percpu.h \
  include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/topology.h \
    $(wildcard include/config/arm/cpu/topology.h) \
  include/asm-generic/topology.h \
  include/linux/proportions.h \
  include/linux/percpu_counter.h \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  include/linux/rculist.h \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/resource.h \
  arch/arm/include/generated/asm/resource.h \
  include/asm-generic/resource.h \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  include/linux/timerqueue.h \
  include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  include/linux/latencytop.h \
  include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/user/ns.h) \
  include/linux/key.h \
    $(wildcard include/config/sysctl.h) \
  include/linux/sysctl.h \
  include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  include/linux/aio.h \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  include/linux/aio_abi.h \
  include/linux/uio.h \
  include/linux/cgroupstats.h \
  include/linux/taskstats.h \
  include/linux/prio_heap.h \
  include/linux/gfp.h \
    $(wildcard include/config/pm/sleep.h) \
  include/linux/mmdebug.h \
    $(wildcard include/config/debug/virtual.h) \
  include/linux/idr.h \
  include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/debug.h) \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/net/cls/cgroup.h) \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/cgroup/perf.h) \
    $(wildcard include/config/netprio/cgroup.h) \
  include/linux/vm_event_item.h \
  include/linux/node.h \
    $(wildcard include/config/memory/hotplug/sparse.h) \
    $(wildcard include/config/hugetlbfs.h) \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  include/linux/ioport.h \
  include/linux/kobject.h \
  include/linux/sysfs.h \
    $(wildcard include/config/sysfs.h) \
  include/linux/kobject_ns.h \
  include/linux/kref.h \
  include/linux/klist.h \
  include/linux/pm.h \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/device.h \
    $(wildcard include/config/dmabounce.h) \
    $(wildcard include/config/iommu/api.h) \
    $(wildcard include/config/arch/omap.h) \
  include/linux/pm_wakeup.h \
  include/linux/bootmem.h \
    $(wildcard include/config/have/arch/bootmem/node.h) \
    $(wildcard include/config/have/arch/alloc/remap.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/dma.h \
    $(wildcard include/config/isa/dma/api.h) \
    $(wildcard include/config/pci.h) \
  include/linux/mman.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/mman.h \
  include/asm-generic/mman.h \
  include/asm-generic/mman-common.h \
    $(wildcard include/config/mmap/allow/uninitialized.h) \
  include/linux/mm.h \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hibernation.h) \
  include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  include/linux/range.h \
  include/linux/bit_spinlock.h \
  include/linux/shrinker.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/pgtable.h \
    $(wildcard include/config/highpte.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/proc-fns.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/glue-proc.h \
    $(wildcard include/config/cpu/arm610.h) \
    $(wildcard include/config/cpu/arm7tdmi.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/cpu/arm720t.h) \
    $(wildcard include/config/cpu/arm740t.h) \
    $(wildcard include/config/cpu/arm9tdmi.h) \
    $(wildcard include/config/cpu/arm920t.h) \
    $(wildcard include/config/cpu/arm922t.h) \
    $(wildcard include/config/cpu/arm925t.h) \
    $(wildcard include/config/cpu/arm926t.h) \
    $(wildcard include/config/cpu/arm940t.h) \
    $(wildcard include/config/cpu/arm946e.h) \
    $(wildcard include/config/cpu/arm1020.h) \
    $(wildcard include/config/cpu/arm1020e.h) \
    $(wildcard include/config/cpu/arm1022.h) \
    $(wildcard include/config/cpu/arm1026.h) \
    $(wildcard include/config/cpu/mohawk.h) \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/cpu/v6k.h) \
    $(wildcard include/config/cpu/v7.h) \
  include/asm-generic/pgtable-nopud.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/pgtable-hwdef.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/pgtable-2level-hwdef.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/pgtable-2level.h \
  include/asm-generic/pgtable.h \
  include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/s390.h) \
  include/linux/huge_mm.h \
  include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
  include/linux/export.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  include/linux/initrd.h \
  include/linux/of_fdt.h \
  include/linux/highmem.h \
    $(wildcard include/config/x86/32.h) \
    $(wildcard include/config/debug/highmem.h) \
  include/linux/fs.h \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/fs/xip.h) \
  include/linux/limits.h \
  include/linux/ioctl.h \
  arch/arm/include/generated/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/linux/blk_types.h \
    $(wildcard include/config/blk/dev/integrity.h) \
  include/linux/kdev_t.h \
  include/linux/dcache.h \
  include/linux/rculist_bl.h \
  include/linux/list_bl.h \
  include/linux/path.h \
  include/linux/stat.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/stat.h \
  include/linux/radix-tree.h \
  include/linux/semaphore.h \
  include/linux/fiemap.h \
  include/linux/migrate_mode.h \
  include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  include/linux/dqblk_xfs.h \
  include/linux/dqblk_v1.h \
  include/linux/dqblk_v2.h \
  include/linux/dqblk_qtree.h \
  include/linux/nfs_fs_i.h \
  include/linux/fcntl.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/fcntl.h \
  include/asm-generic/fcntl.h \
  include/linux/err.h \
  include/linux/uaccess.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/uaccess.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  include/linux/hardirq.h \
  include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/hardirq.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/irq.h \
    $(wildcard include/config/sparse/irq.h) \
  arch/arm/mach-hi3516a/include/mach/irqs.h \
  include/linux/irq_cpustat.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/cacheflush.h \
    $(wildcard include/config/smp/on/up.h) \
    $(wildcard include/config/arm/errata/411920.h) \
    $(wildcard include/config/cpu/cache/vipt.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/glue-cache.h \
    $(wildcard include/config/cpu/cache/v3.h) \
    $(wildcard include/config/cpu/cache/v4.h) \
    $(wildcard include/config/cpu/cache/v4wb.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/shmparam.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/cachetype.h \
    $(wildcard include/config/cpu/cache/vivt.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/rodata.h \
    $(wildcard include/config/debug/rodata.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/kmap_types.h \
  include/linux/memblock.h \
    $(wildcard include/config/have/memblock.h) \
    $(wildcard include/config/arch/discard/memblock.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/mach-types.h \
  include/generated/mach-types.h \
    $(wildcard include/config/arch/ebsa110.h) \
    $(wildcard include/config/arch/rpc.h) \
    $(wildcard include/config/arch/ebsa285.h) \
    $(wildcard include/config/arch/netwinder.h) \
    $(wildcard include/config/arch/cats.h) \
    $(wildcard include/config/arch/shark.h) \
    $(wildcard include/config/sa1100/brutus.h) \
    $(wildcard include/config/arch/personal/server.h) \
    $(wildcard include/config/arch/l7200.h) \
    $(wildcard include/config/sa1100/pleb.h) \
    $(wildcard include/config/arch/integrator.h) \
    $(wildcard include/config/sa1100/h3600.h) \
    $(wildcard include/config/arch/p720t.h) \
    $(wildcard include/config/sa1100/assabet.h) \
    $(wildcard include/config/sa1100/lart.h) \
    $(wildcard include/config/sa1100/graphicsclient.h) \
    $(wildcard include/config/sa1100/xp860.h) \
    $(wildcard include/config/sa1100/cerf.h) \
    $(wildcard include/config/sa1100/nanoengine.h) \
    $(wildcard include/config/sa1100/jornada720.h) \
    $(wildcard include/config/arch/edb7211.h) \
    $(wildcard include/config/sa1100/pfs168.h) \
    $(wildcard include/config/sa1100/flexanet.h) \
    $(wildcard include/config/sa1100/simpad.h) \
    $(wildcard include/config/arch/lubbock.h) \
    $(wildcard include/config/arch/clep7212.h) \
    $(wildcard include/config/sa1100/shannon.h) \
    $(wildcard include/config/sa1100/consus.h) \
    $(wildcard include/config/arch/aaed2000.h) \
    $(wildcard include/config/arch/cdb89712.h) \
    $(wildcard include/config/sa1100/graphicsmaster.h) \
    $(wildcard include/config/sa1100/adsbitsy.h) \
    $(wildcard include/config/arch/pxa/idp.h) \
    $(wildcard include/config/sa1100/pt/system3.h) \
    $(wildcard include/config/arch/autcpu12.h) \
    $(wildcard include/config/sa1100/h3100.h) \
    $(wildcard include/config/sa1100/collie.h) \
    $(wildcard include/config/sa1100/badge4.h) \
    $(wildcard include/config/arch/fortunet.h) \
    $(wildcard include/config/arch/mx1ads.h) \
    $(wildcard include/config/arch/h7201.h) \
    $(wildcard include/config/arch/h7202.h) \
    $(wildcard include/config/arch/iq80321.h) \
    $(wildcard include/config/arch/ks8695.h) \
    $(wildcard include/config/arch/karo.h) \
    $(wildcard include/config/arch/smdk2410.h) \
    $(wildcard include/config/arch/ceiva.h) \
    $(wildcard include/config/mach/voiceblue.h) \
    $(wildcard include/config/arch/h5400.h) \
    $(wildcard include/config/mach/omap/innovator.h) \
    $(wildcard include/config/arch/ixdp2400.h) \
    $(wildcard include/config/arch/ixdp2800.h) \
    $(wildcard include/config/arch/ixdp425.h) \
    $(wildcard include/config/sa1100/hackkit.h) \
    $(wildcard include/config/arch/ixcdp1100.h) \
    $(wildcard include/config/arch/at91rm9200dk.h) \
    $(wildcard include/config/arch/cintegrator.h) \
    $(wildcard include/config/arch/viper.h) \
    $(wildcard include/config/arch/adi/coyote.h) \
    $(wildcard include/config/arch/ixdp2401.h) \
    $(wildcard include/config/arch/ixdp2801.h) \
    $(wildcard include/config/arch/iq31244.h) \
    $(wildcard include/config/arch/bast.h) \
    $(wildcard include/config/arch/h1940.h) \
    $(wildcard include/config/arch/enp2611.h) \
    $(wildcard include/config/arch/s3c2440.h) \
    $(wildcard include/config/arch/gumstix.h) \
    $(wildcard include/config/mach/omap/h2.h) \
    $(wildcard include/config/mach/e740.h) \
    $(wildcard include/config/arch/iq80331.h) \
    $(wildcard include/config/arch/versatile/pb.h) \
    $(wildcard include/config/mach/kev7a400.h) \
    $(wildcard include/config/mach/lpd7a400.h) \
    $(wildcard include/config/mach/lpd7a404.h) \
    $(wildcard include/config/mach/csb337.h) \
    $(wildcard include/config/mach/mainstone.h) \
    $(wildcard include/config/mach/xcep.h) \
    $(wildcard include/config/mach/arcom/vulcan.h) \
    $(wildcard include/config/mach/nomadik.h) \
    $(wildcard include/config/mach/corgi.h) \
    $(wildcard include/config/mach/poodle.h) \
    $(wildcard include/config/mach/armcore.h) \
    $(wildcard include/config/mach/mx31ads.h) \
    $(wildcard include/config/mach/himalaya.h) \
    $(wildcard include/config/mach/edb9312.h) \
    $(wildcard include/config/mach/omap/generic.h) \
    $(wildcard include/config/mach/edb9301.h) \
    $(wildcard include/config/mach/edb9315.h) \
    $(wildcard include/config/mach/vr1000.h) \
    $(wildcard include/config/mach/omap/perseus2.h) \
    $(wildcard include/config/mach/e800.h) \
    $(wildcard include/config/mach/e750.h) \
    $(wildcard include/config/mach/scb9328.h) \
    $(wildcard include/config/mach/omap/h3.h) \
    $(wildcard include/config/mach/omap/h4.h) \
    $(wildcard include/config/mach/omap/osk.h) \
    $(wildcard include/config/mach/tosa.h) \
    $(wildcard include/config/mach/avila.h) \
    $(wildcard include/config/mach/edb9302.h) \
    $(wildcard include/config/mach/husky.h) \
    $(wildcard include/config/mach/shepherd.h) \
    $(wildcard include/config/mach/h4700.h) \
    $(wildcard include/config/mach/rx3715.h) \
    $(wildcard include/config/mach/nslu2.h) \
    $(wildcard include/config/mach/e400.h) \
    $(wildcard include/config/mach/ixdpg425.h) \
    $(wildcard include/config/mach/versatile/ab.h) \
    $(wildcard include/config/mach/edb9307.h) \
    $(wildcard include/config/mach/kb9200.h) \
    $(wildcard include/config/mach/sx1.h) \
    $(wildcard include/config/mach/ixdp465.h) \
    $(wildcard include/config/mach/ixdp2351.h) \
    $(wildcard include/config/mach/iq80332.h) \
    $(wildcard include/config/mach/gtwx5715.h) \
    $(wildcard include/config/mach/csb637.h) \
    $(wildcard include/config/mach/n30.h) \
    $(wildcard include/config/mach/nec/mp900.h) \
    $(wildcard include/config/mach/kafa.h) \
    $(wildcard include/config/mach/ts72xx.h) \
    $(wildcard include/config/mach/otom.h) \
    $(wildcard include/config/mach/nexcoder/2440.h) \
    $(wildcard include/config/mach/eco920.h) \
    $(wildcard include/config/mach/roadrunner.h) \
    $(wildcard include/config/mach/at91rm9200ek.h) \
    $(wildcard include/config/mach/spitz.h) \
    $(wildcard include/config/mach/adssphere.h) \
    $(wildcard include/config/mach/colibri.h) \
    $(wildcard include/config/mach/gateway7001.h) \
    $(wildcard include/config/mach/pcm027.h) \
    $(wildcard include/config/mach/anubis.h) \
    $(wildcard include/config/mach/akita.h) \
    $(wildcard include/config/mach/e330.h) \
    $(wildcard include/config/mach/nokia770.h) \
    $(wildcard include/config/mach/carmeva.h) \
    $(wildcard include/config/mach/edb9315a.h) \
    $(wildcard include/config/mach/stargate2.h) \
    $(wildcard include/config/mach/intelmote2.h) \
    $(wildcard include/config/mach/trizeps4.h) \
    $(wildcard include/config/mach/pnx4008.h) \
    $(wildcard include/config/mach/cpuat91.h) \
    $(wildcard include/config/mach/iq81340sc.h) \
    $(wildcard include/config/mach/iq81340mc.h) \
    $(wildcard include/config/mach/micro9.h) \
    $(wildcard include/config/mach/micro9l.h) \
    $(wildcard include/config/mach/omap/palmte.h) \
    $(wildcard include/config/mach/realview/eb.h) \
    $(wildcard include/config/mach/borzoi.h) \
    $(wildcard include/config/mach/palmld.h) \
    $(wildcard include/config/mach/ixdp28x5.h) \
    $(wildcard include/config/mach/omap/palmtt.h) \
    $(wildcard include/config/mach/arcom/zeus.h) \
    $(wildcard include/config/mach/osiris.h) \
    $(wildcard include/config/mach/palmte2.h) \
    $(wildcard include/config/mach/mx27ads.h) \
    $(wildcard include/config/mach/at91sam9261ek.h) \
    $(wildcard include/config/mach/loft.h) \
    $(wildcard include/config/mach/mx21ads.h) \
    $(wildcard include/config/mach/ams/delta.h) \
    $(wildcard include/config/mach/nas100d.h) \
    $(wildcard include/config/mach/magician.h) \
    $(wildcard include/config/mach/nxdkn.h) \
    $(wildcard include/config/mach/palmtx.h) \
    $(wildcard include/config/mach/s3c2413.h) \
    $(wildcard include/config/mach/wg302v2.h) \
    $(wildcard include/config/mach/omap/2430sdp.h) \
    $(wildcard include/config/mach/davinci/evm.h) \
    $(wildcard include/config/mach/palmz72.h) \
    $(wildcard include/config/mach/nxdb500.h) \
    $(wildcard include/config/mach/apf9328.h) \
    $(wildcard include/config/mach/palmt5.h) \
    $(wildcard include/config/mach/palmtc.h) \
    $(wildcard include/config/mach/omap/apollon.h) \
    $(wildcard include/config/mach/ateb9200.h) \
    $(wildcard include/config/mach/n35.h) \
    $(wildcard include/config/mach/logicpd/pxa270.h) \
    $(wildcard include/config/mach/nxeb500hmi.h) \
    $(wildcard include/config/mach/espresso.h) \
    $(wildcard include/config/mach/rx1950.h) \
    $(wildcard include/config/mach/gesbc9312.h) \
    $(wildcard include/config/mach/picotux2xx.h) \
    $(wildcard include/config/mach/dsmg600.h) \
    $(wildcard include/config/mach/omap/fsample.h) \
    $(wildcard include/config/mach/snapper/cl15.h) \
    $(wildcard include/config/mach/omap/palmz71.h) \
    $(wildcard include/config/mach/smdk2412.h) \
    $(wildcard include/config/mach/smdk2413.h) \
    $(wildcard include/config/mach/aml/m5900.h) \
    $(wildcard include/config/mach/balloon3.h) \
    $(wildcard include/config/mach/ecbat91.h) \
    $(wildcard include/config/mach/onearm.h) \
    $(wildcard include/config/mach/smdk2443.h) \
    $(wildcard include/config/mach/fsg.h) \
    $(wildcard include/config/mach/at91sam9260ek.h) \
    $(wildcard include/config/mach/glantank.h) \
    $(wildcard include/config/mach/n2100.h) \
    $(wildcard include/config/mach/qt2410.h) \
    $(wildcard include/config/mach/kixrp435.h) \
    $(wildcard include/config/mach/cc9p9360dev.h) \
    $(wildcard include/config/mach/edb9302a.h) \
    $(wildcard include/config/mach/edb9307a.h) \
    $(wildcard include/config/mach/omap/3430sdp.h) \
    $(wildcard include/config/mach/vstms.h) \
    $(wildcard include/config/mach/micro9m.h) \
    $(wildcard include/config/mach/bug.h) \
    $(wildcard include/config/mach/at91sam9263ek.h) \
    $(wildcard include/config/mach/em7210.h) \
    $(wildcard include/config/mach/vpac270.h) \
    $(wildcard include/config/mach/treo680.h) \
    $(wildcard include/config/mach/zylonite.h) \
    $(wildcard include/config/mach/mx31lite.h) \
    $(wildcard include/config/mach/mioa701.h) \
    $(wildcard include/config/mach/armadillo5x0.h) \
    $(wildcard include/config/mach/cc9p9360js.h) \
    $(wildcard include/config/mach/smdk6400.h) \
    $(wildcard include/config/mach/nokia/n800.h) \
    $(wildcard include/config/mach/ep80219.h) \
    $(wildcard include/config/mach/goramo/mlr.h) \
    $(wildcard include/config/mach/em/x270.h) \
    $(wildcard include/config/mach/neo1973/gta02.h) \
    $(wildcard include/config/mach/at91sam9rlek.h) \
    $(wildcard include/config/mach/colibri320.h) \
    $(wildcard include/config/mach/cam60.h) \
    $(wildcard include/config/mach/at91eb01.h) \
    $(wildcard include/config/mach/db88f5281.h) \
    $(wildcard include/config/mach/csb726.h) \
    $(wildcard include/config/mach/davinci/dm6467/evm.h) \
    $(wildcard include/config/mach/davinci/dm355/evm.h) \
    $(wildcard include/config/mach/littleton.h) \
    $(wildcard include/config/mach/realview/pb11mp.h) \
    $(wildcard include/config/mach/mx27/3ds.h) \
    $(wildcard include/config/mach/halibut.h) \
    $(wildcard include/config/mach/trout.h) \
    $(wildcard include/config/mach/tct/hammer.h) \
    $(wildcard include/config/mach/herald.h) \
    $(wildcard include/config/mach/sim/one.h) \
    $(wildcard include/config/mach/jive.h) \
    $(wildcard include/config/mach/sam9/l9260.h) \
    $(wildcard include/config/mach/realview/pb1176.h) \
    $(wildcard include/config/mach/yl9200.h) \
    $(wildcard include/config/mach/rd88f5182.h) \
    $(wildcard include/config/mach/kurobox/pro.h) \
    $(wildcard include/config/mach/mx31/3ds.h) \
    $(wildcard include/config/mach/qong.h) \
    $(wildcard include/config/mach/omap2evm.h) \
    $(wildcard include/config/mach/omap3evm.h) \
    $(wildcard include/config/mach/dns323.h) \
    $(wildcard include/config/mach/omap3/beagle.h) \
    $(wildcard include/config/mach/nokia/n810.h) \
    $(wildcard include/config/mach/pcm038.h) \
    $(wildcard include/config/mach/ts209.h) \
    $(wildcard include/config/mach/at91cap9adk.h) \
    $(wildcard include/config/mach/mx31moboard.h) \
    $(wildcard include/config/mach/vision/ep9307.h) \
    $(wildcard include/config/mach/terastation/pro2.h) \
    $(wildcard include/config/mach/linkstation/pro.h) \
    $(wildcard include/config/mach/e350.h) \
    $(wildcard include/config/mach/ts409.h) \
    $(wildcard include/config/mach/rsi/ews.h) \
    $(wildcard include/config/mach/cm/x300.h) \
    $(wildcard include/config/mach/at91sam9g20ek.h) \
    $(wildcard include/config/mach/smdk6410.h) \
    $(wildcard include/config/mach/u300.h) \
    $(wildcard include/config/mach/wrt350n/v2.h) \
    $(wildcard include/config/mach/omap/ldp.h) \
    $(wildcard include/config/mach/mx35/3ds.h) \
    $(wildcard include/config/mach/neuros/osd2.h) \
    $(wildcard include/config/mach/trizeps4wl.h) \
    $(wildcard include/config/mach/ts78xx.h) \
    $(wildcard include/config/mach/sffsdr.h) \
    $(wildcard include/config/mach/pcm037.h) \
    $(wildcard include/config/mach/db88f6281/bp.h) \
    $(wildcard include/config/mach/rd88f6192/nas.h) \
    $(wildcard include/config/mach/rd88f6281.h) \
    $(wildcard include/config/mach/db78x00/bp.h) \
    $(wildcard include/config/mach/smdk2416.h) \
    $(wildcard include/config/mach/wbd111.h) \
    $(wildcard include/config/mach/mv2120.h) \
    $(wildcard include/config/mach/mx51/3ds.h) \
    $(wildcard include/config/mach/imx27lite.h) \
    $(wildcard include/config/mach/usb/a9260.h) \
    $(wildcard include/config/mach/usb/a9263.h) \
    $(wildcard include/config/mach/qil/a9260.h) \
    $(wildcard include/config/mach/kzm/arm11/01.h) \
    $(wildcard include/config/mach/nokia/n810/wimax.h) \
    $(wildcard include/config/mach/sapphire.h) \
    $(wildcard include/config/mach/stmp37xx.h) \
    $(wildcard include/config/mach/stmp378x.h) \
    $(wildcard include/config/mach/ezx/a780.h) \
    $(wildcard include/config/mach/ezx/e680.h) \
    $(wildcard include/config/mach/ezx/a1200.h) \
    $(wildcard include/config/mach/ezx/e6.h) \
    $(wildcard include/config/mach/ezx/e2.h) \
    $(wildcard include/config/mach/ezx/a910.h) \
    $(wildcard include/config/mach/edmini/v2.h) \
    $(wildcard include/config/mach/zipit2.h) \
    $(wildcard include/config/mach/omap3/pandora.h) \
    $(wildcard include/config/mach/mss2.h) \
    $(wildcard include/config/mach/lb88rc8480.h) \
    $(wildcard include/config/mach/mx25/3ds.h) \
    $(wildcard include/config/mach/omap3530/lv/som.h) \
    $(wildcard include/config/mach/davinci/da830/evm.h) \
    $(wildcard include/config/mach/dove/db.h) \
    $(wildcard include/config/mach/overo.h) \
    $(wildcard include/config/mach/at2440evb.h) \
    $(wildcard include/config/mach/neocore926.h) \
    $(wildcard include/config/mach/wnr854t.h) \
    $(wildcard include/config/mach/rd88f5181l/ge.h) \
    $(wildcard include/config/mach/rd88f5181l/fxo.h) \
    $(wildcard include/config/mach/stamp9g20.h) \
    $(wildcard include/config/mach/smdkc100.h) \
    $(wildcard include/config/mach/tavorevb.h) \
    $(wildcard include/config/mach/saar.h) \
    $(wildcard include/config/mach/at91sam9m10g45ek.h) \
    $(wildcard include/config/mach/usb/a9g20.h) \
    $(wildcard include/config/mach/mxlads.h) \
    $(wildcard include/config/mach/linkstation/mini.h) \
    $(wildcard include/config/mach/afeb9260.h) \
    $(wildcard include/config/mach/imx27ipcam.h) \
    $(wildcard include/config/mach/rd88f6183ap/ge.h) \
    $(wildcard include/config/mach/realview/pba8.h) \
    $(wildcard include/config/mach/realview/pbx.h) \
    $(wildcard include/config/mach/micro9s.h) \
    $(wildcard include/config/mach/rut100.h) \
    $(wildcard include/config/mach/g3evm.h) \
    $(wildcard include/config/mach/w90p910evb.h) \
    $(wildcard include/config/mach/w90p950evb.h) \
    $(wildcard include/config/mach/w90n960evb.h) \
    $(wildcard include/config/mach/mv88f6281gtw/ge.h) \
    $(wildcard include/config/mach/ncp.h) \
    $(wildcard include/config/mach/davinci/dm365/evm.h) \
    $(wildcard include/config/mach/centro.h) \
    $(wildcard include/config/mach/nokia/rx51.h) \
    $(wildcard include/config/mach/omap/zoom2.h) \
    $(wildcard include/config/mach/cpuat9260.h) \
    $(wildcard include/config/mach/eukrea/cpuimx27.h) \
    $(wildcard include/config/mach/acs5k.h) \
    $(wildcard include/config/mach/snapper/9260.h) \
    $(wildcard include/config/mach/dsm320.h) \
    $(wildcard include/config/mach/exeda.h) \
    $(wildcard include/config/mach/mini2440.h) \
    $(wildcard include/config/mach/colibri300.h) \
    $(wildcard include/config/mach/linkstation/ls/hgl.h) \
    $(wildcard include/config/mach/cpuat9g20.h) \
    $(wildcard include/config/mach/smdk6440.h) \
    $(wildcard include/config/mach/nas4220b.h) \
    $(wildcard include/config/mach/zylonite2.h) \
    $(wildcard include/config/mach/aspenite.h) \
    $(wildcard include/config/mach/ttc/dkb.h) \
    $(wildcard include/config/mach/pcm043.h) \
    $(wildcard include/config/mach/sheevaplug.h) \
    $(wildcard include/config/mach/avengers/lite.h) \
    $(wildcard include/config/mach/mx51/babbage.h) \
    $(wildcard include/config/mach/tx37.h) \
    $(wildcard include/config/mach/rd78x00/masa.h) \
    $(wildcard include/config/mach/dm355/leopard.h) \
    $(wildcard include/config/mach/ts219.h) \
    $(wildcard include/config/mach/pca100.h) \
    $(wildcard include/config/mach/davinci/da850/evm.h) \
    $(wildcard include/config/mach/at91sam9g10ek.h) \
    $(wildcard include/config/mach/omap/4430sdp.h) \
    $(wildcard include/config/mach/magx/zn5.h) \
    $(wildcard include/config/mach/btmavb101.h) \
    $(wildcard include/config/mach/btmawb101.h) \
    $(wildcard include/config/mach/tx25.h) \
    $(wildcard include/config/mach/omap3/torpedo.h) \
    $(wildcard include/config/mach/anw6410.h) \
    $(wildcard include/config/mach/imx27/visstrim/m10.h) \
    $(wildcard include/config/mach/portuxg20.h) \
    $(wildcard include/config/mach/smdkc110.h) \
    $(wildcard include/config/mach/omap3517evm.h) \
    $(wildcard include/config/mach/netspace/v2.h) \
    $(wildcard include/config/mach/netspace/max/v2.h) \
    $(wildcard include/config/mach/d2net/v2.h) \
    $(wildcard include/config/mach/net2big/v2.h) \
    $(wildcard include/config/mach/net5big/v2.h) \
    $(wildcard include/config/mach/inetspace/v2.h) \
    $(wildcard include/config/mach/at91sam9g45ekes.h) \
    $(wildcard include/config/mach/pc7302.h) \
    $(wildcard include/config/mach/spear600.h) \
    $(wildcard include/config/mach/spear300.h) \
    $(wildcard include/config/mach/lilly1131.h) \
    $(wildcard include/config/mach/hmt.h) \
    $(wildcard include/config/mach/vexpress.h) \
    $(wildcard include/config/mach/d2net.h) \
    $(wildcard include/config/mach/bigdisk.h) \
    $(wildcard include/config/mach/at91sam9g20ek/2mmc.h) \
    $(wildcard include/config/mach/bcmring.h) \
    $(wildcard include/config/mach/dp6xx.h) \
    $(wildcard include/config/mach/mahimahi.h) \
    $(wildcard include/config/mach/smdk6442.h) \
    $(wildcard include/config/mach/openrd/base.h) \
    $(wildcard include/config/mach/devkit8000.h) \
    $(wildcard include/config/mach/mx51/efikamx.h) \
    $(wildcard include/config/mach/cm/t35.h) \
    $(wildcard include/config/mach/net2big.h) \
    $(wildcard include/config/mach/igep0020.h) \
    $(wildcard include/config/mach/nuc932evb.h) \
    $(wildcard include/config/mach/openrd/client.h) \
    $(wildcard include/config/mach/u8500.h) \
    $(wildcard include/config/mach/mx51/efikasb.h) \
    $(wildcard include/config/mach/marvell/jasper.h) \
    $(wildcard include/config/mach/flint.h) \
    $(wildcard include/config/mach/tavorevb3.h) \
    $(wildcard include/config/mach/touchbook.h) \
    $(wildcard include/config/mach/raumfeld/rc.h) \
    $(wildcard include/config/mach/raumfeld/connector.h) \
    $(wildcard include/config/mach/raumfeld/speaker.h) \
    $(wildcard include/config/mach/tnetv107x.h) \
    $(wildcard include/config/mach/mx51/m2id.h) \
    $(wildcard include/config/mach/smdkv210.h) \
    $(wildcard include/config/mach/omap/zoom3.h) \
    $(wildcard include/config/mach/omap/3630sdp.h) \
    $(wildcard include/config/mach/smartq7.h) \
    $(wildcard include/config/mach/watson/efm/plugin.h) \
    $(wildcard include/config/mach/g4evm.h) \
    $(wildcard include/config/mach/omapl138/hawkboard.h) \
    $(wildcard include/config/mach/ts41x.h) \
    $(wildcard include/config/mach/phy3250.h) \
    $(wildcard include/config/mach/mini6410.h) \
    $(wildcard include/config/mach/tx51.h) \
    $(wildcard include/config/mach/mx28evk.h) \
    $(wildcard include/config/mach/smartq5.h) \
    $(wildcard include/config/mach/davinci/dm6467tevm.h) \
    $(wildcard include/config/mach/mxt/td60.h) \
    $(wildcard include/config/mach/riot/bei2.h) \
    $(wildcard include/config/mach/riot/x37.h) \
    $(wildcard include/config/mach/pca101.h) \
    $(wildcard include/config/mach/capc7117.h) \
    $(wildcard include/config/mach/icontrol.h) \
    $(wildcard include/config/mach/gplugd.h) \
    $(wildcard include/config/mach/qsd8x50a/st1/5.h) \
    $(wildcard include/config/mach/mx23evk.h) \
    $(wildcard include/config/mach/ap4evb.h) \
    $(wildcard include/config/mach/mityomapl138.h) \
    $(wildcard include/config/mach/guruplug.h) \
    $(wildcard include/config/mach/spear310.h) \
    $(wildcard include/config/mach/spear320.h) \
    $(wildcard include/config/mach/aquila.h) \
    $(wildcard include/config/mach/esata/sheevaplug.h) \
    $(wildcard include/config/mach/msm7x30/surf.h) \
    $(wildcard include/config/mach/ea2478devkit.h) \
    $(wildcard include/config/mach/terastation/wxl.h) \
    $(wildcard include/config/mach/msm7x25/surf.h) \
    $(wildcard include/config/mach/msm7x25/ffa.h) \
    $(wildcard include/config/mach/msm7x27/surf.h) \
    $(wildcard include/config/mach/msm7x27/ffa.h) \
    $(wildcard include/config/mach/msm7x30/ffa.h) \
    $(wildcard include/config/mach/qsd8x50/surf.h) \
    $(wildcard include/config/mach/mx53/evk.h) \
    $(wildcard include/config/mach/igep0030.h) \
    $(wildcard include/config/mach/sbc3530.h) \
    $(wildcard include/config/mach/saarb.h) \
    $(wildcard include/config/mach/harmony.h) \
    $(wildcard include/config/mach/msm7x30/fluid.h) \
    $(wildcard include/config/mach/cm/t3517.h) \
    $(wildcard include/config/mach/wbd222.h) \
    $(wildcard include/config/mach/msm8x60/surf.h) \
    $(wildcard include/config/mach/msm8x60/sim.h) \
    $(wildcard include/config/mach/tcc8000/sdk.h) \
    $(wildcard include/config/mach/nanos.h) \
    $(wildcard include/config/mach/stamp9g45.h) \
    $(wildcard include/config/mach/cns3420vb.h) \
    $(wildcard include/config/mach/omap4/panda.h) \
    $(wildcard include/config/mach/ti8168evm.h) \
    $(wildcard include/config/mach/teton/bga.h) \
    $(wildcard include/config/mach/eukrea/cpuimx25sd.h) \
    $(wildcard include/config/mach/eukrea/cpuimx35sd.h) \
    $(wildcard include/config/mach/eukrea/cpuimx51sd.h) \
    $(wildcard include/config/mach/eukrea/cpuimx51.h) \
    $(wildcard include/config/mach/smdkc210.h) \
    $(wildcard include/config/mach/pca102.h) \
    $(wildcard include/config/mach/t5325.h) \
    $(wildcard include/config/mach/income.h) \
    $(wildcard include/config/mach/vvbox/sdorig2.h) \
    $(wildcard include/config/mach/vvbox/sdlite2.h) \
    $(wildcard include/config/mach/vvbox/sdpro4.h) \
    $(wildcard include/config/mach/mx257sx.h) \
    $(wildcard include/config/mach/goni.h) \
    $(wildcard include/config/mach/bv07.h) \
    $(wildcard include/config/mach/openrd/ultimate.h) \
    $(wildcard include/config/mach/devixp.h) \
    $(wildcard include/config/mach/miccpt.h) \
    $(wildcard include/config/mach/mic256.h) \
    $(wildcard include/config/mach/u5500.h) \
    $(wildcard include/config/mach/linkstation/lschl.h) \
    $(wildcard include/config/mach/smdkv310.h) \
    $(wildcard include/config/mach/wm8505/7in/netbook.h) \
    $(wildcard include/config/mach/craneboard.h) \
    $(wildcard include/config/mach/smdk6450.h) \
    $(wildcard include/config/mach/brownstone.h) \
    $(wildcard include/config/mach/flexibity.h) \
    $(wildcard include/config/mach/mx50/rdp.h) \
    $(wildcard include/config/mach/universal/c210.h) \
    $(wildcard include/config/mach/real6410.h) \
    $(wildcard include/config/mach/dockstar.h) \
    $(wildcard include/config/mach/ti8148evm.h) \
    $(wildcard include/config/mach/seaboard.h) \
    $(wildcard include/config/mach/mx53/ard.h) \
    $(wildcard include/config/mach/mx53/smd.h) \
    $(wildcard include/config/mach/msm8x60/rumi3.h) \
    $(wildcard include/config/mach/msm8x60/ffa.h) \
    $(wildcard include/config/mach/cm/a510.h) \
    $(wildcard include/config/mach/tx28.h) \
    $(wildcard include/config/mach/pcontrol/g20.h) \
    $(wildcard include/config/mach/vpr200.h) \
    $(wildcard include/config/mach/torbreck.h) \
    $(wildcard include/config/mach/prima2/evb.h) \
    $(wildcard include/config/mach/paz00.h) \
    $(wildcard include/config/mach/acmenetusfoxg20.h) \
    $(wildcard include/config/mach/ag5evm.h) \
    $(wildcard include/config/mach/tsunagi.h) \
    $(wildcard include/config/mach/ics/if/voip.h) \
    $(wildcard include/config/mach/wlf/cragg/6410.h) \
    $(wildcard include/config/mach/trimslice.h) \
    $(wildcard include/config/mach/mackerel.h) \
    $(wildcard include/config/mach/kaen.h) \
    $(wildcard include/config/mach/nokia/rm680.h) \
    $(wildcard include/config/mach/dm6446/adbox.h) \
    $(wildcard include/config/mach/quad/salsa.h) \
    $(wildcard include/config/mach/abb/gma/1/1.h) \
    $(wildcard include/config/mach/svcid.h) \
    $(wildcard include/config/mach/msm8960/sim.h) \
    $(wildcard include/config/mach/msm8960/rumi3.h) \
    $(wildcard include/config/mach/icon/g.h) \
    $(wildcard include/config/mach/mb3.h) \
    $(wildcard include/config/mach/gsia18s.h) \
    $(wildcard include/config/mach/pivicc.h) \
    $(wildcard include/config/mach/pcm048.h) \
    $(wildcard include/config/mach/dds.h) \
    $(wildcard include/config/mach/chalten/xa1.h) \
    $(wildcard include/config/mach/ts48xx.h) \
    $(wildcard include/config/mach/tonga2/tfttimer.h) \
    $(wildcard include/config/mach/whistler.h) \
    $(wildcard include/config/mach/asl/phoenix.h) \
    $(wildcard include/config/mach/at91sam9263otlite.h) \
    $(wildcard include/config/mach/ddplug.h) \
    $(wildcard include/config/mach/d2plug.h) \
    $(wildcard include/config/mach/kzm9d.h) \
    $(wildcard include/config/mach/verdi/lte.h) \
    $(wildcard include/config/mach/nanozoom.h) \
    $(wildcard include/config/mach/dm3730/som/lv.h) \
    $(wildcard include/config/mach/dm3730/torpedo.h) \
    $(wildcard include/config/mach/anchovy.h) \
    $(wildcard include/config/mach/re2rev20.h) \
    $(wildcard include/config/mach/re2rev21.h) \
    $(wildcard include/config/mach/cns21xx.h) \
    $(wildcard include/config/mach/rider.h) \
    $(wildcard include/config/mach/nsk330.h) \
    $(wildcard include/config/mach/cns2133evb.h) \
    $(wildcard include/config/mach/z3/816x/mod.h) \
    $(wildcard include/config/mach/z3/814x/mod.h) \
    $(wildcard include/config/mach/beect.h) \
    $(wildcard include/config/mach/dma/thunderbug.h) \
    $(wildcard include/config/mach/omn/at91sam9g20.h) \
    $(wildcard include/config/mach/mx25/e2s/uc.h) \
    $(wildcard include/config/mach/mione.h) \
    $(wildcard include/config/mach/top9000/tcu.h) \
    $(wildcard include/config/mach/top9000/bsl.h) \
    $(wildcard include/config/mach/kingdom.h) \
    $(wildcard include/config/mach/armadillo460.h) \
    $(wildcard include/config/mach/lq2.h) \
    $(wildcard include/config/mach/sweda/tms2.h) \
    $(wildcard include/config/mach/mx53/loco.h) \
    $(wildcard include/config/mach/acer/a8.h) \
    $(wildcard include/config/mach/acer/gauguin.h) \
    $(wildcard include/config/mach/guppy.h) \
    $(wildcard include/config/mach/mx61/ard.h) \
    $(wildcard include/config/mach/tx53.h) \
    $(wildcard include/config/mach/omapl138/case/a3.h) \
    $(wildcard include/config/mach/uemd.h) \
    $(wildcard include/config/mach/ccwmx51mut.h) \
    $(wildcard include/config/mach/rockhopper.h) \
    $(wildcard include/config/mach/encore.h) \
    $(wildcard include/config/mach/hkdkc100.h) \
    $(wildcard include/config/mach/ts42xx.h) \
    $(wildcard include/config/mach/aebl.h) \
    $(wildcard include/config/mach/wario.h) \
    $(wildcard include/config/mach/gfs/spm.h) \
    $(wildcard include/config/mach/cm/t3730.h) \
    $(wildcard include/config/mach/isc3.h) \
    $(wildcard include/config/mach/rascal.h) \
    $(wildcard include/config/mach/hrefv60.h) \
    $(wildcard include/config/mach/tpt/2/0.h) \
    $(wildcard include/config/mach/splendor.h) \
    $(wildcard include/config/mach/msm8x60/qt.h) \
    $(wildcard include/config/mach/htc/hd/mini.h) \
    $(wildcard include/config/mach/athene.h) \
    $(wildcard include/config/mach/deep/r/ek/1.h) \
    $(wildcard include/config/mach/vivow/ct.h) \
    $(wildcard include/config/mach/nery/1000.h) \
    $(wildcard include/config/mach/rfl109145/ssrv.h) \
    $(wildcard include/config/mach/nmh.h) \
    $(wildcard include/config/mach/wn802t.h) \
    $(wildcard include/config/mach/dragonet.h) \
    $(wildcard include/config/mach/at91sam9263desk16l.h) \
    $(wildcard include/config/mach/bcmhana/sv.h) \
    $(wildcard include/config/mach/bcmhana/tablet.h) \
    $(wildcard include/config/mach/koi.h) \
    $(wildcard include/config/mach/ts4800.h) \
    $(wildcard include/config/mach/tqma9263.h) \
    $(wildcard include/config/mach/holiday.h) \
    $(wildcard include/config/mach/pcats/overlay.h) \
    $(wildcard include/config/mach/hwgw6410.h) \
    $(wildcard include/config/mach/shenzhou.h) \
    $(wildcard include/config/mach/cwme9210.h) \
    $(wildcard include/config/mach/cwme9210js.h) \
    $(wildcard include/config/mach/colibri/tegra2.h) \
    $(wildcard include/config/mach/w21.h) \
    $(wildcard include/config/mach/polysat1.h) \
    $(wildcard include/config/mach/dataway.h) \
    $(wildcard include/config/mach/cobral138.h) \
    $(wildcard include/config/mach/roverpcs8.h) \
    $(wildcard include/config/mach/marvelc.h) \
    $(wildcard include/config/mach/navefihid.h) \
    $(wildcard include/config/mach/dm365/cv100.h) \
    $(wildcard include/config/mach/able.h) \
    $(wildcard include/config/mach/legacy.h) \
    $(wildcard include/config/mach/icong.h) \
    $(wildcard include/config/mach/rover/g8.h) \
    $(wildcard include/config/mach/t5388p.h) \
    $(wildcard include/config/mach/dingo.h) \
    $(wildcard include/config/mach/goflexhome.h) \
    $(wildcard include/config/mach/lanreadyfn511.h) \
    $(wildcard include/config/mach/omap3/baia.h) \
    $(wildcard include/config/mach/omap3smartdisplay.h) \
    $(wildcard include/config/mach/xilinx.h) \
    $(wildcard include/config/mach/a2f.h) \
    $(wildcard include/config/mach/sky25.h) \
    $(wildcard include/config/mach/ccmx53.h) \
    $(wildcard include/config/mach/ccmx53js.h) \
    $(wildcard include/config/mach/ccwmx53.h) \
    $(wildcard include/config/mach/ccwmx53js.h) \
    $(wildcard include/config/mach/frisms.h) \
    $(wildcard include/config/mach/msm7x27a/ffa.h) \
    $(wildcard include/config/mach/msm7x27a/surf.h) \
    $(wildcard include/config/mach/msm7x27a/rumi3.h) \
    $(wildcard include/config/mach/dimmsam9g20.h) \
    $(wildcard include/config/mach/dimm/imx28.h) \
    $(wildcard include/config/mach/amk/a4.h) \
    $(wildcard include/config/mach/gnet/sgme.h) \
    $(wildcard include/config/mach/shooter/u.h) \
    $(wildcard include/config/mach/vmx53.h) \
    $(wildcard include/config/mach/rhino.h) \
    $(wildcard include/config/mach/armlex4210.h) \
    $(wildcard include/config/mach/swarcoextmodem.h) \
    $(wildcard include/config/mach/snowball.h) \
    $(wildcard include/config/mach/pcm049.h) \
    $(wildcard include/config/mach/vigor.h) \
    $(wildcard include/config/mach/oslo/amundsen.h) \
    $(wildcard include/config/mach/gsl/diamond.h) \
    $(wildcard include/config/mach/cv2201.h) \
    $(wildcard include/config/mach/cv2202.h) \
    $(wildcard include/config/mach/cv2203.h) \
    $(wildcard include/config/mach/vit/ibox.h) \
    $(wildcard include/config/mach/dm6441/esp.h) \
    $(wildcard include/config/mach/at91sam9x5ek.h) \
    $(wildcard include/config/mach/libra.h) \
    $(wildcard include/config/mach/easycrrh.h) \
    $(wildcard include/config/mach/tripel.h) \
    $(wildcard include/config/mach/endian/mini.h) \
    $(wildcard include/config/mach/xilinx/ep107.h) \
    $(wildcard include/config/mach/nuri.h) \
    $(wildcard include/config/mach/janus.h) \
    $(wildcard include/config/mach/ddnas.h) \
    $(wildcard include/config/mach/tag.h) \
    $(wildcard include/config/mach/tagw.h) \
    $(wildcard include/config/mach/nitrogen/vm/imx51.h) \
    $(wildcard include/config/mach/viprinet.h) \
    $(wildcard include/config/mach/bockw.h) \
    $(wildcard include/config/mach/eva2000.h) \
    $(wildcard include/config/mach/steelyard.h) \
    $(wildcard include/config/mach/nsslsboard.h) \
    $(wildcard include/config/mach/geneva/b5.h) \
    $(wildcard include/config/mach/spear1340.h) \
    $(wildcard include/config/mach/rexmas.h) \
    $(wildcard include/config/mach/msm8960/cdp.h) \
    $(wildcard include/config/mach/msm8960/fluid.h) \
    $(wildcard include/config/mach/msm8960/apq.h) \
    $(wildcard include/config/mach/helios/v2.h) \
    $(wildcard include/config/mach/mif10p.h) \
    $(wildcard include/config/mach/iam28.h) \
    $(wildcard include/config/mach/picasso.h) \
    $(wildcard include/config/mach/mr301a.h) \
    $(wildcard include/config/mach/notle.h) \
    $(wildcard include/config/mach/eelx2.h) \
    $(wildcard include/config/mach/moon.h) \
    $(wildcard include/config/mach/ruby.h) \
    $(wildcard include/config/mach/goldengate.h) \
    $(wildcard include/config/mach/ctbu/gen2.h) \
    $(wildcard include/config/mach/kmp/am17/01.h) \
    $(wildcard include/config/mach/wtplug.h) \
    $(wildcard include/config/mach/mx27su2.h) \
    $(wildcard include/config/mach/nb31.h) \
    $(wildcard include/config/mach/hjsdu.h) \
    $(wildcard include/config/mach/td3/rev1.h) \
    $(wildcard include/config/mach/eag/ci4000.h) \
    $(wildcard include/config/mach/net5big/nand/v2.h) \
    $(wildcard include/config/mach/cpx2.h) \
    $(wildcard include/config/mach/net2big/nand/v2.h) \
    $(wildcard include/config/mach/ecuv5.h) \
    $(wildcard include/config/mach/hsgx6d.h) \
    $(wildcard include/config/mach/dawad7.h) \
    $(wildcard include/config/mach/sam9repeater.h) \
    $(wildcard include/config/mach/gt/i5700.h) \
    $(wildcard include/config/mach/ctera/plug/c2.h) \
    $(wildcard include/config/mach/marvelct.h) \
    $(wildcard include/config/mach/ag11005.h) \
    $(wildcard include/config/mach/vangogh.h) \
    $(wildcard include/config/mach/matrix505.h) \
    $(wildcard include/config/mach/oce/nigma.h) \
    $(wildcard include/config/mach/t55.h) \
    $(wildcard include/config/mach/bio3k.h) \
    $(wildcard include/config/mach/expressct.h) \
    $(wildcard include/config/mach/cardhu.h) \
    $(wildcard include/config/mach/aruba.h) \
    $(wildcard include/config/mach/bonaire.h) \
    $(wildcard include/config/mach/nuc700evb.h) \
    $(wildcard include/config/mach/nuc710evb.h) \
    $(wildcard include/config/mach/nuc740evb.h) \
    $(wildcard include/config/mach/nuc745evb.h) \
    $(wildcard include/config/mach/transcede.h) \
    $(wildcard include/config/mach/mora.h) \
    $(wildcard include/config/mach/nda/evm.h) \
    $(wildcard include/config/mach/timu.h) \
    $(wildcard include/config/mach/expressh.h) \
    $(wildcard include/config/mach/veridis/a300.h) \
    $(wildcard include/config/mach/dm368/leopard.h) \
    $(wildcard include/config/mach/omap/mcop.h) \
    $(wildcard include/config/mach/tritip.h) \
    $(wildcard include/config/mach/sm1k.h) \
    $(wildcard include/config/mach/monch.h) \
    $(wildcard include/config/mach/curacao.h) \
    $(wildcard include/config/mach/origen.h) \
    $(wildcard include/config/mach/epc10.h) \
    $(wildcard include/config/mach/sgh/i740.h) \
    $(wildcard include/config/mach/tuna.h) \
    $(wildcard include/config/mach/mx51/tulip.h) \
    $(wildcard include/config/mach/mx51/aster7.h) \
    $(wildcard include/config/mach/acro37xbrd.h) \
    $(wildcard include/config/mach/elke.h) \
    $(wildcard include/config/mach/sbc6000x.h) \
    $(wildcard include/config/mach/r1801e.h) \
    $(wildcard include/config/mach/h1600.h) \
    $(wildcard include/config/mach/mini210.h) \
    $(wildcard include/config/mach/mini8168.h) \
    $(wildcard include/config/mach/pc7308.h) \
    $(wildcard include/config/mach/kmm2m01.h) \
    $(wildcard include/config/mach/mx51erebus.h) \
    $(wildcard include/config/mach/wm8650refboard.h) \
    $(wildcard include/config/mach/tuxrail.h) \
    $(wildcard include/config/mach/arthur.h) \
    $(wildcard include/config/mach/doorboy.h) \
    $(wildcard include/config/mach/xarina.h) \
    $(wildcard include/config/mach/roverx7.h) \
    $(wildcard include/config/mach/sdvr.h) \
    $(wildcard include/config/mach/acer/maya.h) \
    $(wildcard include/config/mach/pico.h) \
    $(wildcard include/config/mach/cwmx233.h) \
    $(wildcard include/config/mach/cwam1808.h) \
    $(wildcard include/config/mach/cwdm365.h) \
    $(wildcard include/config/mach/mx51/moray.h) \
    $(wildcard include/config/mach/thales/cbc.h) \
    $(wildcard include/config/mach/bluepoint.h) \
    $(wildcard include/config/mach/dir665.h) \
    $(wildcard include/config/mach/acmerover1.h) \
    $(wildcard include/config/mach/shooter/ct.h) \
    $(wildcard include/config/mach/bliss.h) \
    $(wildcard include/config/mach/blissc.h) \
    $(wildcard include/config/mach/thales/adc.h) \
    $(wildcard include/config/mach/ubisys/p9d/evp.h) \
    $(wildcard include/config/mach/atdgp318.h) \
    $(wildcard include/config/mach/dma210u.h) \
    $(wildcard include/config/mach/em/t3.h) \
    $(wildcard include/config/mach/htx3250.h) \
    $(wildcard include/config/mach/g50.h) \
    $(wildcard include/config/mach/eco5.h) \
    $(wildcard include/config/mach/wintergrasp.h) \
    $(wildcard include/config/mach/puro.h) \
    $(wildcard include/config/mach/shooter/k.h) \
    $(wildcard include/config/mach/nspire.h) \
    $(wildcard include/config/mach/mickxx.h) \
    $(wildcard include/config/mach/lxmb.h) \
    $(wildcard include/config/mach/adam.h) \
    $(wildcard include/config/mach/b1004.h) \
    $(wildcard include/config/mach/oboea.h) \
    $(wildcard include/config/mach/a1015.h) \
    $(wildcard include/config/mach/robin/vbdt30.h) \
    $(wildcard include/config/mach/tegra/enterprise.h) \
    $(wildcard include/config/mach/rfl108200/mk10.h) \
    $(wildcard include/config/mach/rfl108300/mk16.h) \
    $(wildcard include/config/mach/rover/v7.h) \
    $(wildcard include/config/mach/miphone.h) \
    $(wildcard include/config/mach/femtobts.h) \
    $(wildcard include/config/mach/monopoli.h) \
    $(wildcard include/config/mach/boss.h) \
    $(wildcard include/config/mach/davinci/dm368/vtam.h) \
    $(wildcard include/config/mach/clcon.h) \
    $(wildcard include/config/mach/nokia/rm696.h) \
    $(wildcard include/config/mach/tahiti.h) \
    $(wildcard include/config/mach/fighter.h) \
    $(wildcard include/config/mach/sgh/i710.h) \
    $(wildcard include/config/mach/integreproscb.h) \
    $(wildcard include/config/mach/monza.h) \
    $(wildcard include/config/mach/calimain.h) \
    $(wildcard include/config/mach/mx6q/sabreauto.h) \
    $(wildcard include/config/mach/gma01x.h) \
    $(wildcard include/config/mach/sbc51.h) \
    $(wildcard include/config/mach/fit.h) \
    $(wildcard include/config/mach/steelhead.h) \
    $(wildcard include/config/mach/panther.h) \
    $(wildcard include/config/mach/msm8960/liquid.h) \
    $(wildcard include/config/mach/lexikonct.h) \
    $(wildcard include/config/mach/ns2816/stb.h) \
    $(wildcard include/config/mach/sei/mm2/lpc3250.h) \
    $(wildcard include/config/mach/cmimx53.h) \
    $(wildcard include/config/mach/sandwich.h) \
    $(wildcard include/config/mach/chief.h) \
    $(wildcard include/config/mach/pogo/e02.h) \
    $(wildcard include/config/mach/mikrap/x168.h) \
    $(wildcard include/config/mach/htcmozart.h) \
    $(wildcard include/config/mach/htcgold.h) \
    $(wildcard include/config/mach/mt72xx.h) \
    $(wildcard include/config/mach/mx51/ivy.h) \
    $(wildcard include/config/mach/mx51/lvd.h) \
    $(wildcard include/config/mach/omap3/wiser2.h) \
    $(wildcard include/config/mach/dreamplug.h) \
    $(wildcard include/config/mach/cobas/c/111.h) \
    $(wildcard include/config/mach/cobas/u/411.h) \
    $(wildcard include/config/mach/hssd.h) \
    $(wildcard include/config/mach/iom35x.h) \
    $(wildcard include/config/mach/psom/omap.h) \
    $(wildcard include/config/mach/iphone/2g.h) \
    $(wildcard include/config/mach/iphone/3g.h) \
    $(wildcard include/config/mach/ipod/touch/1g.h) \
    $(wildcard include/config/mach/pharos/tpc.h) \
    $(wildcard include/config/mach/mx53/hydra.h) \
    $(wildcard include/config/mach/ns2816/dev/board.h) \
    $(wildcard include/config/mach/iphone/3gs.h) \
    $(wildcard include/config/mach/iphone/4.h) \
    $(wildcard include/config/mach/ipod/touch/4g.h) \
    $(wildcard include/config/mach/dragon/e1100.h) \
    $(wildcard include/config/mach/topside.h) \
    $(wildcard include/config/mach/irisiii.h) \
    $(wildcard include/config/mach/deto/macarm9.h) \
    $(wildcard include/config/mach/eti/d1.h) \
    $(wildcard include/config/mach/som3530sdk.h) \
    $(wildcard include/config/mach/oc/engine.h) \
    $(wildcard include/config/mach/apq8064/sim.h) \
    $(wildcard include/config/mach/alps.h) \
    $(wildcard include/config/mach/tny/t3730.h) \
    $(wildcard include/config/mach/geryon/nfe.h) \
    $(wildcard include/config/mach/ns2816/ref/board.h) \
    $(wildcard include/config/mach/silverstone.h) \
    $(wildcard include/config/mach/mtt2440.h) \
    $(wildcard include/config/mach/ynicdb.h) \
    $(wildcard include/config/mach/bct.h) \
    $(wildcard include/config/mach/tuscan.h) \
    $(wildcard include/config/mach/xbt/sam9g45.h) \
    $(wildcard include/config/mach/enbw/cmc.h) \
    $(wildcard include/config/mach/ch104mx257.h) \
    $(wildcard include/config/mach/openpri.h) \
    $(wildcard include/config/mach/am335xevm.h) \
    $(wildcard include/config/mach/picodmb.h) \
    $(wildcard include/config/mach/waluigi.h) \
    $(wildcard include/config/mach/punicag7.h) \
    $(wildcard include/config/mach/ipad/1g.h) \
    $(wildcard include/config/mach/appletv/2g.h) \
    $(wildcard include/config/mach/mach/ecog45.h) \
    $(wildcard include/config/mach/ait/cam/enc/4xx.h) \
    $(wildcard include/config/mach/runnymede.h) \
    $(wildcard include/config/mach/play.h) \
    $(wildcard include/config/mach/hw90260.h) \
    $(wildcard include/config/mach/tagh.h) \
    $(wildcard include/config/mach/filbert.h) \
    $(wildcard include/config/mach/getinge/netcomv3.h) \
    $(wildcard include/config/mach/cw20.h) \
    $(wildcard include/config/mach/cinema.h) \
    $(wildcard include/config/mach/cinema/tea.h) \
    $(wildcard include/config/mach/cinema/coffee.h) \
    $(wildcard include/config/mach/cinema/juice.h) \
    $(wildcard include/config/mach/mx53/mirage2.h) \
    $(wildcard include/config/mach/mx53/efikasb.h) \
    $(wildcard include/config/mach/stm/b2000.h) \
    $(wildcard include/config/mach/m28evk.h) \
    $(wildcard include/config/mach/pda.h) \
    $(wildcard include/config/mach/meraki/mr58.h) \
    $(wildcard include/config/mach/kota2.h) \
    $(wildcard include/config/mach/letcool.h) \
    $(wildcard include/config/mach/mx27iat.h) \
    $(wildcard include/config/mach/apollo/td.h) \
    $(wildcard include/config/mach/arena.h) \
    $(wildcard include/config/mach/gsngateway.h) \
    $(wildcard include/config/mach/lf2000.h) \
    $(wildcard include/config/mach/bonito.h) \
    $(wildcard include/config/mach/asymptote.h) \
    $(wildcard include/config/mach/bst2brd.h) \
    $(wildcard include/config/mach/tx335s.h) \
    $(wildcard include/config/mach/pelco/tesla.h) \
    $(wildcard include/config/mach/rrhtestplat.h) \
    $(wildcard include/config/mach/vidtonic/pro.h) \
    $(wildcard include/config/mach/pl/apollo.h) \
    $(wildcard include/config/mach/pl/phoenix.h) \
    $(wildcard include/config/mach/m28cu3.h) \
    $(wildcard include/config/mach/vvbox/hd.h) \
    $(wildcard include/config/mach/coreware/sam9260/.h) \
    $(wildcard include/config/mach/marmaduke.h) \
    $(wildcard include/config/mach/amg/xlcore/camera.h) \
    $(wildcard include/config/mach/omap3/egf.h) \
    $(wildcard include/config/mach/smdk4212.h) \
    $(wildcard include/config/mach/dnp9200.h) \
    $(wildcard include/config/mach/tf101.h) \
    $(wildcard include/config/mach/omap3silvio.h) \
    $(wildcard include/config/mach/picasso2.h) \
    $(wildcard include/config/mach/vangogh2.h) \
    $(wildcard include/config/mach/olpc/xo/1/75.h) \
    $(wildcard include/config/mach/gx400.h) \
    $(wildcard include/config/mach/gs300.h) \
    $(wildcard include/config/mach/acer/a9.h) \
    $(wildcard include/config/mach/vivow/evm.h) \
    $(wildcard include/config/mach/veloce/cxq.h) \
    $(wildcard include/config/mach/veloce/cxm.h) \
    $(wildcard include/config/mach/p1852.h) \
    $(wildcard include/config/mach/naxy100.h) \
    $(wildcard include/config/mach/taishan.h) \
    $(wildcard include/config/mach/touchlink.h) \
    $(wildcard include/config/mach/stm32f103ze.h) \
    $(wildcard include/config/mach/mcx.h) \
    $(wildcard include/config/mach/stm/nmhdk/fli7610.h) \
    $(wildcard include/config/mach/top28x.h) \
    $(wildcard include/config/mach/okl4vp/microvisor.h) \
    $(wildcard include/config/mach/pop.h) \
    $(wildcard include/config/mach/layer.h) \
    $(wildcard include/config/mach/trondheim.h) \
    $(wildcard include/config/mach/eva.h) \
    $(wildcard include/config/mach/trust/taurus.h) \
    $(wildcard include/config/mach/ns2816/huashan.h) \
    $(wildcard include/config/mach/ns2816/yangcheng.h) \
    $(wildcard include/config/mach/p852.h) \
    $(wildcard include/config/mach/flea3.h) \
    $(wildcard include/config/mach/bowfin.h) \
    $(wildcard include/config/mach/mv88de3100.h) \
    $(wildcard include/config/mach/pia/am35x.h) \
    $(wildcard include/config/mach/cedar.h) \
    $(wildcard include/config/mach/picasso/e.h) \
    $(wildcard include/config/mach/samsung/e60.h) \
    $(wildcard include/config/mach/sdvr/mini.h) \
    $(wildcard include/config/mach/omap3/ij3k.h) \
    $(wildcard include/config/mach/modasmc1.h) \
    $(wildcard include/config/mach/apq8064/rumi3.h) \
    $(wildcard include/config/mach/matrix506.h) \
    $(wildcard include/config/mach/msm9615/mtp.h) \
    $(wildcard include/config/mach/dm36x/spawndc.h) \
    $(wildcard include/config/mach/sff792.h) \
    $(wildcard include/config/mach/am335xiaevm.h) \
    $(wildcard include/config/mach/g3c2440.h) \
    $(wildcard include/config/mach/tion270.h) \
    $(wildcard include/config/mach/w22q7arm02.h) \
    $(wildcard include/config/mach/omap/cat.h) \
    $(wildcard include/config/mach/at91sam9n12ek.h) \
    $(wildcard include/config/mach/morrison.h) \
    $(wildcard include/config/mach/svdu.h) \
    $(wildcard include/config/mach/lpp01.h) \
    $(wildcard include/config/mach/ubc283.h) \
    $(wildcard include/config/mach/zeppelin.h) \
    $(wildcard include/config/mach/motus.h) \
    $(wildcard include/config/mach/neomainboard.h) \
    $(wildcard include/config/mach/devkit3250.h) \
    $(wildcard include/config/mach/devkit7000.h) \
    $(wildcard include/config/mach/fmc/uic.h) \
    $(wildcard include/config/mach/fmc/dcm.h) \
    $(wildcard include/config/mach/batwm.h) \
    $(wildcard include/config/mach/atlas6cb.h) \
    $(wildcard include/config/mach/blue.h) \
    $(wildcard include/config/mach/colorado.h) \
    $(wildcard include/config/mach/popc.h) \
    $(wildcard include/config/mach/promwad/jade.h) \
    $(wildcard include/config/mach/amp.h) \
    $(wildcard include/config/mach/gnet/amp.h) \
    $(wildcard include/config/mach/toques.h) \
    $(wildcard include/config/mach/dct/storm.h) \
    $(wildcard include/config/mach/owl.h) \
    $(wildcard include/config/mach/cogent/csb1741.h) \
    $(wildcard include/config/mach/adillustra610.h) \
    $(wildcard include/config/mach/ecafe/na04.h) \
    $(wildcard include/config/mach/popct.h) \
    $(wildcard include/config/mach/omap3/helena.h) \
    $(wildcard include/config/mach/ach.h) \
    $(wildcard include/config/mach/module/dtb.h) \
    $(wildcard include/config/mach/oslo/elisabeth.h) \
    $(wildcard include/config/mach/tt01.h) \
    $(wildcard include/config/mach/msm8930/cdp.h) \
    $(wildcard include/config/mach/msm8930/mtp.h) \
    $(wildcard include/config/mach/msm8930/fluid.h) \
    $(wildcard include/config/mach/ltu11.h) \
    $(wildcard include/config/mach/am1808/spawnco.h) \
    $(wildcard include/config/mach/flx6410.h) \
    $(wildcard include/config/mach/mx6q/qsb.h) \
    $(wildcard include/config/mach/mx53/plt424.h) \
    $(wildcard include/config/mach/jasmine.h) \
    $(wildcard include/config/mach/l138/owlboard/plus.h) \
    $(wildcard include/config/mach/wr21.h) \
    $(wildcard include/config/mach/peaboy.h) \
    $(wildcard include/config/mach/mx28/plato.h) \
    $(wildcard include/config/mach/kacom2.h) \
    $(wildcard include/config/mach/slco.h) \
    $(wildcard include/config/mach/imx51pico.h) \
    $(wildcard include/config/mach/glink1.h) \
    $(wildcard include/config/mach/diamond.h) \
    $(wildcard include/config/mach/d9000.h) \
    $(wildcard include/config/mach/w5300e01.h) \
    $(wildcard include/config/mach/im6000.h) \
    $(wildcard include/config/mach/mx51/fred51.h) \
    $(wildcard include/config/mach/stm32f2.h) \
    $(wildcard include/config/mach/ville.h) \
    $(wildcard include/config/mach/ptip/murnau.h) \
    $(wildcard include/config/mach/ptip/classic.h) \
    $(wildcard include/config/mach/mx53grb.h) \
    $(wildcard include/config/mach/gagarin.h) \
    $(wildcard include/config/mach/nas2big.h) \
    $(wildcard include/config/mach/superfemto.h) \
    $(wildcard include/config/mach/teufel.h) \
    $(wildcard include/config/mach/dinara.h) \
    $(wildcard include/config/mach/vanquish.h) \
    $(wildcard include/config/mach/zipabox1.h) \
    $(wildcard include/config/mach/u9540.h) \
    $(wildcard include/config/mach/jet.h) \
    $(wildcard include/config/mach/smdk4412.h) \
    $(wildcard include/config/mach/elite.h) \
    $(wildcard include/config/mach/spear320/hmi.h) \
    $(wildcard include/config/mach/ontario.h) \
    $(wildcard include/config/mach/mx6q/sabrelite.h) \
    $(wildcard include/config/mach/vc200.h) \
    $(wildcard include/config/mach/msm7625a/ffa.h) \
    $(wildcard include/config/mach/msm7625a/surf.h) \
    $(wildcard include/config/mach/benthossbp.h) \
    $(wildcard include/config/mach/smdk5210.h) \
    $(wildcard include/config/mach/empq2300.h) \
    $(wildcard include/config/mach/minipos.h) \
    $(wildcard include/config/mach/omap5/sevm.h) \
    $(wildcard include/config/mach/shelter.h) \
    $(wildcard include/config/mach/omap3/devkit8500.h) \
    $(wildcard include/config/mach/edgetd.h) \
    $(wildcard include/config/mach/copperyard.h) \
    $(wildcard include/config/mach/edge.h) \
    $(wildcard include/config/mach/edge/u.h) \
    $(wildcard include/config/mach/edge/td.h) \
    $(wildcard include/config/mach/wdss.h) \
    $(wildcard include/config/mach/dl/pb25.h) \
    $(wildcard include/config/mach/dss11.h) \
    $(wildcard include/config/mach/cpa.h) \
    $(wildcard include/config/mach/aptp2000.h) \
    $(wildcard include/config/mach/marzen.h) \
    $(wildcard include/config/mach/st/turbine.h) \
    $(wildcard include/config/mach/gtl/it3300.h) \
    $(wildcard include/config/mach/mx6/mule.h) \
    $(wildcard include/config/mach/v7pxa/dt.h) \
    $(wildcard include/config/mach/v7mmp/dt.h) \
    $(wildcard include/config/mach/dragon7.h) \
    $(wildcard include/config/mach/krome.h) \
    $(wildcard include/config/mach/oratisdante.h) \
    $(wildcard include/config/mach/fathom.h) \
    $(wildcard include/config/mach/dns325.h) \
    $(wildcard include/config/mach/sarnen.h) \
    $(wildcard include/config/mach/ubisys/g1.h) \
    $(wildcard include/config/mach/mx53/pf1.h) \
    $(wildcard include/config/mach/asanti.h) \
    $(wildcard include/config/mach/volta.h) \
    $(wildcard include/config/mach/knight.h) \
    $(wildcard include/config/mach/beaglebone.h) \
    $(wildcard include/config/mach/becker.h) \
    $(wildcard include/config/mach/fc360.h) \
    $(wildcard include/config/mach/pmi2/xls.h) \
    $(wildcard include/config/mach/taranto.h) \
    $(wildcard include/config/mach/plutux.h) \
    $(wildcard include/config/mach/ipmp/medcom.h) \
    $(wildcard include/config/mach/absolut.h) \
    $(wildcard include/config/mach/awpb3.h) \
    $(wildcard include/config/mach/nfp32xx/dt.h) \
    $(wildcard include/config/mach/dl/pb53.h) \
    $(wildcard include/config/mach/acu/ii.h) \
    $(wildcard include/config/mach/avalon.h) \
    $(wildcard include/config/mach/sphinx.h) \
    $(wildcard include/config/mach/titan/t.h) \
    $(wildcard include/config/mach/harvest/boris.h) \
    $(wildcard include/config/mach/mach/msm7x30/m3s.h) \
    $(wildcard include/config/mach/smdk5250.h) \
    $(wildcard include/config/mach/imxt/lite.h) \
    $(wildcard include/config/mach/imxt/std.h) \
    $(wildcard include/config/mach/imxt/log.h) \
    $(wildcard include/config/mach/imxt/nav.h) \
    $(wildcard include/config/mach/imxt/full.h) \
    $(wildcard include/config/mach/ag09015.h) \
    $(wildcard include/config/mach/am3517/mt/ventoux.h) \
    $(wildcard include/config/mach/dp1arm9.h) \
    $(wildcard include/config/mach/picasso/m.h) \
    $(wildcard include/config/mach/video/gadget.h) \
    $(wildcard include/config/mach/mtt/om3x.h) \
    $(wildcard include/config/mach/mx6q/arm2.h) \
    $(wildcard include/config/mach/picosam9g45.h) \
    $(wildcard include/config/mach/vpm/dm365.h) \
    $(wildcard include/config/mach/bonfire.h) \
    $(wildcard include/config/mach/mt2p2d.h) \
    $(wildcard include/config/mach/sigpda01.h) \
    $(wildcard include/config/mach/cn27.h) \
    $(wildcard include/config/mach/mx25/cwtap.h) \
    $(wildcard include/config/mach/apf28.h) \
    $(wildcard include/config/mach/pelco/maxwell.h) \
    $(wildcard include/config/mach/ge/phoenix.h) \
    $(wildcard include/config/mach/empc/a500.h) \
    $(wildcard include/config/mach/ims/arm9.h) \
    $(wildcard include/config/mach/mini2416.h) \
    $(wildcard include/config/mach/mini2450.h) \
    $(wildcard include/config/mach/mini310.h) \
    $(wildcard include/config/mach/spear/hurricane.h) \
    $(wildcard include/config/mach/mt7208.h) \
    $(wildcard include/config/mach/lpc178x.h) \
    $(wildcard include/config/mach/farleys.h) \
    $(wildcard include/config/mach/efm32gg/dk3750.h) \
    $(wildcard include/config/mach/zeus/board.h) \
    $(wildcard include/config/mach/cc51.h) \
    $(wildcard include/config/mach/fxi/c210.h) \
    $(wildcard include/config/mach/msm8627/cdp.h) \
    $(wildcard include/config/mach/msm8627/mtp.h) \
    $(wildcard include/config/mach/armadillo800eva.h) \
    $(wildcard include/config/mach/primou.h) \
    $(wildcard include/config/mach/primoc.h) \
    $(wildcard include/config/mach/primoct.h) \
    $(wildcard include/config/mach/a9500.h) \
    $(wildcard include/config/mach/pluto.h) \
    $(wildcard include/config/mach/acfx100.h) \
    $(wildcard include/config/mach/msm8625/rumi3.h) \
    $(wildcard include/config/mach/valente.h) \
    $(wildcard include/config/mach/crfs/rfeye.h) \
    $(wildcard include/config/mach/rfeye.h) \
    $(wildcard include/config/mach/phidget/sbc3.h) \
    $(wildcard include/config/mach/tcw/mika.h) \
    $(wildcard include/config/mach/imx28/egf.h) \
    $(wildcard include/config/mach/valente/wx.h) \
    $(wildcard include/config/mach/huangshans.h) \
    $(wildcard include/config/mach/bosphorus1.h) \
    $(wildcard include/config/mach/prima.h) \
    $(wildcard include/config/mach/evita/ulk.h) \
    $(wildcard include/config/mach/merisc600.h) \
    $(wildcard include/config/mach/dolak.h) \
    $(wildcard include/config/mach/sbc53.h) \
    $(wildcard include/config/mach/elite/ulk.h) \
    $(wildcard include/config/mach/pov2.h) \
    $(wildcard include/config/mach/ipod/touch/2g.h) \
    $(wildcard include/config/mach/da850/pqab.h) \
    $(wildcard include/config/mach/hi3535.h) \
    $(wildcard include/config/mach/hi3516a.h) \
    $(wildcard include/config/mach/hi3518ev200.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/memblock.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/prom.h \
    $(wildcard include/config/of.h) \
  arch/arm/include/generated/asm/sections.h \
  include/asm-generic/sections.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/setup.h \
    $(wildcard include/config/arm/nr/banks.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/tlb.h \
    $(wildcard include/config/cpu/32v7.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/pgalloc.h \
  include/linux/pagemap.h \
  include/linux/hugetlb_inline.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/tlbflush.h \
    $(wildcard include/config/cpu/tlb/v3.h) \
    $(wildcard include/config/cpu/tlb/v4wt.h) \
    $(wildcard include/config/cpu/tlb/fa.h) \
    $(wildcard include/config/cpu/tlb/v4wbi.h) \
    $(wildcard include/config/cpu/tlb/feroceon.h) \
    $(wildcard include/config/cpu/tlb/v4wb.h) \
    $(wildcard include/config/cpu/tlb/v6.h) \
    $(wildcard include/config/cpu/tlb/v7.h) \
    $(wildcard include/config/arm/errata/720789.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/fixmap.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/mach/arch.h \
    $(wildcard include/config/multi/irq/handler.h) \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/mach/map.h \
  /home/jun/hi3516dv100/3.software_source_code/osdrv/opensource/kernel/linux-3.4.y/arch/arm/include/asm/io.h \
    $(wildcard include/config/need/mach/io/h.h) \
    $(wildcard include/config/pcmcia/soc/common.h) \
    $(wildcard include/config/isa.h) \
    $(wildcard include/config/pccard.h) \
  include/asm-generic/pci_iomap.h \
    $(wildcard include/config/no/generic/pci/ioport/map.h) \
    $(wildcard include/config/generic/pci/iomap.h) \
  arch/arm/mach-hi3516a/include/mach/io.h \
  arch/arm/mm/mm.h \

arch/arm/mm/init.o: $(deps_arch/arm/mm/init.o)

$(deps_arch/arm/mm/init.o):
