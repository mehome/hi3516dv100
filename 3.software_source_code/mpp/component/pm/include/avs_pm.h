/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : avs_pm.h
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/23
  Last Modified :
  Description   : avs.h
  Function List :
  History       :
  1.Date        : 2014/6/23
    Author      : l00165163
    Modification: Created file

******************************************************************************/
#ifndef __AVS_PM_H__
#define __AVS_PM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

struct avs_dev;
struct pm_device;

typedef void pfnAvsPause(struct pm_device *);
typedef void pfnAvsResume(struct pm_device *);

struct avs_ops
{
    pfnAvsPause  *pfnAvsPause;
    pfnAvsResume *pfnAvsResume;
};

typedef struct hiHPM_VF_S
{
    unsigned int freq;          /* unit: kHz */
    unsigned int vmin;
    unsigned int hpmrecord;     /* hpm record */    
    unsigned int div;           /* frequency division ratio */
} HPM_VF_S;

struct avs_dev
{
    unsigned int avs_enable;

    struct avs_ops avs_ops;
    struct task_struct *pstAvsThread;    
    struct mutex avs_lock;

    unsigned int cur_volt_max;
    unsigned int cur_volt_min;

    HPM_VF_S *freq_hpm_table;
    unsigned int max_hpm_tale_index;

    /* hpm ctrl param */
    unsigned int cur_freq;
    unsigned int cur_hpm;
    unsigned int hpm_uplimit;
    unsigned int hpm_downlimit;
    unsigned int low_period;
    unsigned int high_period;
    unsigned int div;
    unsigned int shift;
    unsigned int offset;

    /* hw avs hpm parameter */
    unsigned int hpm_fsm_mode;
    unsigned int hpm_pwm_inc_step;
    unsigned int hpm_pwm_dec_step;

    /* timing sensor ctrl parameter */
    unsigned int ts_crazy_mode;
    unsigned int ts_crazy_path_dly;
    unsigned int ts_code_step;

    /* timing sensor hw avs parameter */
    unsigned int ts_avs_mode;
    unsigned int ts_avs_period;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
