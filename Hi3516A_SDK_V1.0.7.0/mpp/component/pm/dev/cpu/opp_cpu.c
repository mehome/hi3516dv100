#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>

#include "pm.h"
#include "hi_opp_data.h"
#include "cpu.h"

/*
 * gloabl static variables
 */

/* cpu :Table of dvfs */
static struct hi_opp_def cpu_opp_table[] = {
    OPP_INITIALIZER(true, HI_VDD_CPU_OPP1_FREQ, HI_VDD_CPU_OPP1_MV),
    OPP_INITIALIZER(true, HI_VDD_CPU_OPP2_FREQ, HI_VDD_CPU_OPP2_MV),
    OPP_INITIALIZER(true, HI_VDD_CPU_OPP3_FREQ, HI_VDD_CPU_OPP3_MV),
    OPP_INITIALIZER(true, HI_VDD_CPU_OPP4_FREQ, HI_VDD_CPU_OPP4_MV),
    OPP_INITIALIZER(true, HI_VDD_CPU_OPP5_FREQ, HI_VDD_CPU_OPP5_MV),
    //OPP_INITIALIZER(true, HI_VDD_CPU_OPP6_FREQ, HI_VDD_CPU_OPP6_MV),
    //OPP_INITIALIZER(true, HI_VDD_CPU_OPP7_FREQ, HI_VDD_CPU_OPP7_MV),
};

/*
 * functions
 */
int cpu_OppTableInit(struct pm_device *pm_device, void *pData)
{
    int oppsize = sizeof(cpu_opp_table);
    int ret;
    
    pm_device->opp_table = kmalloc(oppsize, GFP_KERNEL);
    if (!pm_device->opp_table)
    {
        ret = -ENOMEM;
        printk("malloc opptable(%d) err. \n", oppsize);
        goto err0;
    }
    memcpy((void*)pm_device->opp_table, (void*)cpu_opp_table, sizeof(cpu_opp_table));
    ret = PM_OppInitTable(&pm_device->device.dev, cpu_opp_table, 
                          ARRAY_SIZE(cpu_opp_table));
    if (ret)
    {
        printk("opptable init err. \n");
        goto err1;
    }

    pm_device->min_rate = MIN_CPU_FREQ;
    pm_device->max_rate = MAX_CPU_FREQ;
    
    return 0;
    
err1:
    if (pm_device->opp_table)
    {
        kfree(pm_device->opp_table);
        pm_device->opp_table = NULL;
    }
err0:
    return ret;
}

void cpu_OppTableExit(struct pm_device *pm_device, void *pData)
{
    if (pm_device->opp_table)
    {
        kfree(pm_device->opp_table);
        pm_device->opp_table = NULL;
    }

    return;
}
