/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : cpu.h
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/20
  Last Modified :
  Description   : cpu_pm header file
  Function List :
  History       :
  1.Date        : 2014/6/20
    Author      : l00165163
    Modification: Created file

******************************************************************************/
#ifndef __CPU_H__
#define __CPU_H__

#include "pm.h"

/*
 * macro define
 */
 /* opp table define */
#define HI_VDD_CPU_OPP1_MV 1100
#define HI_VDD_CPU_OPP1_FREQ 600
#define HI_VDD_CPU_OPP1_AVS_VMIN_MV 940
#define HI_VDD_CPU_OPP1_AVS_HPM 270
#define HI_VDD_CPU_OPP1_AVS_HPM_DIV 11

#define HI_VDD_CPU_OPP2_MV 1200
#define HI_VDD_CPU_OPP2_FREQ 732
#define HI_VDD_CPU_OPP2_AVS_VMIN_MV 1000
#define HI_VDD_CPU_OPP2_AVS_HPM 325
#define HI_VDD_CPU_OPP2_AVS_HPM_DIV 14

#define HI_VDD_CPU_OPP3_MV 1300      
#define HI_VDD_CPU_OPP3_FREQ 850 
#define HI_VDD_CPU_OPP3_AVS_VMIN_MV 1070
#define HI_VDD_CPU_OPP3_AVS_HPM 365
#define HI_VDD_CPU_OPP3_AVS_HPM_DIV 16

#define HI_VDD_CPU_OPP4_MV 1060
#define HI_VDD_CPU_OPP4_FREQ 500
#define HI_VDD_CPU_OPP4_AVS_VMIN_MV 940
#define HI_VDD_CPU_OPP4_AVS_HPM 255
#define HI_VDD_CPU_OPP4_AVS_HPM_DIV 10

#define HI_VDD_CPU_OPP5_MV 1020
#define HI_VDD_CPU_OPP5_FREQ 400
#define HI_VDD_CPU_OPP5_AVS_VMIN_MV 940
#define HI_VDD_CPU_OPP5_AVS_HPM 240
#define HI_VDD_CPU_OPP5_AVS_HPM_DIV 8

#define HI_VDD_CPU_OPP6_MV 1020
#define HI_VDD_CPU_OPP6_FREQ 300
#define HI_VDD_CPU_OPP6_AVS_VMIN_MV 940
#define HI_VDD_CPU_OPP6_AVS_HPM 240
#define HI_VDD_CPU_OPP6_AVS_HPM_DIV 6

#define HI_VDD_CPU_OPP7_MV 1020
#define HI_VDD_CPU_OPP7_FREQ 200
#define HI_VDD_CPU_OPP7_AVS_VMIN_MV 940
#define HI_VDD_CPU_OPP7_AVS_HPM 240
#define HI_VDD_CPU_OPP7_AVS_HPM_DIV 4

#define HI_VDD_CPU_OPP8_MV 1020
#define HI_VDD_CPU_OPP8_FREQ 100
#define HI_VDD_CPU_OPP8_AVS_VMIN_MV 940
#define HI_VDD_CPU_OPP8_AVS_HPM 240
#define HI_VDD_CPU_OPP8_AVS_HPM_DIV 2

//#define MIN_CPU_FREQ HI_VDD_CPU_OPP1_FREQ
#define MIN_CPU_FREQ HI_VDD_CPU_OPP5_FREQ
#define MAX_CPU_FREQ HI_VDD_CPU_OPP3_FREQ

#define CPU_VMAX 1310 /*mv*/
#define CPU_VMIN 800 /*mv*/

/*
 * function refer
 */
int  cpu_OppTableInit(struct pm_device *pm_device, void *pData);
void cpu_OppTableExit(struct pm_device *pm_device, void *pData);

int  cpu_RegulatorInit(struct pm_device *pm_device, void *pData);
void cpu_RegulatorExit(struct pm_device *pm_device, void *pData);

int  cpu_ClockInit(struct clk *clk, void *data);
void cpu_ClockExit(struct clk *clk, void *pdata);

int  cpu_AvsInit(struct pm_device *pm_device, void *pdata);
void cpu_AvsExit(struct pm_device *pm_device, void *pdata);

int  cpu_pm_init(void);
void cpu_pm_exit(void);

int cpu_RegulatorRestore(struct pm_device *pm_device);
int cpu_ClockRestore(struct clk *clk);
int cpu_AvsRestore(struct pm_device *pm_device);




#endif
