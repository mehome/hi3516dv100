/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : regulator.h
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/23
  Last Modified :
  Description   : regulator.h
  Function List :
  History       :
  1.Date        : 2014/6/23
    Author      : l00165163
    Modification: Created file

******************************************************************************/
#ifndef  __REGULATOR_H__
#define  __REGULATOR_H__

#include <linux/regulator/machine.h>
#include <linux/regulator/driver.h>

#ifdef __cplusplus
#if __cplusplus
    extern "C"{
#endif
#endif /* Begin of #ifdef __cplusplus */

#define DC_DC_CPU 0
#define DC_DC_MEDIA 1

struct hisi_regulator_data
{
    struct regulator_init_data *init_data;
    struct regulator_desc *desc;

    int volt_cur;
};

int  regulator_init(void);
void regulator_exit(void);

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif /* End of #ifdef __cplusplus */
    
#endif/* End of #ifndef __PM_H__*/
