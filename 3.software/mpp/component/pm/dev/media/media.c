/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : media.c
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/25
  Last Modified :
  Description   : media.c
  Function List :
                  media_pm_exit
                  media_pm_init
  History       :
  1.Date        : 2014/6/25
    Author      : l00165163
    Modification: Created file

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* Begin of #ifdef __cplusplus */

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/clk.h>
#include <linux/io.h>

#include "pm.h"
#include "hi_dvfs.h"
#include "media.h"

static void cf_platform_device_release(struct device* dev){}
struct pm_device hi_mediafreq_device = {
    .device = {
        .name = "hisi_pm_media",
        .dev  = {
            .platform_data = NULL,
            .release       = cf_platform_device_release,
    },},

    .pfnOppTableInit  = media_OppTableInit,
    .pfnOppTableExit  = media_OppTableExit,
    .pfnClockInit     = media_ClockInit,
    .pfnClockExit     = media_ClockExit,
    .pfnRegulatorInit = media_RegulatorInit,
    .pfnRegulatorExit = media_RegulatorExit,
    .pfnAvsInit       = media_AvsInit,
    .pfnAvsExit       = media_AvsExit,
};

int media_set_profile(unsigned int new_profile)
{
    unsigned int old_profile = clk_get_rate(&hi_mediafreq_device.clk);
    
    return hi_device_scale(&hi_mediafreq_device.device.dev, old_profile, new_profile);
}
EXPORT_SYMBOL(media_set_profile);


static ssize_t media_pm_profile_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
    unsigned int profile = clk_get_rate(&hi_mediafreq_device.clk);
    
	return sprintf(buf, "profile:%u. \n", profile);
}

static ssize_t media_pm_profile_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned int profile;
	if (kstrtouint(buf, 0, &profile))
		return -EINVAL;

	media_set_profile(profile);

	return count;
}


static DEVICE_ATTR(pm_profile, S_IRUGO|S_IWUSR,
	media_pm_profile_show,
	media_pm_profile_store);

static int media_add_sysfs(void)
{
	int result;

	result = device_create_file(&hi_mediafreq_device.device.dev, &dev_attr_pm_profile);
	if (result)
		return -ENODEV;

	return 0;
}

static void media_remove_sysfs(void)
{
	device_remove_file(&hi_mediafreq_device.device.dev, &dev_attr_pm_profile);
}

static int media_pm_freeze(struct device *dev)
{
	struct pm_device *device;
	struct avs_ops *media_avs_ops;
	device = to_pm_device_ex(dev);
	media_avs_ops = &device->avs_dev.avs_ops;

	media_avs_ops->pfnAvsPause(device);
    return 0;
}

static int media_pm_restore(struct device *dev)
{
    struct pm_device *device;
	struct avs_ops *media_avs_ops;
	struct clk *clk;
	
	device = to_pm_device_ex(dev);
	clk =&device->clk;
	media_avs_ops = &device->avs_dev.avs_ops;

	media_RegulatorRestore(device);
	media_ClockRestore(&device->clk);
	media_AvsRestore(device);
	media_avs_ops->pfnAvsResume(device);
	return 0;
}
	
static struct dev_pm_ops media_pm_ops = {
	.freeze         = media_pm_freeze,
	.restore        = media_pm_restore,
};


static int __devinit media_probe(struct platform_device *device)
{
	return 0;
}
static int __devexit media_remove(struct platform_device *device)
{
	return 0;
}

static struct platform_driver hi_media_driver = {
	.driver = {
		.name  = "hisi_pm_media",
		.owner = THIS_MODULE,
		.pm = &media_pm_ops,
	},
	.probe = media_probe,
	.remove = __devexit_p(media_remove),
	
};

int __init media_pm_init(void)
{
    int ret;

    ret = pm_device_init(&hi_mediafreq_device);
    if (ret)
    {
        printk("media pm device init fail. \n");
        goto fail;
    }

    media_add_sysfs();
	
    return platform_driver_register(&hi_media_driver);
    
fail:
    return ret;
}

void media_pm_exit(void)
{
    media_remove_sysfs();
    pm_device_exit(&hi_mediafreq_device);
	platform_driver_unregister(&hi_media_driver);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
