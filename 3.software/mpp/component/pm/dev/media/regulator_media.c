#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/regulator/consumer.h>

#include "hi_math.h"
#include "pm.h"
#include "regulator.h"
#include "pmc.h"
#include "media.h"
#include "hi_io.h"
#include "sys_pm.h"

extern struct PM_DC_DC_ATTR_S g_stDcdcAttr;
struct PM_PMU_ATTR_S g_stMediaPmuAttr = {
	.min_volt = 800,
	.step = 10,
}; 

int media_get_HwVoltage(void)
{    
    int uvolt;
#ifdef MEDIA_PWM
    int Vpwm, duty, freqN, freqM, Vout_base;

    freqN = iGetPERI_PMC3mda_pwm_period();
    freqM = iGetPERI_PMC3mda_pwm_duty();

    duty = (freqM + 1) * 100 / (freqN + 1);
    Vpwm = 3300 * duty / 100;
    Vout_base = g_stDcdcAttr.Vout_base + (g_stDcdcAttr.Vref - Vpwm) * g_stDcdcAttr.Rconfig;
    uvolt = Vout_base / g_stDcdcAttr.VoltConfig;
#else
    int step, cnt = 0;
    iSetPERI_PMC58pmu_reg_rd_all(0x1);
    while (1)
    {
        unsigned int value;
        iGetPERI_PMC58pmu_reg_rd_all(&value);
        if ((!value) || (cnt >= MAX_I2C_ADJUST_CNT))
            break;
        cnt++;
        mdelay(1);
    }
    if (cnt >= MAX_I2C_ADJUST_CNT)
    {
        printk("pmu i2c set fail. \n");
        return -1;
    }
    iGetPERI_PMC59pmu_reg3(&step);

    uvolt = (step >> 1) * 10 + g_stMediaPmuAttr.min_volt;
    
#endif

    return uvolt;
}

int hi_get_media_duty(int uvolt)
{
    int duty, Vpwm;

    Vpwm = g_stDcdcAttr.Vref - ((uvolt * g_stDcdcAttr.VoltConfig - g_stDcdcAttr.Vout_base) / g_stDcdcAttr.Rconfig);
    duty = Vpwm * 100 / 3300 ;
    
    return duty;
}

void media_VoltScale(unsigned int uvolt)
{
#ifdef MEDIA_PWM
    /* set duty cycle */
    int duty;
    int freqN, freqM;
    duty = hi_get_media_duty(uvolt);
    freqN = g_stDcdcAttr.PwmFreqN;
    freqM = (duty * (freqN + 1)) / 100  - 1;

    iSetPERI_PMC3mda_pwm_period(freqN);
    iSetPERI_PMC3mda_pwm_duty(freqM);

#else
    int step, cnt = 0;

    step = (uvolt - g_stMediaPmuAttr.min_volt) / g_stMediaPmuAttr.step; 
   
    iSetPERI_PMC59pmu_reg3(step << 1);
    iSetPERI_PMC58pmu_reg3_wt_req(0x1);
    while (1)
    {
        unsigned int value;
        iGetPERI_PMC58pmu_reg3_wt_req(&value);
        if ((!value) || (cnt >= MAX_I2C_ADJUST_CNT))
            break;
        cnt++;
        mdelay(1);
    }
    if (cnt >= MAX_I2C_ADJUST_CNT)
    {
        printk("pmu i2c set fail. \n");
        return -1;
    }
#endif

    return;
}
static int hi_set_voltage(struct regulator_dev *rdev,
			      int min_uV, int max_uV, unsigned *selector)
{
    unsigned int clipped_volt;
    struct hisi_regulator_data *pdata = rdev->reg_data;


    clipped_volt = CLIP3(min_uV, MEDIA_VMIN, MEDIA_VMAX);
    
    media_VoltScale(clipped_volt);
    msleep(20);
    pdata->volt_cur = media_get_HwVoltage();
    
#ifdef PM_DEBUG
    printk("Media cur volt is %d.\n", pdata->volt_cur);
#endif
	return 0;
}

static int hi_get_voltage(struct regulator_dev *rdev)
{
    struct hisi_regulator_data *pdata = rdev->reg_data;
    
	return pdata->volt_cur;
}

static int hi_regulator_enable(struct regulator_dev *rdev)
{

#ifdef MEDIA_PWM
    iSetPERI_PMC67mda_avs_ctrl_mux(0);
    HI_RegSetBitEx(0x0, 0, 2, PERI_MUX85);

    iSetPERI_PMC4pwm2_reuse_cfg(0x3);

    iSetPERI_PMC4mda_pwm_enable(1);

#else
    int cnt = 0;
    iSetPERI_PMC67mda_avs_ctrl_mux(1);

    HI_RegSetBitEx(0x2, 0, 2, PERI_MUX83);    
    HI_RegSetBitEx(0x2, 0, 2, PERI_MUX84);
    
    iSetPERI_PMC63pmu_avs_reg3_mux(0x11);
    iSetPERI_PMC63pmu_avs_reg3_en(0x1);
    
    iSetPERI_PMC62pmc_i2c_lcnt(0x0F9F);
    iSetPERI_PMC62pmc_i2c_hcnt(0x0F9F);
    
    iSetPERI_PMC58pmu_addr(0x2a);

    iSetPERI_PMC58pmc_i2c_enable(0x1);

    iSetPERI_PMC60pmu_reg7(0x0);    
    iSetPERI_PMC58pmu_reg7_wt_req(0x1);
    while (1)
    {
        unsigned int value;
        iGetPERI_PMC58pmu_reg7_wt_req(&value);
        if ((!value) || (cnt >= MAX_I2C_ADJUST_CNT))
            break;
        cnt++;
        mdelay(1);
    }
    if (cnt >= MAX_I2C_ADJUST_CNT)
    {
        printk("%s:%d pmu i2c set fail. \n", __FUNCTION__, __LINE__);
        return -1;
    }

    //g_stMediaPmuAttr.min_volt = 800;
    //g_stMediaPmuAttr.step = 10;
#endif    
    return 0;

    return 0;
}

static int hi_regulator_disable(struct regulator_dev *rdev)
{
#ifdef MEDIA_PWM
        iSetPERI_PMC4mda_pwm_enable(0);
#else
        iSetPERI_PMC58pmc_i2c_enable(0x0);
#endif
    return 0;
}

static int hi_regulator_is_enabled(struct regulator_dev *rdev)
{
        int bEnable;
#ifdef MEDIA_PWM
    
        iGetPERI_PMC4mda_pwm_enable(&bEnable);
        
#else
        iGetPERI_PMC58pmc_i2c_enable(&bEnable);
#endif
        
        return bEnable;
}

static struct regulator_ops regulator_ops_media = {
	.set_voltage	= hi_set_voltage,
	.get_voltage	= hi_get_voltage,
	.enable		    = hi_regulator_enable,
	.disable	    = hi_regulator_disable,
	.is_enabled	    = hi_regulator_is_enabled,
};

static struct regulator_desc regulator_desc_media = {
        .name   = "regulator_media",
        .ops    = &regulator_ops_media,
        .id     = DC_DC_MEDIA,
        .type   = REGULATOR_VOLTAGE,
        .owner  = THIS_MODULE,
};

static struct regulator_consumer_supply regulator_supply_media = {
    .dev_name = "hisi_regulator.1",
    .supply   = "Vcc",
};

static struct regulator_init_data regulator_init_data_media = {
    .constraints = 
    {
            .min_uV = MEDIA_VMIN,
            .max_uV = MEDIA_VMAX,
            .valid_modes_mask = REGULATOR_MODE_NORMAL,
            .valid_ops_mask   = REGULATOR_CHANGE_VOLTAGE,           
    },
    .num_consumer_supplies = 1,
    .consumer_supplies = &regulator_supply_media,
};

static struct hisi_regulator_data regulator_data_media = {
    .init_data = &regulator_init_data_media,
    .desc      = &regulator_desc_media,
    .volt_cur  = MEDIA_VMAX,
};
static void cf_platform_device_release(struct device* dev){}

static struct platform_device regulator_media = {
    .name = "hisi_regulator",
    .id = DC_DC_MEDIA,
    .dev = {
            .platform_data = &regulator_data_media,
            .release       = cf_platform_device_release,
           },
};

int media_RegulatorInit(struct pm_device *pm_device, void *pData)
{
    int ret;
    int volt_cur;
    ret = platform_device_register(&regulator_media);
    if (ret)
    {
        printk("platform_device_register media fail. \n");
        goto err0;
    }
    pm_device->reg = regulator_get(&regulator_media.dev, "Vcc");
    if (IS_ERR(pm_device->reg)) 
    {
        printk("%s: unable to get media regulator\n", __func__);
        pm_device->reg = NULL;
        ret = -1;
        goto err1;
    } 
    module_put(THIS_MODULE); 
    
#ifndef HI_FPGA     
    volt_cur = media_get_HwVoltage();
#else    
    volt_cur = MEDIA_VMAX;
#endif
    ret = regulator_set_voltage(pm_device->reg, volt_cur, volt_cur);
    if (ret)
    {
        printk("%s: scale volt to %u falt\n", __func__, volt_cur);
        return ret;
    }
    pm_device->cur_volt = regulator_get_voltage(pm_device->reg);

    return 0;
err1:
    platform_device_unregister(&regulator_media);
err0:
    return ret;
}

void media_RegulatorExit(struct pm_device *pm_device, void *pData)
{
    if (pm_device->reg)
    {
        try_module_get(THIS_MODULE); 
        regulator_put(pm_device->reg);
        
        pm_device->reg = NULL;
    } 
    platform_device_unregister(&regulator_media);
}

int media_RegulatorRestore(struct pm_device *pm_device)
{
	int ret;
	int volt_cur;
	struct platform_device *device=&regulator_media;
	struct regulator_dev *rdev;
	struct hisi_regulator_data *pdata;
	
	rdev = (struct regulator_dev *)platform_get_drvdata(device);
	pdata = (struct hisi_regulator_data *)device->dev.platform_data;

	if(!pdata->desc->ops->is_enabled(rdev))
	{
		ret = pdata->desc->ops->enable(rdev);
	} 
  	
#ifndef HI_FPGA     
    volt_cur = media_get_HwVoltage();
#else    
    volt_cur = MEDIA_VMAX;
#endif
    ret = regulator_set_voltage(pm_device->reg, volt_cur, volt_cur);
    if (ret)
    {
        printk("%s: scale volt to %u falt\n", __func__, volt_cur);
        return ret;
    }
    pm_device->cur_volt = regulator_get_voltage(pm_device->reg);

    return 0;
}