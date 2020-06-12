#include <linux/types.h>
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
#include <asm/stat.h>
#include <asm/smp_plat.h>
#include <asm/cpu.h>
#include <mach/io.h>
#include <mach/clock.h>

#include "pm.h"
#include "hi_cpufreq.h"
#include "cpu.h"
#include "media.h"
#include "hi_io.h"
#include "sys_pm.h"

int media_avs_en = PM_MEDIA;
struct PM_DC_DC_ATTR_S g_stDcdcAttr = {0};
int __init pm_device_init(struct pm_device *pm_device)
{
    int ret;
    
    if (unlikely(!pm_device))
        return -EINVAL;

    ret = platform_device_register(&pm_device->device);
    if (ret)
    {
        printk("register cpu pm_device fail. \n");
        goto register_device_fail;
    }
    ret = pm_device->pfnOppTableInit(pm_device, NULL);
    if (ret)
    {
        printk("Init opp fail. \n");
        goto init_opp_fail;
    }
    ret = PM_FreqtableInit(&pm_device->device.dev, &pm_device->freq_table);
    if (ret)
    {
        printk("Init freq table fail. \n");
        goto init_freqtable_fail;
    }

    mutex_init(&pm_device->freq_table_lock);
    /* regiseter regulatot and set init volt */
    ret = pm_device->pfnRegulatorInit(pm_device, NULL);
    if (ret)
    {
        printk("Init regulator fail. \n");
        goto init_regulator_fail;
    }
    /* get clk and set init freq */
    ret = pm_device->pfnClockInit(&pm_device->clk, &pm_device->device.dev);
    if (ret)
    {
        printk("Init clk fail. \n");
        goto init_clk_fail;
    }
    
    mutex_init(&pm_device->dvfs_lock);
    
    /* init hw avs */
    ret = pm_device->pfnAvsInit(pm_device, NULL);
    if (ret)
    {
        printk("Init avs fail. \n");
        goto init_avs_fail;
    }
    return ret;

init_avs_fail:
    pm_device->pfnRegulatorExit(pm_device, NULL);
init_clk_fail:
    pm_device->pfnClockExit(&pm_device->clk, NULL);
init_regulator_fail:
    PM_FreqtableExit(&pm_device->device.dev, &pm_device->freq_table);
init_freqtable_fail:
    pm_device->pfnOppTableExit(pm_device, NULL);
init_opp_fail:
    platform_device_unregister(&pm_device->device);
register_device_fail:
    return ret;
}

/* todo */
void pm_device_exit(struct pm_device *pm_device)
{
    pm_device->pfnAvsExit(pm_device, NULL);

    pm_device->pfnRegulatorExit(pm_device, NULL);

    pm_device->pfnClockExit(&pm_device->clk, NULL);

    PM_FreqtableExit(&pm_device->device.dev, &pm_device->freq_table);

    pm_device->pfnOppTableExit(pm_device, NULL);

    platform_device_unregister(&pm_device->device);
}

int __init pm_DCDCAttr_init(struct PM_DC_DC_ATTR_S *pstDcDcAttr)
{
    int ret = 0;
    
    pstDcDcAttr->Vref = PM_VREF;
    pstDcDcAttr->R1 = PM_R1;
    pstDcDcAttr->R2 = PM_R2;
    pstDcDcAttr->R3 = PM_R3 + PM_R4;
    pstDcDcAttr->R4 = PM_R5;    

    pstDcDcAttr->Vout_base = pstDcDcAttr->Vref * (pstDcDcAttr->R1 + pstDcDcAttr->R2) * (pstDcDcAttr->R3 + pstDcDcAttr->R4);
    pstDcDcAttr->Rconfig = pstDcDcAttr->R1 * pstDcDcAttr->R2;
    pstDcDcAttr->VoltConfig = (pstDcDcAttr->R3 + pstDcDcAttr->R4) * pstDcDcAttr->R2;

    /* pwm's period is 120kHz,so the config N of pwm's period is changeless*/
    pstDcDcAttr->PwmFreqN = 199;
    return ret;
}
static int __init pm_init(void)
{
    int ret;
    unsigned long value;
    U_PROFILE_REG profileReg;
    
    ret = pm_DCDCAttr_init(&g_stDcdcAttr);
    if(ret)
    {
        printk("DcDcAttr init fail. \n");
         return ret;
    }
    
    ret = regulator_init();
    if (ret)
    {
        printk("regulator init fail. \n");
        return ret;
    }

    /* get hw proflie */
    HI_RegRead(&profileReg.u32, PROFILE_REG);
    value = profileReg.bits.hw_profile;
    
#ifdef CPU_PM
    /* 0x0(1 source); 0x1(2 source(media/other)) */
    if((0x0 == value)||(0x1 == value))
    {
        printk("Cpu has no independent Volt-Source.\n");
        regulator_exit();
     return -1;
    }
    
    ret = cpu_pm_init();
    if (ret)
    {
        printk("Cpu pm init fail. \n");
        regulator_exit();
     return ret;
        
    }
#endif

#ifdef MEDIA_PM 
    if(PM_MEDIA == media_avs_en)
    {           
        /* 0x0(1 source); 0x2(2 source(cpu/other)) */
        if((0x0 == value)||(0x2 == value))
        {
            printk("Media0 has no independent Volt-Source.\n");
		#ifdef CPU_PM
    		cpu_pm_exit();
		#endif
    		regulator_exit();
			return -1;
        }
        
        ret = media_pm_init();
        if (ret)
        {
            printk("Media0 pm init fail. \n");
    	#ifdef CPU_PM
    		cpu_pm_exit();
    	#endif
    		regulator_exit();
    		return ret;
        }
    }
    
#endif   
    printk("load pm.ko ok!.\n");
    return ret;
}

static void pm_exit(void)
{
#ifdef MEDIA_PM
    if(PM_MEDIA == media_avs_en)
    {        
        media_pm_exit();
    }
#endif
#ifdef CPU_PM
	cpu_pm_exit();
#endif
    regulator_exit();
    printk("unload pm.ko ok!.\n");
}

module_param(media_avs_en, int, S_IRUGO);

MODULE_DESCRIPTION("pm driver for hi3516A SoCs");
MODULE_LICENSE("GPL");
module_init(pm_init);
module_exit(pm_exit);

