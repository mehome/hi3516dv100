/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : media.h
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/20
  Last Modified :
  Description   : media_pm header file
  Function List :
  History       :
  1.Date        : 2014/6/20
    Author      : l00165163
    Modification: Created file

******************************************************************************/
#ifndef __MEDIA_H__
#define __MEDIA_H__

#include "pm.h"

/*
 * macro define
 */
 /* opp table define */

/* 1080p@30fps profile */
#define HI_VDD_MEDIA_OPP1_MV            1030
#define HI_VDD_MEDIA_OPP1_PROFILE       0
#define HI_VDD_MEDIA_OPP1_AVS_HPM       245
#define HI_VDD_MEDIA_OPP1_AVS_VMIN_MV   930
#define HI_VDD_MEDIA_OPP1_AVS_HPM_DIV   3

/* 3M@30fps profile */
#define HI_VDD_MEDIA_OPP2_MV            1030
#define HI_VDD_MEDIA_OPP2_PROFILE       1
#define HI_VDD_MEDIA_OPP2_AVS_HPM       245
#define HI_VDD_MEDIA_OPP2_AVS_VMIN_MV   930
#define HI_VDD_MEDIA_OPP2_AVS_HPM_DIV   3

/* 1080p@60fps profile */
#define HI_VDD_MEDIA_OPP3_MV            1030
#define HI_VDD_MEDIA_OPP3_PROFILE       2
#define HI_VDD_MEDIA_OPP3_AVS_HPM       245
#define HI_VDD_MEDIA_OPP3_AVS_VMIN_MV   930
#define HI_VDD_MEDIA_OPP3_AVS_HPM_DIV   4

/* 5M@30fps profile */
#define HI_VDD_MEDIA_OPP4_MV            1100
#define HI_VDD_MEDIA_OPP4_PROFILE       3
#define HI_VDD_MEDIA_OPP4_AVS_HPM       260
#define HI_VDD_MEDIA_OPP4_AVS_VMIN_MV   930
#define HI_VDD_MEDIA_OPP4_AVS_HPM_DIV   5

#define MIN_MEDIA_PROFILE HI_VDD_MEDIA_OPP1_PROFILE
#define MAX_MEDIA_PROFILE HI_VDD_MEDIA_OPP4_PROFILE
#define DEFAULT_HW_PROFILE HI_VDD_MEDIA_OPP4_PROFILE

#define MEDIA_VMAX 1310 /*mv*/
#define MEDIA_VMIN 800 /*mv*/

/*
 * function refer
 */
int  media_OppTableInit(struct pm_device *pm_device, void *pData);
void media_OppTableExit(struct pm_device *pm_device, void *pData);

int  media_RegulatorInit(struct pm_device *pm_device, void *pData);
void media_RegulatorExit(struct pm_device *pm_device, void *pData);

int  media_ClockInit(struct clk *clk, void *data);
void media_ClockExit(struct clk *clk, void *pdata);

int  media_AvsInit(struct pm_device *pm_device, void *pdata);
void media_AvsExit(struct pm_device *pm_device, void *pdata);

int  media_pm_init(void);
void media_pm_exit(void);
int media_RegulatorRestore(struct pm_device *pm_device);
int media_ClockRestore(struct clk *clk);
int media_AvsRestore(struct pm_device *pm_device);

#endif
