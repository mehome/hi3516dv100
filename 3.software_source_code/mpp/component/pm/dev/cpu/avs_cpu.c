/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : avs_cpu.c
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/28
  Last Modified :
  Description   : avs_cpu.c
  Function List :
              cpu_AvsExit
              cpu_AvsInit
              cpu_AvsPause
              cpu_AvsResume
              cpu_AvsThread
  History       :
  1.Date        : 2014/6/28
    Author      : l00165163
    Modification: Created file

******************************************************************************/
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include "hi_io.h"

#include "avs_pm.h"
#include "pm.h"
#include "cpu.h"
#include "pmc.h"
#include "sys_pm.h"


#ifdef CPU_AVS

#define AVS_STEP 10 /*mv*/
#define AVS_INTERVAL 20 /*ms*/
int cpu_avs_inter = 20;
int cpu_avs_en = 1;
module_param(cpu_avs_inter, int, S_IRUGO);
module_param(cpu_avs_en, int, S_IRUGO);
//module_param(cpu_avs, int, S_IRUGO);
/* hpm table define */
static HPM_VF_S cpu_freq_hpm_table[] = 
{
    { HI_VDD_CPU_OPP1_FREQ, HI_VDD_CPU_OPP1_AVS_VMIN_MV, HI_VDD_CPU_OPP1_AVS_HPM, HI_VDD_CPU_OPP1_AVS_HPM_DIV},
    { HI_VDD_CPU_OPP2_FREQ, HI_VDD_CPU_OPP2_AVS_VMIN_MV, HI_VDD_CPU_OPP2_AVS_HPM, HI_VDD_CPU_OPP2_AVS_HPM_DIV},
    { HI_VDD_CPU_OPP3_FREQ, HI_VDD_CPU_OPP3_AVS_VMIN_MV, HI_VDD_CPU_OPP3_AVS_HPM, HI_VDD_CPU_OPP3_AVS_HPM_DIV},
    { HI_VDD_CPU_OPP4_FREQ, HI_VDD_CPU_OPP4_AVS_VMIN_MV, HI_VDD_CPU_OPP4_AVS_HPM, HI_VDD_CPU_OPP4_AVS_HPM_DIV},
    { HI_VDD_CPU_OPP5_FREQ, HI_VDD_CPU_OPP5_AVS_VMIN_MV, HI_VDD_CPU_OPP5_AVS_HPM, HI_VDD_CPU_OPP5_AVS_HPM_DIV},
    //{ HI_VDD_CPU_OPP6_FREQ, HI_VDD_CPU_OPP6_AVS_VMIN_MV, HI_VDD_CPU_OPP6_AVS_HPM, HI_VDD_CPU_OPP6_AVS_HPM_DIV},
    //{ HI_VDD_CPU_OPP7_FREQ, HI_VDD_CPU_OPP7_AVS_VMIN_MV, HI_VDD_CPU_OPP7_AVS_HPM, HI_VDD_CPU_OPP7_AVS_HPM_DIV},
};

int cpu_AvsThread(void *Arg)
{
    struct pm_device *pm_device = (struct pm_device *)Arg;
    struct avs_dev *avs_dev = &(pm_device->avs_dev);
    unsigned long u32HpmCode, u32HpmCodeAverage = 0;
    unsigned long u32RegVal;
    int s32HpmDelta;
    int ret;
    
    while (!kthread_should_stop())
    {
        msleep(cpu_avs_inter);

        if (false == avs_dev->avs_enable)
        {
            continue;
        }

        mutex_lock(&avs_dev->avs_lock);

#ifdef CPU_AVS_HPM

#ifndef CPU_AVS_HW
        /* read current code */
        u32HpmCodeAverage = 0;

        HI_RegRead(&u32RegVal, PERI_PMC15);

        u32HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);
        u32HpmCodeAverage += u32HpmCode;

        u32HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
        u32HpmCodeAverage += u32HpmCode;

        HI_RegRead(&u32RegVal, PERI_PMC16);
        u32HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);

        u32HpmCodeAverage += u32HpmCode;
        u32HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
        u32HpmCodeAverage += u32HpmCode;

        u32HpmCodeAverage = u32HpmCodeAverage / 4;
		//printk("**************u32HpmCodeAverage=%d\n",u32HpmCodeAverage);
        s32HpmDelta = u32HpmCodeAverage - avs_dev->cur_hpm; 
        
        /* compare code value */
        if (s32HpmDelta < 0x1)
        {            
            /* up 10mv */

            if (pm_device->cur_volt +  AVS_STEP <= avs_dev->cur_volt_max)
            {
                ret = regulator_set_voltage(pm_device->reg, pm_device->cur_volt + AVS_STEP,
                    pm_device->cur_volt + AVS_STEP);  
                if (ret)
                {
                    printk("%s: scale volt to %u falt\n",
                              __func__, pm_device->cur_volt + AVS_STEP);
                }
                pm_device->cur_volt = regulator_get_voltage(pm_device->reg);
			#ifdef PM_DEBUG
                printk("%s :%d cpu cur_volt is %d\n",__FUNCTION__,__LINE__,pm_device->cur_volt);
			#endif
            }
        }
        else if (s32HpmDelta >= 0xa)
        {            
            /*down 10mv */            
            if (pm_device->cur_volt - AVS_STEP >= avs_dev->cur_volt_min)
            {
                ret = regulator_set_voltage(pm_device->reg, pm_device->cur_volt - AVS_STEP,
                    pm_device->cur_volt - AVS_STEP);
                if (ret)
                {
                    printk("%s: scale volt to %u falt\n",
                              __func__, pm_device->cur_volt - AVS_STEP);
                    return ret;
                }
                pm_device->cur_volt = regulator_get_voltage(pm_device->reg);
			#ifdef PM_DEBUG
                printk("%s :%d cpu cur_volt is %d\n",__FUNCTION__,__LINE__,pm_device->cur_volt);
			#endif
            }
            
        }
        else           
        {
            msleep(cpu_avs_inter);
        }
#endif

#else

    /* read pmc37~40 record */

    


#ifndef CPU_AVS_HW
#endif

#endif
        mutex_unlock(&avs_dev->avs_lock);
    }

    return 0;
}

void cpu_AvsPause(struct pm_device *pm_device)
{
    struct avs_dev *avs_dev = &pm_device->avs_dev;
    
    avs_dev->avs_enable = false;

    mutex_lock(&avs_dev->avs_lock);

#ifdef CPU_AVS_HPM

#ifdef CPU_AVS_HW
    iSetPERI_PMC6cpu_hpm_fsm_en(0);
    /*todo  to get State machine */
    msleep(10);   
#endif

#else

#ifdef CPU_AVS_HW
    iSetPERI_PMC65cpu_ts_monitor_en(0);
    /*todo  to get State machine */
    msleep(10);
#endif

#endif
}

/* after change the rate, reinitialize the hpm */
static int cpu_update_hpm(struct avs_dev *avs_dev)
{
    int i;
    
    /* get default hpm record */
    for (i = 0; i < avs_dev->max_hpm_tale_index; i++)
    {
        if (avs_dev->cur_freq == avs_dev->freq_hpm_table[i].freq)
        {
            avs_dev->cur_hpm      = avs_dev->freq_hpm_table[i].hpmrecord;
            avs_dev->cur_volt_min = avs_dev->freq_hpm_table[i].vmin;            
            avs_dev->div          = avs_dev->freq_hpm_table[i].div;            
            /* cpu HPM freq */
            iSetPERI_PMC14cpu_hpm_div(avs_dev->div);
            break;
        }
    }

    return 0;
}


void cpu_AvsResume(struct pm_device *pm_device)
{    
    struct avs_dev *avs_dev = &pm_device->avs_dev;
    avs_dev->cur_freq   = pm_device->cur_rate;
    avs_dev->avs_enable = true;

#ifdef CPU_AVS_HPM
    cpu_update_hpm(avs_dev);
#ifdef CPU_AVS_HW

#ifdef CPU_PWM
    iSetPERI_PMC17cpu_hpm_lowlimit(4095/*avs_dev->hpm_downlimit*/);
    iSetPERI_PMC17cpu_hpm_uplimit(0/*avs_dev->hpm_uplimit*/);
#endif
    iSetPERI_PMC6cpu_hpm_fsm_en(1);
#endif
    
#else /* CPU_AVS_HPM */

#ifdef CPU_AVS_HW
    iSetPERI_PMC65cpu_ts_monitor_en(1);
#endif
    
#endif /* CPU_AVS_HPM */

    mutex_unlock(&avs_dev->avs_lock);

    return;
}

static struct avs_ops cpu_avs_ops = 
{
    .pfnAvsPause = cpu_AvsPause,
    .pfnAvsResume = cpu_AvsResume,
};


HI_VOID cpu_HpmInit(struct avs_dev *avs_dev)
{
    /* set cpu avs control source */
    iSetPERI_PMC65cpu_avs_ctrl_sel(0x1);
    /* cpu HPM reset */
    iSetPERI_PMC14cpu_hpm_srst_req(0x1);    
    iSetPERI_PMC14cpu_hpm_srst_req(0x0);
    /* cpu HPM limit*/
    iSetPERI_PMC17cpu_hpm_uplimit(avs_dev->hpm_uplimit);    
    iSetPERI_PMC17cpu_hpm_lowlimit(avs_dev->hpm_downlimit);
    iSetPERI_PMC17cpu_hpm_monitor_period(avs_dev->high_period);
    iSetPERI_PMC30cpu_hpm_monitor_period(avs_dev->low_period);
    
    iSetPERI_PMC14cpu_hpm_shift(avs_dev->shift);
    iSetPERI_PMC14cpu_hpm_offset(avs_dev->offset);
    
    iSetPERI_PMC14cpu_hpm_monitor_en(0x1);
    iSetPERI_PMC14cpu_hpm_en(0x1);
#ifdef CPU_AVS_HW
    
#ifdef CPU_PWM
    iSetPERI_PMC6cpu_avs_fsm_dec_pwm_step(avs_dev->hpm_pwm_dec_step);
    iSetPERI_PMC6cpu_avs_fsm_inc_pwm_step(avs_dev->hpm_pwm_inc_step);
#endif
    iSetPERI_PMC6cpu_avs_hpm_fsm_calc_mode(avs_dev->hpm_fsm_mode);    
    iSetPERI_PMC6cpu_hpm_fsm_en(0x1);
#endif 

}

HI_VOID cpu_TsInit(struct avs_dev *avs_dev)
{
    /* ts mode */
    iSetPERI_PMC65cpu_avs_ctrl_sel(0x0);

    /* ts ctrl */
    iSetPERI_PMC32cpu_ts_sel(avs_dev->ts_crazy_mode);
    iSetPERI_PMC32cpu_ts_dly_adjust(avs_dev->ts_crazy_path_dly);
    iSetPERI_PMC32cpu_ts_step(avs_dev->ts_code_step);
    iSetPERI_PMC32cpu_ts_en(0x1);
     
#ifdef CPU_AVS_HW
    /* ts avs */
    iSetPERI_PMC65cpu_ts_en_must_inc(avs_dev->ts_avs_mode);

    iSetPERI_PMC65cpu_ts_monitor_period(avs_dev->ts_avs_period);
    iSetPERI_PMC65cpu_ts_monitor_en(0x1);    
#endif

}

int cpu_AvsInit(struct pm_device *pm_device, void *pdata)
{
    struct avs_dev *avs_dev = &pm_device->avs_dev;

    avs_dev->freq_hpm_table = kmalloc(sizeof(cpu_freq_hpm_table), GFP_KERNEL);
    if (!avs_dev->freq_hpm_table)
    {
        printk("malloc hpm table err.\n");
        return -1;
    }    
    memcpy(avs_dev->freq_hpm_table, cpu_freq_hpm_table, sizeof(cpu_freq_hpm_table));
    avs_dev->max_hpm_tale_index = ARRAY_SIZE(cpu_freq_hpm_table);
    avs_dev->cur_freq = pm_device->cur_rate;
    avs_dev->avs_ops      = cpu_avs_ops;    
    avs_dev->cur_volt_max = CPU_VMAX; 
    cpu_update_hpm(avs_dev);
    avs_dev->avs_enable = true;
#ifdef CPU_AVS_HPM 
    /* avs hpm */
    avs_dev->hpm_uplimit   = 276;
    avs_dev->hpm_downlimit = 190;
    avs_dev->high_period   = 0x1;
    avs_dev->low_period    = 0;
    avs_dev->shift         = 0;
    avs_dev->offset        = 0; 

    avs_dev->hpm_pwm_dec_step   = 0;
    avs_dev->hpm_pwm_inc_step   = 0;
    avs_dev->hpm_fsm_mode       = 0;
    
    cpu_HpmInit(avs_dev);
#else
    /* avs Ts */
    avs_dev->ts_crazy_mode      = 0;
    avs_dev->ts_crazy_path_dly  = 0;
    avs_dev->ts_code_step       = 0;
    
    avs_dev->ts_avs_mode        = 0;
    avs_dev->ts_avs_period      = 0;
    cpu_TsInit(avs_dev);
#endif
#if 1
    mutex_init(&avs_dev->avs_lock);

    avs_dev->pstAvsThread = kthread_create(cpu_AvsThread, (void*)pm_device,
                                           pm_device->device.name);
    if (IS_ERR(avs_dev->pstAvsThread))
    {
        printk("create avs thread failed.\n");
        return -1;
    }
    if(1 == cpu_avs_en)
    {
       printk("cpu avs  enable.\n");
       wake_up_process(avs_dev->pstAvsThread);
       return 0;
    }
#endif
    return 0;
}

void cpu_AvsExit(struct pm_device *pm_device, void *pdata)
{
    if(cpu_avs_en == 1)
    {
        if (pm_device->avs_dev.pstAvsThread)
        {
            kthread_stop(pm_device->avs_dev.pstAvsThread);
            pm_device->avs_dev.pstAvsThread = NULL;
        }
    }
    
    if (pm_device->avs_dev.freq_hpm_table)
    {
        kfree(pm_device->avs_dev.freq_hpm_table);
        pm_device->avs_dev.freq_hpm_table = NULL;
    }
    
    return;
}

int cpu_AvsRestore(struct pm_device *pm_device)
{
	struct avs_dev *avs_dev = &pm_device->avs_dev;
	
    avs_dev->cur_freq = pm_device->cur_rate;
    avs_dev->avs_ops      = cpu_avs_ops;    
    avs_dev->cur_volt_max = CPU_VMAX; 
    cpu_update_hpm(avs_dev);
    avs_dev->avs_enable = true;
#ifdef CPU_AVS_HPM 
    /* avs hpm */
    avs_dev->hpm_uplimit   = 276;
    avs_dev->hpm_downlimit = 190;
    avs_dev->high_period   = 0x1;
    avs_dev->low_period    = 0;
    avs_dev->shift         = 0;
    avs_dev->offset        = 0; 

    avs_dev->hpm_pwm_dec_step   = 0;
    avs_dev->hpm_pwm_inc_step   = 0;
    avs_dev->hpm_fsm_mode       = 0;
    
    cpu_HpmInit(avs_dev);
#else
    /* avs Ts */
    avs_dev->ts_crazy_mode      = 0;
    avs_dev->ts_crazy_path_dly  = 0;
    avs_dev->ts_code_step       = 0;
    
    avs_dev->ts_avs_mode        = 0;
    avs_dev->ts_avs_period      = 0;
    cpu_TsInit(avs_dev);
#endif
	return 0;
}

#else /* CPU AVS*/

void cpu_AvsPause(struct pm_device *pm_device){}

void cpu_AvsResume(struct pm_device *pm_device){}

static struct avs_ops cpu_avs_ops = 
{
    .pfnAvsPause = cpu_AvsPause,
    .pfnAvsResume = cpu_AvsResume,
};

int  cpu_AvsInit(struct pm_device *pm_device, void *pdata)
{
    pm_device->avs_dev.avs_ops = cpu_avs_ops;
    return 0;
}
void cpu_AvsExit(struct pm_device *pm_device, void *pdata){}

#endif /* CPU AVS*/
