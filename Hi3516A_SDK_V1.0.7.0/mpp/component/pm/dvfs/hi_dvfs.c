/*
 * hisilicon DVFS Management Routines
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

#include <linux/err.h>
#include <linux/errno.h>
#include <linux/spinlock.h>
#include <linux/plist.h>
#include <linux/slab.h>
#include "opp.h"
//#include <linux/opp.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/io.h>
#include <mach/platform.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <mach/io.h>

#include <mach/clock.h>
#include <linux/kthread.h>

#include "pm.h"
#include "hi_dvfs.h"

/**
 * struct hi_dvfs_info - The per vdd dvfs info
 * @user_lock:  spinlock for plist operations
 *
 * This is a fundamental structure used to store all the required
 * DVFS related information for a vdd.
 */
struct hi_dvfs_info
{
    unsigned long volt;
    unsigned long new_freq;
    unsigned long old_freq;
};

/**
 * _dvfs_scale() : Scale the devices associated with a voltage domain
 *
 * Returns 0 on success else the error value.
 */
static int _dvfs_scale(struct pm_device *pm_device, struct hi_dvfs_info *tdvfs_info)
{
    struct clk *clk;
    int ret;

    clk = &pm_device->clk;

    if (tdvfs_info->new_freq == tdvfs_info->old_freq)
    {
        return 0;
    }
    else
    {
        pm_device->avs_dev.avs_ops.pfnAvsPause(pm_device);
        
        if (tdvfs_info->new_freq > tdvfs_info->old_freq)
        {
            ret = regulator_set_voltage(pm_device->reg, tdvfs_info->volt,
                tdvfs_info->volt);
            if (ret)
            {
                printk("%s: scale volt to %ld falt\n",
                          __func__, tdvfs_info->volt);
                return ret;
            }
            pm_device->cur_volt = regulator_get_voltage(pm_device->reg);

            ret = clk_set_rate(clk, tdvfs_info->new_freq);
            if (ret)
            {
                printk("%s: scale freq to %ld falt\n",
                          __func__, tdvfs_info->new_freq);
                return ret;
            }
            pm_device->cur_rate = clk_get_rate(clk);
        }
        else
        {
            ret = clk_set_rate(clk, tdvfs_info->new_freq);
            if (ret)
            {
                printk("%s: scale freq to %ld falt\n",
                          __func__, tdvfs_info->new_freq);
                return ret;
            }
            pm_device->cur_rate = clk_get_rate(clk);
            
            ret = regulator_set_voltage(pm_device->reg, tdvfs_info->volt,
                tdvfs_info->volt);
            if (ret)
            {
                printk("%s: scale volt to %ld falt\n",
                          __func__, tdvfs_info->volt);
                return ret;
            }
            pm_device->cur_volt = regulator_get_voltage(pm_device->reg);
        }
        
        pm_device->avs_dev.avs_ops.pfnAvsResume(pm_device);
    }
    
    return ret;
}

/**
 * hi_device_scale() - Set a new rate at which the devices is to operate
 * @rate:   the rnew rate for the device.
 *
 * This API gets the device opp table associated with this device and
 * tries putting the device to the requested rate and the voltage domain
 * associated with the device to the voltage corresponding to the
 * requested rate. Since multiple devices can be assocciated with a
 * voltage domain this API finds out the possible voltage the
 * voltage domain can enter and then decides on the final device
 * rate.
 *
 * Return 0 on success else the error value
 */
int hi_device_scale(struct device *target_dev, unsigned long old_freq, 
                    unsigned long new_freq)
{
    struct opp *opp;
    unsigned long volt, freq = new_freq;
    struct hi_dvfs_info dvfs_info;
    struct pm_device *device;

    int ret = 0;
    device = to_pm_device_ex(target_dev);

    /* Lock me to ensure cross domain scaling is secure */
    mutex_lock(&device->dvfs_lock);

    rcu_read_lock();

    opp = opp_find_freq_ceil(target_dev, &freq);

    /* If we dont find a max, try a floor at least */
    if (IS_ERR(opp))
    {
        opp = opp_find_freq_floor(target_dev, &freq);
    }

    if (IS_ERR(opp))
    {
        rcu_read_unlock();
        printk("%s: Unable to find OPP for freq%ld\n",
                  __func__, freq);
        ret = -ENODEV;
        goto out;
    }

    volt = opp_get_voltage(opp);

    rcu_read_unlock();

    dvfs_info.old_freq = old_freq;

    dvfs_info.new_freq = freq;

    dvfs_info.volt = volt;

    /* Do the actual scaling */
    ret = _dvfs_scale(device, &dvfs_info);

    if (ret)
    {
        printk("%s: scale failed %d[f=%ld, v=%ld]\n",
                  __func__, ret, freq, volt);

        /* Fall through */
    }

    /* Fall through */
out:
    mutex_unlock(&device->dvfs_lock);
    return ret;
}
