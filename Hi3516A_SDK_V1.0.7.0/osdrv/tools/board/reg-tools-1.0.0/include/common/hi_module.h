/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_module.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/4/23
  Last Modified :
  Description   : 系统模块的定义
  Function List :
  History       :
  1.Date        : 2005/4/23
    Author      : T41030
    Modification: Created file

******************************************************************************/

#ifndef __HI_MODULE_H__
#define __HI_MODULE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef enum tag_MODULE
{
    MODULE_GENERAL = 0,
    MODULE_SYS     = 1 ,  /*系统模块*/           
    MODULE_DRV     = 2 ,  /*驱动模块*/
    MODULE_MMF     = 3,   /*MultiMedia Frame*/
    MODULE_APP     = 4,   /*应用模块*/

    MODULE_BUTT         /*结束标志*/
}MODULE_E;

typedef enum tag_SYS_SUB_MODULE
{
    SYS_SUB_MODULE_AZ   = 1, /*Arm ZSP Message Communication*/
    SYS_SUB_MODULE_RB   = 2, /*Ring Buffer */
    SYS_SUB_MODULE_BM   = 3, /*Buffer Manager*/
    SYS_SUB_MODULE_MQ   = 4, /*Message Queue*/
    SYS_SUB_MODULE_THREAD = 5,
    SYS_SUB_MODULE_BUTT
}SYS_SUB_MODULE;

typedef enum tag_DRV_SUB_MODULE
{
    DRV_SUB_MODULE_VIU   = 1, /*Video In Unit*/
    DRV_SUB_MODULE_VOU   = 2, /*Video Out Unit*/
    DRV_SUB_MODULE_DSU  = 3, /*DS Unit*/
    DRV_SUB_MODULE_USB  = 4, /*USB*/
    DRV_SUB_MODULE_SF   = 5, /*Soft Switch*/
    DRV_SUB_MODULE_TDE   = 6, /*2d accelarate */
    
    DRV_SUB_MODULE_BUTT
}DRV_SUB_MODULE;

typedef enum tag_MMF_SUB_MODULE
{
    MMF_SUB_MODULE_INPUT = 1, 
    MMF_SUB_MODULE_DEMUX = 2,
    MMF_SUB_MODULE_MUX   = 3,
    MMF_SUB_MODULE_AO    = 4,
    MMF_SUB_MODULE_VO    = 5, 
    MMF_SUB_MODULE_STREAM = 6,
    MMF_SUB_MODULE_VDEC = 7,
    MMF_SUB_MODULE_JB = 8,
    
    MMF_SUB_MODULE_BUTT
}MMF_SUB_MODULE;

typedef enum tag_APP_SUB_MODULE
{
    APP_SUB_MODULE_VAPI = 1, 

    APP_SUB_MODULE_BUTT
}APP_SUB_MODULE;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_MODULE_H__ */
