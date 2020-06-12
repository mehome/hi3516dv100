/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : cpu.c
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/25
  Last Modified :
  Description   : cpu.c
  Function List :
              cpu_pm_exit
              cpu_pm_init
  History       :
  1.Date        : 2014/6/25
    Author      : l00165163
    Modification: Created file

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/cpufreq.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/clk.h>
#include <linux/io.h>

#include "pm.h"
#include "cpu.h"
#include "hi_cpufreq.h"
#include "hi_dvfs.h"


static void cf_platform_device_release(struct device* dev){}
struct pm_device hi_cpufreq_device = {
    .device = {
        .name = "hisi_pm_cpu",
        .dev  = {
            .platform_data = NULL,                
            .release       = cf_platform_device_release,
    },},

    .pfnOppTableInit  = cpu_OppTableInit,
    .pfnOppTableExit  = cpu_OppTableExit,
    .pfnClockInit     = cpu_ClockInit,
    .pfnClockExit     = cpu_ClockExit,
    .pfnRegulatorInit = cpu_RegulatorInit,
    .pfnRegulatorExit = cpu_RegulatorExit,
    .pfnAvsInit       = cpu_AvsInit,
    .pfnAvsExit       = cpu_AvsExit,
};

static int cpu_pm_freeze(struct device *dev)
{
	struct pm_device *device;
	struct avs_ops *cpu_avs_ops;
	device = to_pm_device_ex(dev);
	cpu_avs_ops = &device->avs_dev.avs_ops;

	cpufreq_disable();
	cpu_avs_ops->pfnAvsPause(device);
    return 0;
}

static int cpu_pm_restore(struct device *dev)
{
    struct pm_device *device;
	struct clk *clk;
	struct avs_ops *cpu_avs_ops;
	
	device = to_pm_device_ex(dev);
	clk =&device->clk;
	cpu_avs_ops = &device->avs_dev.avs_ops;

	cpu_RegulatorRestore(device);
	cpu_ClockRestore(&device->clk);
	cpu_AvsRestore(device);
	cpu_avs_ops->pfnAvsResume(device);
	cpufreq_enable();
    return 0;    
}

static struct dev_pm_ops cpu_pm_ops = {
	.freeze         = cpu_pm_freeze,
	.restore        = cpu_pm_restore,
};

static int __devinit cpufreq_probe(struct platform_device *device)
{
	return 0;
}

static int __devexit cpufreq_remove(struct platform_device *device)
{
	return 0;
}

static struct platform_driver hi_cpufreq_driver = {
	.driver = {
		.name  = "hisi_pm_cpu",
		.owner = THIS_MODULE,
		.pm = &cpu_pm_ops,
	},
	.probe = cpufreq_probe,
	.remove = __devexit_p(cpufreq_remove),
	
};

int __init cpu_pm_init(void)
{
    int ret;

    ret = pm_device_init(&hi_cpufreq_device);
    if (ret)
    {
        printk("cpu pm device init fail. \n");
        goto fail0;
    }
    
    ret = cpufreq_init();
    if (ret)
    {
        printk("register cpufreq driver fail. \n");
        goto fail1;
    }
	
	return platform_driver_register(&hi_cpufreq_driver);
    
fail1:
    pm_device_exit(&hi_cpufreq_device);
fail0:
    return ret;
}

void cpu_pm_exit(void)
{
    cpufreq_exit();
    pm_device_exit(&hi_cpufreq_device);
	platform_driver_unregister(&hi_cpufreq_driver);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
