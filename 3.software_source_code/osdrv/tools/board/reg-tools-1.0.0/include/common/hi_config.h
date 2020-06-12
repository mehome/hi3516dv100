/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_config.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/5/30
  Last Modified :
  Description   : hi_config.h header file
  Function List :
  History       :
  1.Date        : 2005/5/30
    Author      : T41030
    Modification: Created file

******************************************************************************/

#ifndef __HI_CONFIG_H__
#define __HI_CONFIG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#if defined(TARGET_X86)

/* 在Makefile中
    在PC机模拟的实现
    在PC机模拟时(linux), 不直接访问物理内存地址, 更改为分配一块内存的方式来获取消息区
*/

//#define PC_EMULATOR
/*#undefine PC_EMULATOR*/

/*是否使用BTRACE的调试库*/
/*#define USE_BTRACE*/
/*#undefine USE_BTRACE*/
#endif


/* 调试模式 */
#define DEBUG
/*#define RELEASE*/

/*LINUX 操作系统*/
#define OS_LINUX

/**/


/************ 在makefile 中 -D ******/
/*模拟ARM侧的程序, 用-DARM_CPU*/
/*#define ARM_CPU*/

/*模拟ZSP侧的程序, 用-DZSP_CPU*/
/*#define ZSP_CPU*/


/*是否执行打印函数*/
#define LOGQUEUE

/*是否作Arm和ZSP通讯的统计*/
#define AZ_STAT

/*多任务的logqueue*/
#define MULTI_TASK_LOGQUEUE

/*ARM和ZSP间通讯使用中断方式*/
#define USE_AZ_INT

#define STAT


#if 0
/*调测视频时候, 把两者打开*/
#define AZ_POOL_LOW
#define AZ_MAGIC_LOW
#endif

//#define H264STREAM_CORRECT
/*RingBuffer 统计*/
#define RBSTAT

#define BITSTREAM_ENC_CHECKSUM
#define BITSTREAM_DEC_CHECKSUM


#define RTSP_VOD

#define SAVE_VOICE 1


/*支持网路点播*/
#define MPLAYER_NETWORK

#define DEMO_MEDIA

#define DEMO_VOICE
#define DEMO_VIDEO_ENC
#define DEMO_VIDEO_DEC

/*同步机制使用cond, 否则使用sem*/
//#define SYNC_USE_COND

/*ARM写消息池的时候，判断ZSP语音任务消息池是否可写*/
#define AZPOOLS_X

/*HI3510V100 集成测试*/
#define HI3510V100

#if defined(IMAGESIZE_CIF)
#define CONFIG_VIU_CAPTURE_DOWNSCALING //CIF
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_CONFIG_H__ */
