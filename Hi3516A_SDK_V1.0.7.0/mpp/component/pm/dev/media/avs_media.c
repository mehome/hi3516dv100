/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : avs_media.c
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/28
  Last Modified :
  Description   : avs_media.c
  Function List :
              media_AvsExit
              media_AvsInit
              media_AvsPause
              media_AvsResume
              media_AvsThread
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
#include <mach/clock.h>
#include <linux/module.h>
#include "hi_io.h"

#include "opp.h"
#include "avs_pm.h"
#include "pm.h"
#include "media.h"
#include "pmc.h"
#include "sys_pm.h"


#ifdef MEDIA_AVS

#define AVS_STEP 10 /*mv*/
#define AVS_INTERVAL 20 /*ms*/
int media_avs_inter = 20;
module_param(media_avs_inter, int, S_IRUGO);
/* hpm table define */
static HPM_VF_S media_freq_hpm_table[] = 
{
    { HI_VDD_MEDIA_OPP1_PROFILE, HI_VDD_MEDIA_OPP1_AVS_VMIN_MV, HI_VDD_MEDIA_OPP1_AVS_HPM, HI_VDD_MEDIA_OPP1_AVS_HPM_DIV},
    { HI_VDD_MEDIA_OPP2_PROFILE, HI_VDD_MEDIA_OPP2_AVS_VMIN_MV, HI_VDD_MEDIA_OPP2_AVS_HPM, HI_VDD_MEDIA_OPP2_AVS_HPM_DIV},
    { HI_VDD_MEDIA_OPP3_PROFILE, HI_VDD_MEDIA_OPP3_AVS_VMIN_MV, HI_VDD_MEDIA_OPP3_AVS_HPM, HI_VDD_MEDIA_OPP3_AVS_HPM_DIV},
    { HI_VDD_MEDIA_OPP4_PROFILE, HI_VDD_MEDIA_OPP4_AVS_VMIN_MV, HI_VDD_MEDIA_OPP4_AVS_HPM, HI_VDD_MEDIA_OPP4_AVS_HPM_DIV},
};
static int media_update_hpm(struct avs_dev *avs_dev);
static int media_update_freq(struct avs_dev *avs_dev, struct pm_device *pm_device, int profile);

int media_AvsThread(void *Arg)
{
    struct pm_device *pm_device = (struct pm_device *)Arg;
    struct avs_dev *avs_dev = &(pm_device->avs_dev);
    unsigned long u32HpmCode, u32HpmCodeAverage = 0;
    unsigned long u32RegVal;
    int s32HpmDelta;
    U_PROFILE_REG profileReg;
    int ret;

    while (!kthread_should_stop())
    {
        msleep(media_avs_inter);

        if (false == avs_dev->avs_enable)
        {
            continue;
        }

        mutex_lock(&avs_dev->avs_lock);

#ifdef MEDIA_AVS_HPM

#ifndef MEDIA_AVS_HW
        /* get sw profile */
        HI_RegRead(&profileReg.u32, PROFILE_REG);
        //printk("profileReg.bits.sw_mda_profile: %d\n", profileReg.bits.sw_mda_profile);
        ret = media_update_freq(avs_dev, pm_device, profileReg.bits.sw_mda_profile);
        if(ret)
        {
            mutex_unlock(&avs_dev->avs_lock);            
            continue;
        }
        media_update_hpm(avs_dev);

        /* read current code */
        u32HpmCodeAverage = 0;

        HI_RegRead(&u32RegVal, PERI_PMC23);

        u32HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);
        u32HpmCodeAverage += u32HpmCode;

        u32HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
        u32HpmCodeAverage += u32HpmCode;

        HI_RegRead(&u32RegVal, PERI_PMC24);
        u32HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);

        u32HpmCodeAverage += u32HpmCode;
        u32HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
        u32HpmCodeAverage += u32HpmCode;

        u32HpmCodeAverage = u32HpmCodeAverage / 4;

        s32HpmDelta = u32HpmCodeAverage - avs_dev->cur_hpm;

        /* compare code value */
        if (s32HpmDelta <= 0x1)
        {
            /* up 10mv */
            if (pm_device->cur_volt < avs_dev->cur_volt_max)
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
                printk("%s :%d media cur_volt is %d\n",__FUNCTION__,__LINE__,pm_device->cur_volt);
			#endif
            }
        }
        else if (s32HpmDelta >= 0x10)
        {
            /*down 10mv */
            if (pm_device->cur_volt > avs_dev->cur_volt_min)
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
                printk("%s :%d media cur_volt is %d\n",__FUNCTION__,__LINE__,pm_device->cur_volt);
			#endif
            }
            
        }
        else
        {
            msleep(40);
        }
#endif

#else

#ifndef MEDIA_AVS_HW
#endif

#endif
        mutex_unlock(&avs_dev->avs_lock);
    }

    return 0;
}

void media_AvsPause(struct pm_device *pm_device)
{
    struct avs_dev *avs_dev = &pm_device->avs_dev;
    
    avs_dev->avs_enable = false;
    
    mutex_lock(&avs_dev->avs_lock);

#ifdef MEDIA_AVS_HPM

#ifdef MEDIA_AVS_HW
    iSetPERI_PMC8mda_hpm_fsm_en(0);
    msleep(10);   
#endif

#else

#ifdef MEDIA_AVS_HW
    iSetPERI_PMC67mda_ts_monitor_en(0);
    msleep(10);
#endif

#endif
}

/* after change the rate, reinitialize the hpm */
static int media_update_hpm(struct avs_dev *avs_dev)
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
            iSetPERI_PMC22mda_top_hpm_div(avs_dev->div);
            break;
        }
    }

    return 0;
}

static int media_update_freq(struct avs_dev *avs_dev, struct pm_device *pm_device, int profile)
{
    U_PROFILE_REG profileReg;
    unsigned long sw_profile;
    int ret;
    unsigned long volt;
    struct opp *opp;
    struct clk *clk;

    sw_profile = profile;
    if(sw_profile == pm_device->cur_rate)
    {
        return 0;
    }
    else if(MIN_MEDIA_PROFILE > sw_profile || MAX_MEDIA_PROFILE < sw_profile)
    {
        printk("media profile(%ld) is wrong!\n", sw_profile);
        return -1;
    }
#ifdef PM_DEBUG
    printk("sw_profile: %ld\n", sw_profile);
#endif
    clk = &pm_device->clk;    
    opp = opp_find_freq_ceil(&pm_device->device.dev, &sw_profile);
    
    volt = opp_get_voltage(opp);
#ifdef PM_DEBUG
    printk("target volt: %ld, sw_profile: %ld\n", volt, sw_profile);
#endif
    if(sw_profile > pm_device->cur_rate)
    {
        /* voltage up */
        ret = regulator_set_voltage(pm_device->reg, volt, volt);
        if (ret)
        {
            printk("%s: scale volt to %ld falt\n",
                      __func__, volt);
            return ret;
        }
        pm_device->cur_volt = regulator_get_voltage(pm_device->reg);
        
        ret = clk_set_rate(clk, sw_profile);
        if (ret)
        {
            printk("%s: scale freq to %ld falt\n",
                      __func__, sw_profile);
            return ret;
        }
        pm_device->cur_rate = clk_get_rate(clk);
    }
    else
    {
        ret = clk_set_rate(clk, sw_profile);
        if (ret)
        {
            printk("%s: scale freq to %ld falt\n",
                      __func__, sw_profile);
            return ret;
        }
        pm_device->cur_rate = clk_get_rate(clk);
        
        ret = regulator_set_voltage(pm_device->reg, volt, volt);
        if (ret)
        {
            printk("%s: scale volt to %ld falt\n",
                      __func__,volt);
            return ret;
        }
        pm_device->cur_volt = regulator_get_voltage(pm_device->reg);
    }

    avs_dev->cur_freq = pm_device->cur_rate;
    
#ifdef PM_DEBUG
    printk("pm_device->cur_rate: %d\n", pm_device->cur_rate);
#endif
    if(profileReg.bits.sw_mda_setting)
    {
        /* set media SW unsetting*/
        HI_RegSetBitEx(0, 21, 1, PROFILE_REG);
    }
    return 0;
}

void media_AvsResume(struct pm_device *pm_device)
{    
    struct avs_dev *avs_dev = &pm_device->avs_dev;
    /* this can get from register later*/    
    pm_device->cur_rate = HI_VDD_MEDIA_OPP4_PROFILE;
    avs_dev->cur_freq   = pm_device->cur_rate;
    avs_dev->avs_enable = true;

#ifdef MEDIA_AVS_HPM
    media_update_hpm(avs_dev);
#ifdef MEDIA_AVS_HW

#ifdef MEDIA_PWM
    iSetPERI_PMC25mda_top_hpm_lowlimit(avs_dev->hpm_downlimit);
    iSetPERI_PMC25mda_top_hpm_uplimit(avs_dev->hpm_uplimit);
#endif
    iSetPERI_PMC8mda_hpm_fsm_en(1);
#endif
    
#else /* MEDIA_AVS_HPM */

#ifdef MEDIA_AVS_HW
    iSetPERI_PMC67mda_ts_monitor_en(1);
#endif
    
#endif /* MEDIA_AVS_HPM */

    mutex_unlock(&avs_dev->avs_lock);
    return;
}

static struct avs_ops media_avs_ops = 
{
    .pfnAvsPause = media_AvsPause,
    .pfnAvsResume = media_AvsResume,
};

HI_VOID media_HpmInit(struct avs_dev *avs_dev)
{
    /* hpm mode */
    iSetPERI_PMC67mda_avs_ctrl_sel(0x1);

    /* reset and then unreset */
    iSetPERI_PMC22mda_top_hpm_srst_req(0x1);
    iSetPERI_PMC22mda_top_hpm_srst_req(0x0);

    /* hpm ctrl*/
    iSetPERI_PMC25mda_top_hpm_uplimit(avs_dev->hpm_uplimit);
    iSetPERI_PMC25mda_top_hpm_lowlimit(avs_dev->hpm_downlimit);
    iSetPERI_PMC25mda_top_hpm_monitor_period(avs_dev->high_period);
    iSetPERI_PMC30mda_top_hpm_monitor_period(avs_dev->low_period);

    iSetPERI_PMC22mda_top_hpm_shift(avs_dev->shift);
    iSetPERI_PMC22mda_top_hpm_offset(avs_dev->offset);

    iSetPERI_PMC22mda_top_hpm_monitor_en(0x1);    
    iSetPERI_PMC22mda_top_hpm_en(0x1);

#ifdef MEDIA_AVS_HW
    
#ifdef MEDIA_PWM
    iSetPERI_PMC8mda_avs_fsm_dec_pwm_step(avs_dev->hpm_pwm_dec_step);
    iSetPERI_PMC8mda_avs_fsm_inc_pwm_step(avs_dev->hpm_pwm_inc_step);
#endif

    iSetPERI_PMC8mda_avs_hpm_fsm_calc_mode(avs_dev->hpm_fsm_mode);    
    iSetPERI_PMC8mda_hpm_fsm_en(0x1);
#endif 

}

HI_VOID media_TsInit(struct avs_dev *avs_dev)
{
    /* ts mode */
    iSetPERI_PMC67mda_avs_ctrl_sel(0x0);

    /* ts ctrl */
    iSetPERI_PMC35mda_top_ts_sel(avs_dev->ts_crazy_mode);
    iSetPERI_PMC35mda_top_ts_dly_adjust(avs_dev->ts_crazy_path_dly);
    iSetPERI_PMC35mda_top_ts_step(avs_dev->ts_code_step);
    iSetPERI_PMC35mda_top_ts_en(0x1);
     
#ifdef MEDIA_AVS_HW
    /* ts avs */
    iSetPERI_PMC67mda_ts_en_must_inc(avs_dev->ts_avs_mode);

    iSetPERI_PMC67mda_ts_monitor_period(avs_dev->ts_avs_period);
    iSetPERI_PMC67mda_ts_monitor_en(0x1);    
#endif

}


int media_AvsInit(struct pm_device *pm_device, void *pdata)
{
    struct avs_dev *avs_dev = &pm_device->avs_dev;
    
    avs_dev->freq_hpm_table = kmalloc(sizeof(media_freq_hpm_table), GFP_KERNEL);
    if (!avs_dev->freq_hpm_table)
    {
        printk("malloc hpm table err.\n");
        return -1;
    }
    memcpy(avs_dev->freq_hpm_table, media_freq_hpm_table, sizeof(media_freq_hpm_table));
    avs_dev->max_hpm_tale_index = ARRAY_SIZE(media_freq_hpm_table);
    avs_dev->cur_freq = pm_device->cur_rate;
    avs_dev->avs_ops      = media_avs_ops;    
    avs_dev->cur_volt_max = MEDIA_VMAX; 

    media_update_hpm(avs_dev);
    
    avs_dev->avs_enable = true;
#ifdef MEDIA_AVS_HPM 
    avs_dev->hpm_uplimit   = 0x20;
    avs_dev->hpm_downlimit = 0x10;
    avs_dev->high_period   = 0x1;
    avs_dev->low_period    = 0;
    avs_dev->div           = 0xa;
    avs_dev->shift         = 0;
    avs_dev->offset        = 0; 

    avs_dev->hpm_pwm_dec_step   = 0;
    avs_dev->hpm_pwm_inc_step   = 0;
    avs_dev->hpm_fsm_mode       = 0;
    media_HpmInit(avs_dev);
#else
    avs_dev->ts_crazy_mode      = 0;
    avs_dev->ts_crazy_path_dly  = 0;
    avs_dev->ts_code_step       = 0;
    
    avs_dev->ts_avs_mode        = 0;
    avs_dev->ts_avs_period      = 0;
    media_TsInit(avs_dev);
#endif
    mutex_init(&avs_dev->avs_lock);
    avs_dev->pstAvsThread = kthread_create(media_AvsThread, (void*)pm_device,
                                                     pm_device->device.name);
    if (IS_ERR(avs_dev->pstAvsThread))
    {
        printk("create avs thread failed.\n");
        return -1;
    }

    wake_up_process(avs_dev->pstAvsThread);
    return 0;
}

int media_AvsRestore(struct pm_device *pm_device)
{
    struct avs_dev *avs_dev = &pm_device->avs_dev;
    
    avs_dev->cur_freq = pm_device->cur_rate;
    avs_dev->cur_volt_max = MEDIA_VMAX; 
    media_update_hpm(avs_dev);
    
    avs_dev->avs_enable = true;
#ifdef MEDIA_AVS_HPM 
    avs_dev->hpm_uplimit   = 0x20;
    avs_dev->hpm_downlimit = 0x10;
    avs_dev->high_period   = 0x1;
    avs_dev->low_period    = 0;
    avs_dev->div           = 0xa;
    avs_dev->shift         = 0;
    avs_dev->offset        = 0; 

    avs_dev->hpm_pwm_dec_step   = 0;
    avs_dev->hpm_pwm_inc_step   = 0;
    avs_dev->hpm_fsm_mode       = 0;
    media_HpmInit(avs_dev);
#else
    avs_dev->ts_crazy_mode      = 0;
    avs_dev->ts_crazy_path_dly  = 0;
    avs_dev->ts_code_step       = 0;
    
    avs_dev->ts_avs_mode        = 0;
    avs_dev->ts_avs_period      = 0;
    media_TsInit(avs_dev);
#endif
	return 0;
}

void media_AvsExit(struct pm_device *pm_device, void *pdata)
{
    
    if (pm_device->avs_dev.pstAvsThread)
    {
        kthread_stop(pm_device->avs_dev.pstAvsThread);
        pm_device->avs_dev.pstAvsThread = NULL;
    }
    
	/* restore uboot hw profile */
    //HI_RegRead(&profileReg.u32, PROFILE_REG);
    //printk("restore to uboot profile: %d\n", profileReg.bits.hw_mda_profile);
    media_update_freq(&pm_device->avs_dev, pm_device, DEFAULT_HW_PROFILE);
    
    if (pm_device->avs_dev.freq_hpm_table)
    {
        kfree(pm_device->avs_dev.freq_hpm_table);
        pm_device->avs_dev.freq_hpm_table = NULL;
    }
    
    return;
}
#else /* MEDIA AVS*/

void media_AvsPause(struct pm_device *pm_device){}

void media_AvsResume(struct pm_device *pm_device){}

static struct avs_ops media_avs_ops = 
{
    .pfnAvsPause = media_AvsPause,
    .pfnAvsResume = media_AvsResume,
};

int  media_AvsInit(struct pm_device *pm_device, void *pdata)
{
    pm_device->avs_dev.avs_ops = media_avs_ops;
    return 0;
}
void media_AvsExit(struct pm_device *pm_device, void *pdata){}

#endif /* MEDIA AVS*/
