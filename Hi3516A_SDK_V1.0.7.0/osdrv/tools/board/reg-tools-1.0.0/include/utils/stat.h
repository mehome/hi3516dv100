/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : stat.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/12/1
  Last Modified :
  Description   : stat.c header file
  Function List :
  History       :
  1.Date        : 2005/12/1
    Author      : qushen
    Modification: Created file

******************************************************************************/


#ifndef __STAT_H__
#define __STAT_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifdef STAT

typedef struct
{
    time_t StartTime;
    time_t EndTime;
}TimeVal_t;    

typedef enum STAT_ITEM_ENUM
{
    E_VEnc_SendFrames,
    E_VEnc_RecvPackets,
    E_VEnc_RecvEncdata,
    E_VEnc_Rtp_SendPackets,
    E_VEnc_Rtp_SendBytes,

    E_VDec_SendPackets,
    E_VDec_RecvFrames,
    E_VDec_RecvDecdata,
    E_VDec_Rtp_RecvPackets,
    E_VDec_Rtp_RecvBytes,
    E_VDec_Rtp_Discarded,

    E_Voice_SendPackets,
    E_Voice_RecvFrames,
    E_Voice_ResendTimes,
    E_Voice_Rtp_SendPackets,
    E_Voice_Rtp_SendBytes,
    E_Voice_Rtp_RecvPackets,
    E_Voice_Rtp_RecvBytes,
    E_Voice_Rtp_Discarded,

    E_STAT_ITEM_END
}STAT_ITEM_E;

typedef enum STAT_TYPE_ENUM
{
    STAT_AUDIODEC = 1,
    STAT_AUDIOENC = 2,
    STAT_VIDEODEC = 3,
    STAT_VIDEOENC = 4,    
    STAT_VOICE    = 5,
    
    STAT_TYPE_MAX
}STAT_TYPE_E;



extern VOID stat_init();
extern VOID stat_rtp_discarded(STAT_ITEM_E t, U16 seq, U16 prev_seq);
extern VOID stat_calc(STAT_ITEM_E t, U32 value);
extern VOID stat_time_start(STAT_TYPE_E t);
extern VOID stat_print(STAT_TYPE_E t);

extern VOID stat_print_venc(int argc, char* argv[]);
extern VOID stat_print_vdec(int argc, char* argv[]);
extern VOID stat_print_voice(int argc, char* argv[]);

#define STAT_CALC(t, value)    stat_calc(t, value)
#define STAT_INIT()       stat_init()
#define STAT_TIME_STAT(t)     stat_time_start(t)
#define STAT_RTP_DISCARDED(t, seq, prev_seq)  stat_rtp_discarded(t, seq, prev_seq)
#define STAT_PRINT_VENC(argc, argv ) stat_print_venc(argc, argv )
#define STAT_PRINT_VDEC(argc, argv ) stat_print_vdec(argc, argv )
#define STAT_PRINT_VOICE(argc, argv ) stat_print_voice(argc, argv )
#else

#define STAT_CALC(t, value)    
#define STAT_INIT()       
#define STAT_TIME_STAT(t)     
#define STAT_RTP_DISCARDED(t, seq, prev_seq)  
#define STAT_PRINT_VENC(argc, argv ) 
#define STAT_PRINT_VDEC(argc, argv ) 
#define STAT_PRINT_VOICE(argc, argv )

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __STAT_H__ */
