/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_version.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/10/24
  Last Modified :
  Description   : hi_version.c header file
  Function List :
  History       :
  1.Date        : 2005/10/24
    Author      : T41030
    Modification: Created file

******************************************************************************/


#ifndef __HI_VERSION_H__
#define __HI_VERSION_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdio.h>
typedef unsigned long HI_VERSION_T;

/*
    Version define
     31       24 23      16 15                   0
    -----------------------------------------------
    |    major  |  minor   |   build number      |
    -----------------------------------------------
*/

#define VERSION_CODE(major, minor, build) \
    ( ((major) << 24) | ((minor) << 16) | (build) )
    
#define VERSION_CODE_MAJOR(v) ((v) >> 24)
#define VERSION_CODE_MINOR(v) (((v) >> 16) & 0xFF)
#define VERSION_CODE_BUILD(v) ((v) & 0xFFFF )

#define MMPLIB_VER_MAJOR 0L
#define MMPLIB_VER_MINOR 6L
#define MMPLIB_VER_BUILD 0106L
#define MMPLIB_BUILD_DATE "20060415-V100ITr1"

#define MMPLIB_VER_EXTFLAG 0

#define GET_MMPLIB_VER VERSION_CODE(MMPLIB_VER_MAJOR, MMPLIB_VER_MINOR,MMPLIB_VER_BUILD )

static inline const char* MMPLIB_VER_STR()
{
    static char verstr[64];
    sprintf(verstr, "%02lu.%02lu.%04lu build:%s", 
                MMPLIB_VER_MAJOR, 
                MMPLIB_VER_MINOR, 
                MMPLIB_VER_BUILD,
                MMPLIB_BUILD_DATE
                );
    //printf(verstr);
    return ( (char*)verstr );
}

static inline const char* hi_version_str(HI_VERSION_T v)
{
    static char verstr[64];
    sprintf(verstr, "%02lu.%02lu.%04lu ", 
                VERSION_CODE_MAJOR(v), 
                VERSION_CODE_MINOR(v), 
                VERSION_CODE_BUILD(v)
                );
    return verstr;
}
    
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_VERSION_H__ */
