/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : regulator.c
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/23
  Last Modified :
  Description   : regulator.c
  Function List :
              regulator_exit
              regulator_init
              regulator_probe
  History       :
  1.Date        : 2014/6/23
    Author      : l00165163
    Modification: Created file

******************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>

#include "regulator.h"

static int __devinit regulator_probe(struct platform_device *device)
{
	struct regulator_dev *rdev;
	struct hisi_regulator_data *pdata = device->dev.platform_data;
    int ret = 0;
    
    rdev = regulator_register(pdata->desc, &device->dev, pdata->init_data, pdata, NULL);
	if (IS_ERR(rdev)) 
    {
		printk("failed to register regulator %s\n",
			pdata->desc->name);
		return -1;
	}

	platform_set_drvdata(device, rdev);
    
    if(!pdata->desc->ops->is_enabled(rdev))
    {
        ret = pdata->desc->ops->enable(rdev);
    }    
	return ret;
}

static int __devexit regulator_remove(struct platform_device *device)
{
	struct regulator_dev *rdev = platform_get_drvdata(device);

	regulator_unregister(rdev);

    return 0;
}


static struct platform_driver regulator_driver = {
	.driver = {
		.name  = "hisi_regulator",
		.owner = THIS_MODULE,
	},
	.probe = regulator_probe,
	.remove = __devexit_p(regulator_remove),
};

int __init regulator_init(void)
{
    return platform_driver_register(&regulator_driver);
}

void regulator_exit(void)
{  
	platform_driver_unregister(&regulator_driver);
}
