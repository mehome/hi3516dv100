#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/regulator/consumer.h>
#include <mach/io.h>
#include <linux/io.h>

#include "hi_math.h"
#include "pm.h"
#include "regulator.h"
#include "pmc.h"
#include "cpu.h"
#include "hi_io.h"
#include "sys_pm.h"

extern struct PM_DC_DC_ATTR_S g_stDcdcAttr;

struct PM_PMU_ATTR_S g_stCpuPmuAttr = {
	.min_volt = 800,
	.step = 10,
};

int hi_get_cpu_duty(int uvolt)
{
    int duty, Vpwm;

    Vpwm = g_stDcdcAttr.Vref - ((uvolt * g_stDcdcAttr.VoltConfig - g_stDcdcAttr.Vout_base) / g_stDcdcAttr.Rconfig);
    duty = Vpwm * 100 / 3300 ;
    
    return duty;
}

void cpu_VoltScale(int uvolt)
{
#ifdef CPU_PWM
    /*set duty */
    int duty;
    int freqN, freqM;
    duty = hi_get_cpu_duty(uvolt);
    freqN = g_stDcdcAttr.PwmFreqN;
    freqM = (duty * (freqN + 1)) / 100  - 1;
    
    iSetPERI_PMC1cpu_pwm_period(freqN);
    iSetPERI_PMC1cpu_pwm_duty(freqM);
#else
    int step, cnt = 0;

    step = (uvolt - g_stCpuPmuAttr.min_volt) / g_stCpuPmuAttr.step; 
   
    iSetPERI_PMC60pmu_reg4(step << 1);
    iSetPERI_PMC58pmu_reg4_wt_req(0x1);
    while (1)
    {
        unsigned int value;
        iGetPERI_PMC58pmu_reg4_wt_req(&value);
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

int cpu_get_HwVoltage(void)
{    
    int uvolt;
    
#ifdef CPU_PWM

    int Vpwm, duty, freqN, freqM, Vout_base;

    freqN = iGetPERI_PMC1cpu_pwm_period();
    freqM = iGetPERI_PMC1cpu_pwm_duty();

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
    iGetPERI_PMC60pmu_reg4(&step);

    uvolt = (step >> 1) * 10 + g_stCpuPmuAttr.min_volt;

#endif

    return uvolt;
}

static int hi_set_voltage(struct regulator_dev *rdev,
			      int min_uV, int max_uV, unsigned *selector)
{
    int clipped_volt;
    struct hisi_regulator_data *pdata = rdev->reg_data;

    clipped_volt = CLIP3(min_uV, CPU_VMIN, CPU_VMAX);

    
    cpu_VoltScale(clipped_volt);

    /* wait for volt steady */
    msleep(20);
    
    pdata->volt_cur = cpu_get_HwVoltage();
    
#ifdef PM_DEBUG
    printk("CPU cur volt is %d.\n", pdata->volt_cur);
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

#ifdef CPU_PWM
    /* set power control way to be DC_DC(pwm) */
    iSetPERI_PMC65cpu_avs_ctrl_mux(0);
    /* 1.set pin mux*/
    HI_RegSetBitEx(0x0, 0, 2, PERI_MUX86);

    /* 2.set pwm3 to control cpu  Power domain */
    iSetPERI_PMC4pwm3_reuse_cfg(0x1);

    /* 3.enable pwm*/
    iSetPERI_PMC4cpu_pwm_enable(1);

#else
    int cnt = 0;
    /* set power control way to be PMU(I2C) */
    iSetPERI_PMC65cpu_avs_ctrl_mux(1);

    /* 1.set pin mux*/
    HI_RegSetBitEx(0x2, 0, 2, PERI_MUX83);    
    HI_RegSetBitEx(0x2, 0, 2, PERI_MUX84);
    /* 2.set pmu reg4 to control cpu  Power domain */
    iSetPERI_PMC63pmu_avs_reg4_mux(0x1);
    iSetPERI_PMC63pmu_avs_reg4_en(0x1);
    /* set pmu freq 400K*/
    iSetPERI_PMC62pmc_i2c_lcnt(0x0F9F);
    iSetPERI_PMC62pmc_i2c_hcnt(0x0F9F);
    /*set i2c dev addr */
    iSetPERI_PMC58pmu_addr(0x2a);

    /* enable pmu */ 
    iSetPERI_PMC58pmc_i2c_enable(0x1);

    /* set pmu model to be 0.8-2.07v*/
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

    //g_stCpuPmuAttr.min_volt = 800;
    //g_stCpuPmuAttr.step = 10;
#endif    
    return 0;
}

static int hi_regulator_disable(struct regulator_dev *rdev)
{
#ifdef CPU_PWM
    iSetPERI_PMC4cpu_pwm_enable(0);
#else
    iSetPERI_PMC58pmc_i2c_enable(0x0);

#endif
    return 0;
}

static int hi_regulator_is_enabled(struct regulator_dev *rdev)
{    
    int bEnable;
#ifdef CPU_PWM

    iGetPERI_PMC4cpu_pwm_enable(&bEnable);
    
#else
    iGetPERI_PMC58pmc_i2c_enable(&bEnable);
#endif
    
	return bEnable;
}

static struct regulator_ops regulator_ops_cpu = {
	.set_voltage	= hi_set_voltage,
	.get_voltage	= hi_get_voltage,
	.enable		    = hi_regulator_enable,
	.disable	    = hi_regulator_disable,
	.is_enabled	    = hi_regulator_is_enabled,
};

static struct regulator_desc regulator_desc_cpu = {
        .name   = "regulator_cpu",
        .ops    = &regulator_ops_cpu,
        .id     = DC_DC_CPU,
        .type   = REGULATOR_VOLTAGE,
        .owner  = THIS_MODULE,
};

static struct regulator_consumer_supply regulator_supply_cpu = {
    .dev_name = "hisi_regulator.0",
    .supply   = "Vcc",
};

static struct regulator_init_data regulator_init_data_cpu = {
    .constraints = 
    {
            .min_uV = CPU_VMIN,
            .max_uV = CPU_VMAX,
            .valid_modes_mask = REGULATOR_MODE_NORMAL,
            .valid_ops_mask   = REGULATOR_CHANGE_VOLTAGE,           
    },
    .num_consumer_supplies = 1,
    .consumer_supplies = &regulator_supply_cpu,
};

static struct hisi_regulator_data regulator_data_cpu = {
    .init_data = &regulator_init_data_cpu,
    .desc      = &regulator_desc_cpu,
    .volt_cur  = CPU_VMAX,
};

static void cf_platform_device_release(struct device* dev){}

static struct platform_device regulator_cpu = {
    .name = "hisi_regulator",
    .id = DC_DC_CPU,
    .dev = {
            .platform_data = &regulator_data_cpu,
            .release       = cf_platform_device_release,
           },
};

int cpu_RegulatorInit(struct pm_device *pm_device, void *pData)
{
    int ret;
    int volt_cur;

    ret = platform_device_register(&regulator_cpu);
    if (ret)
    {
        printk("platform_device_register cpu fail. \n");
        goto err0;
    }    
    pm_device->reg = regulator_get(&regulator_cpu.dev, "Vcc");
    if (IS_ERR(pm_device->reg)) 
    {
        pm_device->reg = NULL;
        ret = -1;
        goto err1;
    }    
    module_put(THIS_MODULE);
    
#ifndef HI_FPGA     
    volt_cur = cpu_get_HwVoltage();
#else    
    volt_cur = CPU_VMAX;
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
    platform_device_unregister(&regulator_cpu);
err0:
    return ret;
}

void cpu_RegulatorExit(struct pm_device *pm_device, void *pData)
{
    if (pm_device->reg)
    {
        try_module_get(THIS_MODULE);
        regulator_put(pm_device->reg);
        pm_device->reg = NULL;
    }
    platform_device_unregister(&regulator_cpu);
}

int cpu_RegulatorRestore(struct pm_device *pm_device)
{
	int ret;
	int volt_cur;
	struct platform_device *device=&regulator_cpu;
	struct regulator_dev *rdev;
	struct hisi_regulator_data *pdata;
	
	rdev = (struct regulator_dev *)platform_get_drvdata(device);
	pdata = (struct hisi_regulator_data *)device->dev.platform_data;

	if(!pdata->desc->ops->is_enabled(rdev))
	{
		ret = pdata->desc->ops->enable(rdev);
	} 
  	
#ifndef HI_FPGA     
    volt_cur = cpu_get_HwVoltage();
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

