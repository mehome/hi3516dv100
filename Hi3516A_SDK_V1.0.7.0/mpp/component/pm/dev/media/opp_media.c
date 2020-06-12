#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>

#include "pm.h"
#include "hi_opp_data.h"
#include "media.h"

/*
 * gloabl static variables
 */
static struct hi_opp_def media_opp_table[] = {
    OPP_INITIALIZER(true, HI_VDD_MEDIA_OPP1_PROFILE, HI_VDD_MEDIA_OPP1_MV),
    OPP_INITIALIZER(true, HI_VDD_MEDIA_OPP2_PROFILE, HI_VDD_MEDIA_OPP2_MV),
    OPP_INITIALIZER(true, HI_VDD_MEDIA_OPP3_PROFILE, HI_VDD_MEDIA_OPP3_MV),
    OPP_INITIALIZER(true, HI_VDD_MEDIA_OPP4_PROFILE, HI_VDD_MEDIA_OPP4_MV),
};

/*
 * functions
 */
int media_OppTableInit(struct pm_device *pm_device, void *pData)
{
    int oppsize = sizeof(media_opp_table);
    int ret;
   
     pm_device->opp_table = kmalloc(oppsize, GFP_KERNEL);
    if (!pm_device->opp_table)
    {
        ret = -ENOMEM;
        printk("malloc opptable(%d) err. \n", oppsize);
        goto err0;
    }
    memcpy((void*)pm_device->opp_table, (void*)media_opp_table, sizeof(media_opp_table));
    ret = PM_OppInitTable(&pm_device->device.dev, media_opp_table, 
                          ARRAY_SIZE(media_opp_table));
    if (ret)
    {
        printk("opptable init err. \n");
        goto err1;
    }

    pm_device->min_rate = MIN_MEDIA_PROFILE;
    pm_device->max_rate = MAX_MEDIA_PROFILE;
    
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

void media_OppTableExit(struct pm_device *pm_device, void *pData)
{
    if (pm_device->opp_table)
    {
        kfree(pm_device->opp_table);
        pm_device->opp_table = NULL;
    }
}
