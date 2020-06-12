/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : avs.c
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/28
  Last Modified :
  Description   : avs.c
  Function List :
              avs_pause
              avs_resume
  History       :
  1.Date        : 2014/6/28
    Author      : l00165163
    Modification: Created file

******************************************************************************/

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/io.h>

#include "avs_pm.h"
#include "pm.h"

