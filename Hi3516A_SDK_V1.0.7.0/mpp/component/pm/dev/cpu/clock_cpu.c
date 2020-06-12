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
#include "cpu.h"

static void HI_SetCpuApll(unsigned rate)
{    
    HI_U32 u32Frac, u32Postdiv1, u32Postdiv2, u32Fbdiv, u32Refdiv;
    
    switch (rate)
    {
        case (HI_VDD_CPU_OPP1_FREQ):
        {
            u32Frac = 0;
            u32Postdiv1 = 2;
            u32Postdiv2 = 1;
            u32Refdiv = 1;
            u32Fbdiv = 50;
            break;
        }
        case (HI_VDD_CPU_OPP2_FREQ):
        {
            u32Frac = 0;
            u32Postdiv1 = 1;
            u32Postdiv2 = 1;
            u32Refdiv = 24;
            u32Fbdiv = 732;
            break;
        }
        case (HI_VDD_CPU_OPP3_FREQ):
        {
            u32Frac = 0;
            u32Postdiv1 = 1;
            u32Postdiv2 = 1;
            u32Refdiv = 24;
            u32Fbdiv = 850;
            break;
        }
        case (HI_VDD_CPU_OPP4_FREQ):
        {
            u32Frac = 0;
            u32Postdiv1 = 1;
            u32Postdiv2 = 1;
            u32Refdiv = 24;
            u32Fbdiv = 500;
            break;
        }
        case (HI_VDD_CPU_OPP5_FREQ):
        {
            u32Frac = 0;
            u32Postdiv1 = 1;
            u32Postdiv2 = 1;
            u32Refdiv = 24;
            u32Fbdiv = 400;
            break;
        }
        case (HI_VDD_CPU_OPP6_FREQ):
        {
            u32Frac = 0;
            u32Postdiv1 = 1;
            u32Postdiv2 = 1;
            u32Refdiv = 24;
            u32Fbdiv = 300;
            break;
        }
        case (HI_VDD_CPU_OPP7_FREQ):
        {
            u32Frac = 0;
            u32Postdiv1 = 1;
            u32Postdiv2 = 1;
            u32Refdiv = 24;
            u32Fbdiv = 200;
            break;
        }
        case (HI_VDD_CPU_OPP8_FREQ):
        {
            u32Frac = 0;
            u32Postdiv1 = 1;
            u32Postdiv2 = 1;
            u32Refdiv = 24;
            u32Fbdiv = 100;
            break;
        }
        default:
            printk("rate %d not blong to scaling_available_frequencies. \n", rate);
            return;
    }
    HI_RegSetBitEx(u32Frac, 0, 24, PERI_CRG0);
    HI_RegSetBitEx(u32Postdiv1, 24, 3, PERI_CRG0);
    HI_RegSetBitEx(u32Postdiv2, 28, 3, PERI_CRG0);
    HI_RegSetBitEx(u32Fbdiv, 0, 12, PERI_CRG1);
    HI_RegSetBitEx(u32Refdiv, 12, 6, PERI_CRG1);

    return;
}
/*
 * notes:
 */
static int cpu_clk_set_rate(struct clk *clk, unsigned rate)
{
    unsigned int cnt = 0;
    unsigned cliped_rate;

    /* check config */
    cliped_rate = CLIP3(rate, clk->min_rate, clk->max_rate);
    if (cliped_rate != rate)
    {
        printk("warning, input rate(%d) out of clk range[%d, %d]. \n", rate, clk->min_rate, clk->max_rate);        
        return -1;
    }

    /* 1.set PERI_CRG12[9:8] to be 0x1 or 0x2,make cpu working freq to be 500MHz or 400MHz */
    HI_RegSetBitEx(0x1, 8, 2, PERI_CRG12);
    /* 2.set PERI_CRG0 and PERI_CRG1,change APLL_FOUTPOSTDIV to be target */
    HI_SetCpuApll(cliped_rate);
    
    /* 3.wait for the success of APLL LOCK */
    while (1)
    {
        unsigned long value;
        HI_RegRead(&value, PERI_CRG58);
        if ((value & 0x1) || (cnt >= MAX_FREQ_ADJUST_CNT))
            break;
        cnt++;
        mdelay(1);
    }

    /* delay 1ms after apll lock */
    mdelay(1);
    
    if (cnt >= MAX_FREQ_ADJUST_CNT)
    {
        printk("cpu set rate fail. \n");
        return 0;
    }
    
    /* 4.set PERI_CRG12[9:8] to be 0x0,make cpu working freq to be APLL_FOUTPOSTDIV*/
    HI_RegSetBitEx(0x0, 8, 2, PERI_CRG12);
    
#ifdef PM_DEBUG
    printk("cur_rate is %d.\n", cliped_rate);
#endif
    /* 5.update current freq */
    clk->rate = cliped_rate;
    return 0;
}

static void cpu_clk_init(struct clk *clk)
{
    unsigned int clk_rate;
    struct pm_device *pm_device = clk_to_pm_device(clk);
    
    /* 1.read PERI_CRG12[9:8],get Clock source of cpu*/
    unsigned long value;
    unsigned cpu_sel;
    HI_RegRead(&value, PERI_CRG12);
    cpu_sel = value & 0x300;
    if(0x100 == cpu_sel)
    {
        clk_rate = 500;
    }
    else if(0x200 == cpu_sel)
    {
        clk_rate = 400;
    }
    else 
    {        
        unsigned long cpu_sel_addr0, cpu_sel_addr1;
        unsigned fbdiv, frac, refdiv, pstdiv1, pstdiv2;
        if(0x0 == cpu_sel)
        {
            cpu_sel_addr0 = PERI_CRG0;            
            cpu_sel_addr1 = PERI_CRG1;
        }
        else
        {
            
#ifdef PM_DEBUG
            printk("cpu sel from Bpll. \n"); 
#endif
            cpu_sel_addr0 = PERI_CRG2;            
            cpu_sel_addr1 = PERI_CRG3;
        }
        HI_RegRead(&value, cpu_sel_addr0);
        frac    = 0xFFFFFF & value;
        pstdiv1 = ((0x7 << 24) & value) >> 24;
        pstdiv2 = ((0x7 << 28) & value) >> 28;
        HI_RegRead(&value, cpu_sel_addr1);
        fbdiv   = 0xFFF & value;
        refdiv  = ((0x3F << 12) & value) >> 12;

        clk_rate = 24 * (fbdiv + (frac >> 24)) / (refdiv * pstdiv1 * pstdiv2);
        
    }
    
    clk->rate = clk_rate;
    pm_device->cur_rate = clk_rate;
#ifdef PM_DEBUG
    printk("init cur_rate is %d.\n", clk_rate);
#endif
    return;
}

static struct clk_ops cpu_clock_ops = {
    .set_rate = cpu_clk_set_rate,
    .init     = cpu_clk_init,
};

int cpu_ClockInit(struct clk *clk, void *data)
{
    struct pm_device *pm_device = clk_to_pm_device(clk);
    
    clk->name     = "cpu_clk";
    clk->ops      = &cpu_clock_ops;
    clk->min_rate = pm_device->min_rate;
    clk->max_rate = pm_device->max_rate;
    
    clk_init(clk);
    return 0;
}

void cpu_ClockExit(struct clk *clk, void *pdata)
{
    clk_exit(clk);
}

int cpu_ClockRestore(struct clk *clk)
{

	//cpu_clk_init(clk);
	if(clk->ops->set_rate)
	{
		if(clk->ops->set_rate(clk,clk->rate) < 0)
		{
			printk("error: media set rate fail\n");
		}
	}
    return 0;
}

