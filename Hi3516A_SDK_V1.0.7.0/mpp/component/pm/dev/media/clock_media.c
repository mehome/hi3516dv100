/*
 * hisilicon mpu clock management Routines
 *
 * Author: wangjian <stand.wang@huawei.com>
 *
 * Copyright (C) 2012 Hisilicon Instruments, Inc.
 * wangjian <stand.wang@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/device.h>
#include <linux/clkdev.h>

#include <mach/platform.h>
#include <asm/clkdev.h>
#include <mach/io.h>
#include <mach/clock.h>
#include <mach/early-debug.h>

#include "hi_math.h"
#include "hi_io.h"
#include "pm.h"
#include "sys_pm.h"
#include "media.h"
#include "hi_common.h"

int media_avs_profile = DEFAULT_HW_PROFILE;
module_param(media_avs_profile, int, S_IRUGO);



static int media_clk_set_rate(struct clk *clk, unsigned rate)
{
    unsigned cliped_rate;
    
    /* config check */
    cliped_rate = CLIP3(rate, clk->min_rate, clk->max_rate);
    if (cliped_rate != rate)
    {
        printk("warning, input rate out of clk range. \n");
    }

    if(clk->rate == cliped_rate)
    {
        return 0;
    }  
    switch (rate)
    {
        case (PROFILE_1080P_30):
        case (PROFILE_3M_30):
        {
            /**************************
               Freq VI          150M 
                    VPSS        150M
                    VGS         200M
                    VEDU        200M
                    AVC         200M
                    MDA0 AXI    200M
            ***************************/
            /* return normal status */
            HI_RegSetBitEx(0x00, 0, 2, PERI_CRG65);
            HI_RegSetBitEx(0x10, 2, 2, PERI_CRG11);
            /* mda0 axi [1:0] */
            HI_RegSetBitEx(0x2, 0, 2, PERI_CRG12);
            //HI_RegSetBitEx(0x5, 0, 3, PERI_CRG12);
            /* AVC/VGS/VPSS/VEDU [19:12] */
            HI_RegSetBitEx(0xAA, 12, 8, PERI_CRG12);
            break;
        }
        case (PROFILE_1080P_60):
        {
            /**************************
               Freq VI          200M 
                    VPSS        200M
                    VGS         237M
                    VEDU        250M
                    AVC         250M
                    MDA0 AXI    237M
            ***************************/
            /* setting debug status is to set vi-vpss 200M */
            HI_RegSetBitEx(0x3, 0, 2, PERI_CRG65);
            //HI_RegSetBitEx(0x10, 2, 2, PERI_CRG11);
            /* mda0 axi [1:0] */
            HI_RegSetBitEx(0x0, 0, 2, PERI_CRG12);
            //HI_RegSetBitEx(0x5, 0, 3, PERI_CRG12);
            /* AVC/VGS/VPSS/VEDU [19:12] */
            HI_RegSetBitEx(0x59, 12, 8, PERI_CRG12);
            break;
        }
        case (PROFILE_5M_30):
        {
            /**************************
               Freq VI          250M 
                    VPSS        250M
                    VGS         300M
                    VEDU        300M
                    AVC         300M
                    MDA0 AXI    300M
            ***************************/ 
            /* return normal status */
            HI_RegSetBitEx(0x00, 0, 2, PERI_CRG65);
            HI_RegSetBitEx(0x1, 2, 2, PERI_CRG11);
            /* mda0 axi [1:0] */
            HI_RegSetBitEx(0x1, 0, 2, PERI_CRG12);
            /* AVC/VGS/VPSS/VEDU [19:12] */
            HI_RegSetBitEx(0x4, 12, 8, PERI_CRG12);
            break;
        }
        default:
            printk("rate %d not blong to scaling_available_frequencies. \n", rate);
            return -1;
    }

    {
        unsigned long value11, value12;

        HI_RegRead(&value11, PERI_CRG11);
        HI_RegRead(&value12, PERI_CRG12);
#ifdef PM_DEBUG        
        printk("crg 12: 0x%lx, crg 11: 0x%lx \n", value11, value12);
#endif
    } 

    /* update cur profile*/
    clk->rate = cliped_rate;
    
    return 0;
}

static void media_clk_init(struct clk *clk)
{    
    int hw_profile;
    struct pm_device *pm_device = clk_to_pm_device(clk);
    
    /* this can get from register later */    
    /* get hw proflie */
    hw_profile =  media_avs_profile;
    
	/* start with uboot profile */
    clk->rate = hw_profile;
    pm_device->cur_rate = clk->rate;
    /* set sw profile */
    HI_RegSetBitEx(hw_profile, 16, 4, PROFILE_REG);

    /* set media sw available*/
    HI_RegSetBitEx(1, 20, 1, PROFILE_REG);
    return;
}

static struct clk_ops media_clock_ops = {
    .set_rate = media_clk_set_rate,
    .init     = media_clk_init,
};

int media_ClockInit(struct clk *clk, void *data)
{
    struct pm_device *pm_device = clk_to_pm_device(clk);
    
    clk->name     = "media_clk";
    clk->ops      = &media_clock_ops;
    clk->min_rate = pm_device->min_rate;
    clk->max_rate = pm_device->max_rate;
    
    clk_init(clk);
	if(clk->ops->set_rate)
	{
		if(clk->ops->set_rate(clk,clk->rate) < 0)
		{
			printk("error: media set rate fail\n");
		}
	}
    return 0;
}

int media_ClockRestore(struct clk *clk)
{

	media_clk_init(clk);
	if(clk->ops->set_rate)
	{
		if(clk->ops->set_rate(clk,clk->rate) < 0)
		{
			printk("error: media set rate fail\n");
		}
	}
    return 0;
}

void media_ClockExit(struct clk *clk, void *pdata)
{    
    /* set media sw unavailable*/
    HI_RegSetBitEx(0, 20, 1, PROFILE_REG);
    clk_exit(clk);
}
