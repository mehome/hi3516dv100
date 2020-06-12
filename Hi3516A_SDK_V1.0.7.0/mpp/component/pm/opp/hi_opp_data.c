/*
 * HI OPP table definitions.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *  Nishanth Menon
 *  Kevin Hilman
 *  Thara Gopinath
 * Copyright (C) 2010-2011 Nokia Corporation.
 *      Eduardo Valentin
 *      Paul Walmsley
 * Copyright (C) 2012-2013 Hisilicon Corporation.
 *      wang jian
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <linux/module.h>

#include "opp.h"
//#include <linux/opp.h>
#include "hi_opp_data.h"


/**
 * PM_init_opp_table() - Initialize opp table as per the CPU type
 * @opp_def:		opp default list for this silicon
 * @opp_def_size:	number of opp entries for this silicon
 *
 * Register the initial OPP table with the OPP library based on the CPU
 * type. This is meant to be used only by SoC specific registration.
 */
int PM_OppInitTable(struct device *device, struct hi_opp_def *opp_def, 
                                unsigned int opp_def_size)
{
    int i, r;

    if (!device || !opp_def || !opp_def_size)
    {
        printk("%s: invalid params!\n", __func__);
        return -EINVAL;
    }

    /* Lets now register with OPP library */
    for (i = 0; i < opp_def_size; i++)
    {
        /* todo opp */
        r = opp_add(device, opp_def->freq, opp_def->u_volt);
        if (r)
        {
            printk("%s: add OPP %ld failed for [%d] "
                      "result=%d\n",
                      __func__, opp_def->freq,
                      i, r);
        }
        else
        {
            if (!opp_def->default_available)
            {
                r = opp_disable(device, opp_def->freq);
            }

            if (r)
            {
                printk("%s: disable %ld failed for"
                          "[%d] result=%d\n",
                          __func__, opp_def->freq,
                          i, r);
            }
        }

        opp_def++;
    }

    return 0;
}


int __init PM_FreqtableInit(struct device *dev, 
                                struct cpufreq_frequency_table **table)
{
    return opp_init_cpufreq_table(dev, table);
}

void PM_FreqtableExit(struct device *dev, 
                                struct cpufreq_frequency_table **table)
{
    opp_free_cpufreq_table(dev, table);

    
}
