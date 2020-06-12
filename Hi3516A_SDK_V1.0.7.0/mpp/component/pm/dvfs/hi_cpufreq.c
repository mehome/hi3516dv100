
#include <linux/types.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cpufreq.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/opp.h>
#include <linux/cpu.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>

#include <asm/smp_plat.h>
#include <asm/cpu.h>
#include <mach/io.h>
#include <mach/clock.h>

#include "pm.h"
#include "hi_dvfs.h"

#if 0
#ifndef MODULE
struct lpj_info {
	unsigned long	ref;
	unsigned int	freq;
};

static DEFINE_PER_CPU(struct lpj_info, lpj_ref);
#ifdef CONFIG_SMP
static struct lpj_info global_lpj_ref;
#endif
#endif
#endif

extern struct pm_device hi_cpufreq_device;

static int cpufreq_verify_speed(struct cpufreq_policy *policy)
{
	if (!hi_cpufreq_device.freq_table)
		return -EINVAL;
	return cpufreq_frequency_table_verify(policy, hi_cpufreq_device.freq_table);
}

static unsigned int cpufreq_getspeed(unsigned int cpu)
{
	unsigned long rate;

	if (cpu >= NR_CPUS)
		return 0;

	rate = clk_get_rate(&hi_cpufreq_device.clk);
	return rate;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
static int hi_cpufreq_scale(struct device *dev, unsigned int target_freq, 
                            unsigned int cur_freq)
#else
static int hi_cpufreq_scale(struct device *dev, struct cpufreq_policy *policy, 
                         unsigned int target_freq, unsigned int cur_freq)
#endif
{
#ifndef MODULE
    unsigned int i;
#endif

    int ret;
    struct cpufreq_freqs freqs;

    freqs.new = target_freq;
    freqs.old = cpufreq_getspeed(0);

    if ((freqs.old == freqs.new) && (cur_freq == freqs.new))
    {
        return 0;
    }

    get_online_cpus();

    /* notifiers */
    for_each_online_cpu(freqs.cpu)
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
	cpufreq_notify_transition(&freqs, CPUFREQ_PRECHANGE);
#else
	cpufreq_notify_transition(policy, &freqs, CPUFREQ_PRECHANGE);
#endif

    ret = hi_device_scale(dev, freqs.old, freqs.new);

    freqs.new = cpufreq_getspeed(0);


#if 0
#ifndef MODULE
#ifdef CONFIG_SMP
    /*
     * Note that loops_per_jiffy is not updated on SMP systems in
     * cpufreq driver. So, update the per-CPU loops_per_jiffy value
     * on frequency transition. We need to update all dependent CPUs.
     */
    for_each_possible_cpu(i)
    {
        struct lpj_info *lpj = &per_cpu(lpj_ref, i);

        if (!lpj->freq)
        {
            lpj->ref  = per_cpu(cpu_data, i).loops_per_jiffy;
            lpj->freq = freqs.old;
        }

        per_cpu(cpu_data, i).loops_per_jiffy =
            cpufreq_scale(lpj->ref, lpj->freq, freqs.new);
    }
#endif

    /* And don't forget to adjust the global one */
    if (!global_lpj_ref.freq)
    {
        global_lpj_ref.ref  = loops_per_jiffy;
        global_lpj_ref.freq = freqs.old;
    }

    loops_per_jiffy = cpufreq_scale(global_lpj_ref.ref, global_lpj_ref.freq,
                                    freqs.new);

#endif
#endif


    /* notifiers */
    for_each_online_cpu(freqs.cpu)
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
	cpufreq_notify_transition(&freqs, CPUFREQ_POSTCHANGE);
#else
	cpufreq_notify_transition(policy, &freqs, CPUFREQ_POSTCHANGE);
#endif

    put_online_cpus();

    return ret;
}

static int cpufreq_target(struct cpufreq_policy *policy,
                             unsigned int target_freq, unsigned int relation)
{
    struct cpufreq_frequency_table *freq_table;
    unsigned int current_target_freq;
    unsigned int index;
    int ret = 0;
	if(hi_cpufreq_device.dvfs_en == 0)
	{
        return -EAGAIN;
	}
    freq_table = hi_cpufreq_device.freq_table;
    if (!freq_table)
    {
        printk("%s: cpu%d: no freq table!\n", __func__,
                  policy->cpu);
        return -EINVAL;
    }

    ret = cpufreq_frequency_table_target(policy, freq_table, target_freq,
                                         relation, &index);
    if (ret)
    {
        printk("%s: cpu%d: no freq match for %d(ret=%d)\n",
                   __func__, policy->cpu, target_freq, ret);
        return ret;
    }

    mutex_lock(&hi_cpufreq_device.freq_table_lock);

    current_target_freq = freq_table[index].frequency;

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
	ret = hi_cpufreq_scale(&hi_cpufreq_device.device.dev, current_target_freq, 
	                    policy->cur);
#else
    ret = hi_cpufreq_scale(&hi_cpufreq_device.device.dev, policy, 
                        current_target_freq, policy->cur);
#endif

    mutex_unlock(&hi_cpufreq_device.freq_table_lock);

    return ret;
}

static int cpufreq_cpu_init(struct cpufreq_policy *policy)
{
	int result = 0;

    if (policy->cpu >= NR_CPUS) {
		result = -EINVAL;
		goto fail;
	}

	policy->cur = policy->min = policy->max = cpufreq_getspeed(policy->cpu);

	result = cpufreq_frequency_table_cpuinfo(policy, hi_cpufreq_device.freq_table);
	if (result)
		goto fail;

	cpufreq_frequency_table_get_attr(hi_cpufreq_device.freq_table, policy->cpu);

	policy->min = policy->cpuinfo.min_freq;
	policy->max = policy->cpuinfo.max_freq;
	policy->cur = cpufreq_getspeed(policy->cpu);

#if 0
	/*
	 * On hisilicon SMP configuartion, both processors share the voltage
	 * and clock. So both CPUs needs to be scaled together and hence
	 * needs software co-ordination. Use cpufreq affected_cpus
	 * interface to handle this scenario. Additional is_smp() check
	 * is to keep SMP_ON_UP build working.
	 */
#ifndef MODULE
#ifdef CONFIG_SMP
        if (is_smp())
        {   
            policy->shared_type = CPUFREQ_SHARED_TYPE_ANY;
            cpumask_setall(policy->cpus);
        }   
#endif
#endif
#endif

	/* FIXME: what's the actual transition time? */
	policy->cpuinfo.transition_latency = 1000 * 1000;

	return 0;
fail:
	return result;
}

static int cpufreq_cpu_exit(struct cpufreq_policy *policy)
{
	return 0;
}

static struct freq_attr *cpufreq_attr[] = {
	&cpufreq_freq_attr_scaling_available_freqs,
	NULL,
};

static struct cpufreq_driver stCpufreqDriver = {
	.flags		= CPUFREQ_STICKY,
	.verify		= cpufreq_verify_speed,
	.target		= cpufreq_target,
	.get		= cpufreq_getspeed,
	.init		= cpufreq_cpu_init,
	.exit		= cpufreq_cpu_exit,
	.name		= "cpufreq",
	.attr		= cpufreq_attr,
};

int __init cpufreq_init(void)
{   
	cpufreq_enable();
    return cpufreq_register_driver(&stCpufreqDriver);
}

void cpufreq_exit(void)
{
	cpufreq_disable();
    cpufreq_unregister_driver(&stCpufreqDriver);
}
void cpufreq_disable(void)
{
	
    mutex_lock(&hi_cpufreq_device.dvfs_lock);
	hi_cpufreq_device.dvfs_en = 0;
	mutex_unlock(&hi_cpufreq_device.dvfs_lock);
}

void cpufreq_enable(void)
{
	mutex_lock(&hi_cpufreq_device.dvfs_lock);
	hi_cpufreq_device.dvfs_en = 1;
	mutex_unlock(&hi_cpufreq_device.dvfs_lock);
}


