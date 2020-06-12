/******************************************************************************

  Copyright (C), 2001-2020, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sys_pm.h
  Version       : Initial Draft
  Author        : l00165163
  Created       : 2014/6/23
  Last Modified :
  Description   : sys_pm
  Function List :
  History       :
  1.Date        : 2014/6/23
    Author      : l00165163
    Modification: Created file

******************************************************************************/
#ifndef __SYS_PM_H__
#define __SYS_PM_H__

#include <mach/io.h>/* for IO_ADDRESS */


#define MAX_FREQ_ADJUST_CNT 500
#define MAX_I2C_ADJUST_CNT 500

#define _CRG_BASE	IO_ADDRESS(0x20030000)
#define PERI_CRG0 	(_CRG_BASE + 0x0)
#define PERI_CRG1 	(_CRG_BASE + 0x4)

#define PERI_CRG2 	(_CRG_BASE + 0x8)
#define PERI_CRG3 	(_CRG_BASE + 0xC)
#define PERI_CRG11	(_CRG_BASE + 0x2C)
#define PERI_CRG12	(_CRG_BASE + 0x30)
#define PERI_CRG16	(_CRG_BASE + 0x40)
#define PERI_CRG18	(_CRG_BASE + 0x48)
#define PERI_CRG23	(_CRG_BASE + 0x5C)
#define PERI_CRG49	(_CRG_BASE + 0xC4)
#define PERI_CRG58	(_CRG_BASE + 0xE8)
#define PERI_CRG65	(_CRG_BASE + 0x104)


#define _PMC_BASE    IO_ADDRESS(0x20270000)
#define PERI_PMC0   (_PMC_BASE + 0x0)
#define PERI_PMC1   (_PMC_BASE + 0x4)

#define PERI_PMC6   (_PMC_BASE + 0x18)
#define PERI_PMC7   (_PMC_BASE + 0x1C)
#define PERI_PMC9   (_PMC_BASE + 0x24)
#define PERI_PMC14  (_PMC_BASE + 0x38)
#define PERI_PMC15  (_PMC_BASE + 0x3C)
#define PERI_PMC16  (_PMC_BASE + 0x40)
#define PERI_PMC17  (_PMC_BASE + 0x44)

#define PERI_PMC19  (_PMC_BASE + 0x4C)
#define PERI_PMC20  (_PMC_BASE + 0x50)


#define PERI_PMC22  (_PMC_BASE + 0x58)
#define PERI_PMC23  (_PMC_BASE + 0x5c)
#define PERI_PMC24  (_PMC_BASE + 0x60)
#define PERI_PMC25  (_PMC_BASE + 0x64)
#define PERI_PMC26  (_PMC_BASE + 0x68)
#define PERI_PMC29  (_PMC_BASE + 0x74)
#define PERI_PMC31  (_PMC_BASE + 0x7c)
#define PERI_PMC32  (_PMC_BASE + 0x80)
#define PERI_PMC30  (_PMC_BASE + 0x78)
#define PERI_PMC33  (_PMC_BASE + 0x84)

#define PERI_PMC58  (_PMC_BASE + 0xE8)
#define PERI_PMC65  (_PMC_BASE + 0x104)
#define PERI_PMC67  (_PMC_BASE + 0x10C)

#define HPM_PC_RECORED_MASK 0x3ff

#define _MUX_BASE    IO_ADDRESS(0x200F0000)
#define PERI_MUX83  (_MUX_BASE + 0x14C)
#define PERI_MUX84  (_MUX_BASE + 0x150)
#define PERI_MUX85  (_MUX_BASE + 0x154)
#define PERI_MUX86  (_MUX_BASE + 0x158)

#define PROFILE_REG  IO_ADDRESS(0x2005015C)

typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hw_profile            : 4   ; /* [3..0]  */
        unsigned int    volatge               : 4   ; /* [7..4]  */
        unsigned int    volatge_way           : 4   ; /* [11..8]  */        
        unsigned int    hw_mda_profile        : 4   ; /* [15..12]  */
        unsigned int    sw_mda_profile        : 4   ; /* [19..16]  */
        unsigned int    sw_mda_available      : 1   ; /* [20]  */
        unsigned int    sw_mda_setting        : 1   ; /* [21]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned long    u32;

} U_PROFILE_REG;
#endif
