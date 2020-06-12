/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_help_en.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/6/14
  Last Modified :
  Description   : hi_help_en.h header file
  Function List :
  History       :
  1.Date        : 2005/6/14
    Author      : T41030
    Modification: Created file

******************************************************************************/

#ifndef __HI_HELP_EN_H__
#define __HI_HELP_EN_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define MSG_CR         "\n"

#define MSG_NEWLINE(msg) (msg MSG_CR)


#define MSG_FILE_NotFound   "File '%s' not found."
#define MSG_FILE_Open_Error "File '%s' open error."
#define MSG_FILE_Open_Success "File '%s' open success."
#define MSG_FILE_Filename_Error "File name error."
#define MSG_THREAD_CREATE_INFO "Create Thread. name:%s, threadid:%i "

#define AZ_WAITREADY_TIMEOUT "Waitting for pools ready is timeout."
#define AZ_POOLS_NOTREADY    "Pools is not ready."


#define MSG_COMMON_NOTSUPPORT    "Not support now."

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_HELP_EN_H__ */
