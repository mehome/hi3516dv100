/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : pm.h
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/5/20
  Last Modified :
  Description   : pm.h
  Function List :
  History       :
  1.Date        : 2014/5/20
    Author      : l00165163
    Modification: Created file

******************************************************************************/
#ifndef  __PM_H__
#define  __PM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* Begin of #ifdef __cplusplus */

#include <linux/platform_device.h>
#include <linux/of_device.h>
#include <linux/clk.h>
#include <mach/io.h>
#include <mach/clock.h>

#include "hi_opp_data.h"
#include "hi_clock.h"
#include "regulator.h"
#include "avs_pm.h"

#define PM_CPU      (0x01L<<0)
#define PM_MEDIA    (0x01L<<0)

#define PM_R1    127  //12.7k|?
#define PM_R2    127  //12.7k|?
#define PM_R3    806  //80.6k|?
#define PM_R4    5    //0.5k|?
#define PM_R5    10   //1k|?
#define PM_VREF  608  //608mv

struct PM_DC_DC_ATTR_S
{
    int Vref;
    int R1;
    int R2;
    int R3;
    int R4;
    int PwmFreqN;
    int Vout_base;
    int VoltConfig; 
    int Rconfig;
};

struct PM_PMU_ATTR_S
{
    int min_volt;
    int step;
};

/*
 * define for pm trace;
 */
#define PM_TRACE(level, fmt...)\
do{ \
        HI_TRACE(level, HI_ID_PM, "[Func]:%s [Line]:%d [Info]:", __FUNCTION__, __LINE__);\
        HI_TRACE(level, HI_ID_PM, ##fmt);\
}while(0)

struct pm_device;

typedef int  pfnOppTableInit(struct pm_device *, void *);
typedef void pfnOppTableExit(struct pm_device *, void *);
typedef int  pfnRegulatorInit(struct pm_device *, void *);
typedef void pfnRegulatorExit(struct pm_device *, void *);
typedef int  pfnClockInit(struct clk *, void *);
typedef void pfnClockExit(struct clk *, void *);
typedef int  pfnAvsInit(struct pm_device *, void *);
typedef void pfnAvsExit(struct pm_device *, void *);

/*
 * pm device
 * @device: device of pm device
 * @freq_table: freq of the device;
 * @mpu_clk: 
 */
struct pm_device
{
    struct platform_device device;
    
    /* freq table */
    struct cpufreq_frequency_table *freq_table;
    struct mutex freq_table_lock;

    struct hi_opp_def *opp_table;
    pfnOppTableInit *pfnOppTableInit;
    pfnOppTableExit *pfnOppTableExit;
    unsigned int min_rate;
    unsigned int max_rate;

    /* clk */
    struct clk clk;
    pfnClockInit *pfnClockInit;
    pfnClockExit *pfnClockExit;
    unsigned int cur_rate;

    /*regulator(pmu/dc)*/
    struct regulator *reg;
    pfnRegulatorInit *pfnRegulatorInit;
    pfnRegulatorExit *pfnRegulatorExit;
    unsigned int cur_volt;

    /* dvfs */
    struct mutex dvfs_lock;
	unsigned int dvfs_en;

    /* avs staff */
    pfnAvsInit *pfnAvsInit;
    pfnAvsExit *pfnAvsExit;
    struct avs_dev avs_dev;
};

#define to_pm_device(x) container_of((x), struct pm_device, device)
#define to_pm_device_ex(x) to_pm_device(to_platform_device(x))
#define clk_to_pm_device(x) container_of((x), struct pm_device, clk)

int  pm_device_init(struct pm_device *pm_device);
void pm_device_exit(struct pm_device *pm_device);




#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif /* End of #ifdef __cplusplus */
    
#endif/* End of #ifndef __PM_H__*/

