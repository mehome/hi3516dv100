/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_error.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/4/23
  Last Modified :
  Description   : 错误代码的定义
  Function List :
  History       :
  1.Date        : 2005/4/20
    Author      : T41030
    Modification: Created file

******************************************************************************/

#ifndef __HI_ERROR_H__
#define __HI_ERROR_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*
    系统错误码的定义
     31       24 23      16 15                   0
    -----------------------------------------------
    |    模块   |  子模块  |   错误码(子模块定义) |
    -----------------------------------------------
*/


#define ERR_SUB_MODULE_BASE(module, submodule)    \
                (( module << 24 ) | ( submodule << 16 )) 
                
#define ERR_NUMBER(err, base)          ( (base) | (err) ) 


/*****************************************************************************
通用模块错误代码定义
****************************************************************************/

/*0x00XX*/
#define ERR_GENERAL_BASE      ERR_SUB_MODULE_BASE(MODULE_GENERAL, 0)

#define ERR_GEN_NOT_ENOUGH_MEMORY ERR_NUMBER(2, ERR_GENERAL_BASE) /*0x0002*/
#define ERR_GEN_INVALID_POINTER   ERR_NUMBER(3, ERR_GENERAL_BASE) /*0x0003*/
#define ERR_GEN_OVERFLOW          ERR_NUMBER(4, ERR_GENERAL_BASE) /*0x0004*/
#define ERR_GEN_OUT_OF_BOUND      ERR_NUMBER(5, ERR_GENERAL_BASE) /*0x0004*/
#define ERR_GEN_INVALID_FP        ERR_NUMBER(6, ERR_GENERAL_BASE) /*0x0004*/

#define ERR_GEN_TIMEOUT           ERR_NUMBER(7, ERR_GENERAL_BASE) /*0x0007*/
#define ERR_GEN_INVALID_PARAMETER ERR_NUMBER(8, ERR_GENERAL_BASE) /*0x0008*/

/*****************************************************************************
驱动模块, 子模块错误代码定义
****************************************************************************/
#define ERR_DRV_VIU_BASE    ERR_SUB_MODULE_BASE(MODULE_DRV,  DRV_SUB_MODULE_VIU)
#define ERR_DRV_VOU_BASE    ERR_SUB_MODULE_BASE(MODULE_DRV,  DRV_SUB_MODULE_VOU)
#define ERR_DRV_DSU_BASE    ERR_SUB_MODULE_BASE(MODULE_DRV,  DRV_SUB_MODULE_DSU)
#define ERR_DRV_USB_BASE    ERR_SUB_MODULE_BASE(MODULE_DRV,  DRV_SUB_MODULE_USB)
#define ERR_DRV_SF_BASE     ERR_SUB_MODULE_BASE(MODULE_DRV,  DRV_SUB_MODULE_SF)
#define ERR_DRV_TDE_BASE    ERR_SUB_MODULE_BASE(MODULE_DRV,  DRV_SUB_MODULE_TDE)

/* ERR_DRV_VOU_BASE */
#define ERR_DRV_VOU_ERROR         ERR_NUMBER(0, ERR_DRV_VOU_BASE)
#define ERR_DRV_VOU_NOT_INITED    ERR_NUMBER(1, ERR_DRV_VOU_BASE)
#define ERR_DRV_VOU_INIT_FAILED   ERR_NUMBER(2, ERR_DRV_VOU_BASE)
#define ERR_DRV_VOU_OUTPUT_MODE_NOT_SUPPORT  ERR_NUMBER(3, ERR_DRV_VOU_BASE)
#define ERR_DRV_VOU_LAYER_INVALID ERR_NUMBER(4, ERR_DRV_VOU_BASE)

/* ERR_DRV_VIU_BASE */
#define ERR_DRV_VIU_ERROR        ERR_NUMBER(0, ERR_DRV_VIU_BASE)
#define ERR_DRV_VIU_NOT_INITED   ERR_NUMBER(1, ERR_DRV_VIU_BASE)
#define ERR_DRV_VIU_INIT_FAILED  ERR_NUMBER(2, ERR_DRV_VIU_BASE)
#define ERR_DRV_VIU_MODE_NOT_SUPPORT   ERR_NUMBER(3, ERR_DRV_VIU_BASE)

/* ERR_DRV_DSU_BASE */
#define ERR_DRV_DSU_ERROR        ERR_NUMBER(0, ERR_DRV_DSU_BASE)
#define ERR_DRV_DSU_NOT_INITED   ERR_NUMBER(1, ERR_DRV_DSU_BASE)
#define ERR_DRV_DSU_INIT_FAILED  ERR_NUMBER(2, ERR_DRV_DSU_BASE)
#define ERR_DRV_DSU_FILTER_NOT_SUPPORT   ERR_NUMBER(3, ERR_DRV_DSU_BASE)

/* ERR_DRV_TDE_BASE */
#define ERR_DRV_TDE_ERROR        ERR_NUMBER(0, ERR_DRV_TDE_BASE)
#define ERR_DRV_TDE_NOT_INITED   ERR_NUMBER(1, ERR_DRV_TDE_BASE)
#define ERR_DRV_TDE_INIT_FAILED  ERR_NUMBER(2, ERR_DRV_TDE_BASE)
#define ERR_DRV_TDE_FIFO_TIMEOUT ERR_NUMBER(3, ERR_DRV_TDE_BASE)




/*
Add By You , man
......
.....
*/

/*****************************************************************************
系统模块,ARM ZSP 通讯子模块错误代码定义
****************************************************************************/
/*00000001-00000001-xxxxxxxx-xxxxxxxx  0x11XX*/
#define ERR_SYS_AZ_BASE ERR_SUB_MODULE_BASE(MODULE_SYS, SYS_SUB_MODULE_AZ)


#define ERR_AZMSG_INVALID_MSGPOOLS  ERR_NUMBER(1, ERR_SYS_AZ_BASE) /*0x1101*/
#define ERR_AZMSG_INVALID_MSG      ERR_NUMBER(2, ERR_SYS_AZ_BASE) /*0x1102*/
#define ERR_AZMSG_NO_SPACE_TOSEND  ERR_NUMBER(3, ERR_SYS_AZ_BASE) /*0x1103*/
#define ERR_AZMSG_NO_MSG_TORECV    ERR_NUMBER(4, ERR_SYS_AZ_BASE)
#define ERR_AZMSG_INVALID_MSGDATA  ERR_NUMBER(5, ERR_SYS_AZ_BASE) /*0x1105*/

#define ERR_AZMSG_OVERFLOW         ERR_NUMBER(6, ERR_SYS_AZ_BASE) /*0x1106*/
#define ERR_AZMSG_EMPTY            ERR_NUMBER(7, ERR_SYS_AZ_BASE) /*0x1107*/
#define ERR_AZMSG_READY_TIMEOUT    ERR_NUMBER(8, ERR_SYS_AZ_BASE) /*0x1108*/
#define ERR_AZMSG_POOL_OFFREAD     ERR_NUMBER(9, ERR_SYS_AZ_BASE) /*0x1109*/
#define ERR_AZMSG_POOL_OFFWRITE    ERR_NUMBER(10, ERR_SYS_AZ_BASE) /*0x1110*/

#define ERR_AZMSG_MSG_MAGIC        ERR_NUMBER(11, ERR_SYS_AZ_BASE) /*0x1111*/
#define ERR_AZMSG_MSG_LENGTH       ERR_NUMBER(12, ERR_SYS_AZ_BASE) /*0x1112*/
#define ERR_AZMSG_MSG_PID          ERR_NUMBER(13, ERR_SYS_AZ_BASE) /*0x1113*/
/*Ring Buffer*/
/*00000001-00000002-xxxxxxxx-xxxxxxxx  0x12XX*/
#define ERR_SYS_RB_BASE ERR_SUB_MODULE_BASE(MODULE_SYS, SYS_SUB_MODULE_RB)

#define ERR_RB_ERROR               ERR_NUMBER(0, ERR_SYS_RB_BASE) /*0x1201*/
#define ERR_RB_INIT                ERR_NUMBER(1, ERR_SYS_RB_BASE) /*0x1201*/
#define ERR_RB_OVERFLOW            ERR_NUMBER(2, ERR_SYS_RB_BASE) /*0x1202*/
#define ERR_RB_READ_NOTENOGH       ERR_NUMBER(3, ERR_SYS_RB_BASE) /*0x1203*/
#define ERR_RB_WRITE_NOTENOGH      ERR_NUMBER(4, ERR_SYS_RB_BASE) /*0x1204*/
#define ERR_RB_NULL_BUF            ERR_NUMBER(5, ERR_SYS_RB_BASE) /*0x1205*/
#define ERR_RB_DAMAGE              ERR_NUMBER(6, ERR_SYS_RB_BASE) /*0x1206*/

/*Buffer Manager*/
/*00000001-00000003-xxxxxxxx-xxxxxxxx  0x13XX*/
#define ERR_SYS_BM_BASE ERR_SUB_MODULE_BASE(MODULE_SYS, SYS_SUB_MODULE_BM)

#define ERR_BM_ERROR               ERR_NUMBER(0, ERR_SYS_BM_BASE) /*0x1301*/
#define ERR_BM_INIT                ERR_NUMBER(1, ERR_SYS_BM_BASE) /*0x1301*/
#define ERR_BM_OVERFLOW            ERR_NUMBER(2, ERR_SYS_BM_BASE) /*0x1302*/
#define ERR_BM_READ_NOTENOGH       ERR_NUMBER(3, ERR_SYS_BM_BASE) /*0x1303*/
#define ERR_BM_WRITE_NOTENOGH      ERR_NUMBER(4, ERR_SYS_BM_BASE) /*0x1304*/
#define ERR_BM_INVALIDLEN          ERR_NUMBER(5, ERR_SYS_BM_BASE) /*0x1304*/

/*Message Queue*/
/*00000001-00000004-xxxxxxxx-xxxxxxxx  0x14XX*/
#define ERR_SYS_MQ_BASE ERR_SUB_MODULE_BASE(MODULE_SYS, SYS_SUB_MODULE_MQ)
/*Message Queue's Normal Error*/
#define ERR_MQ_ERROR           ERR_NUMBER(0, ERR_SYS_MQ_BASE)
/*the Queue is invalid*/
#define ERR_MQ_QUEUE_INVALUD   ERR_NUMBER(1, ERR_SYS_MQ_BASE)
/*no enough space to write to queue*/
#define ERR_MQ_QUEUE_OVERFLOW  ERR_NUMBER(2, ERR_SYS_MQ_BASE)
/*the queue is empty to read */
#define ERR_MQ_QUEUE_EMPTY     ERR_NUMBER(3, ERR_SYS_MQ_BASE)
/*the message is invalid*/
#define ERR_MQ_MSG_INVALID     ERR_NUMBER(4, ERR_SYS_MQ_BASE)
/*the message length is null*/
#define ERR_MQ_MSG_LEN_INVALID ERR_NUMBER(5, ERR_SYS_MQ_BASE)
/*the buffer is invalid*/
#define ERR_MQ_BUFFER_INVALID  ERR_NUMBER(6, ERR_SYS_MQ_BASE)

/*thread manager*/
#define ERR_SYS_THREAD_BASE ERR_SUB_MODULE_BASE(MODULE_SYS, SYS_SUB_MODULE_THREAD)

#define ERR_SYS_THREAD_MUTEX_ERROR     ERR_NUMBER(0, ERR_SYS_THREAD_BASE)

/*------------- MMF Module Error Number Define  ---------------0x31xx----------*/
#define ERR_MMF_INPUT_BASE \
                ERR_SUB_MODULE_BASE(MODULE_MMF, MMF_SUB_MODULE_INPUT)

#define ERR_INPUT_STREAM_ERROR \
                ERR_NUMBER(1, ERR_MMF_INPUT_BASE) /*0x3102*/
#define ERR_INPUT_STREAM_NOTSUPPORT \
                ERR_NUMBER(2, ERR_MMF_INPUT_BASE) /*0x3102*/
#define ERR_INPUT_FILE_OPEN_ERROR  \
                ERR_NUMBER(3, ERR_MMF_INPUT_BASE) /*0x3102*/
                
/*------------- DEMUX Module Error Number Define  ---------------0x35xx--------*/
#define ERR_MMF_DEMUX_BASE \
                ERR_SUB_MODULE_BASE(MODULE_MMF, MMF_SUB_MODULE_DEMUX)

#define ERR_DEMUX_STREAM_END \
                ERR_NUMBER(1, ERR_MMF_DEMUX_BASE) 
#define ERR_DEMUX_STREAM_SEEK_FAILED \
                ERR_NUMBER(2, ERR_MMF_DEMUX_BASE) 
#define ERR_DEMUX_STREAM_SEEK_NOSUPPORT  \
                ERR_NUMBER(3, ERR_MMF_DEMUX_BASE) 
#define ERR_DEMUX_NO_DEMUX_INFO  \
                ERR_NUMBER(4, ERR_MMF_DEMUX_BASE)                 



#define ERR_MMF_STREAM_BASE \
                ERR_SUB_MODULE_BASE(MODULE_MMF, MMF_SUB_MODULE_STREAM)
                
#define ERR_STREAM_EMPTY    \
                ERR_NUMBER(1, MMF_SUB_MODULE_STREAM) /*0x3601*/

/*************** video decode error code define *******************/
#define ERR_MMF_VDEC_BASE \
                ERR_SUB_MODULE_BASE(MODULE_MMF, MMF_SUB_MODULE_VDEC)

#define ERR_MMF_VDEC_ERROR \
                ERR_NUMBER(0, ERR_MMF_VDEC_BASE)    /*0x3701*/

#define ERR_MMF_VDEC_HANDLE_INVALID \
                ERR_NUMBER(1, ERR_MMF_VDEC_BASE)

#define ERR_MMF_VDEC_DATA_INVALID \
                ERR_NUMBER(2, ERR_MMF_VDEC_BASE)

#define ERR_MMF_VDEC_DATATYPE_INVALID \
                ERR_NUMBER(3, ERR_MMF_VDEC_BASE)

#define ERR_MMF_VDEC_PAYTYPE_INVALID \
                ERR_NUMBER(4, ERR_MMF_VDEC_BASE)    

#define ERR_MMF_VDEC_FIRST_NALU_INVALID \
                ERR_NUMBER(5, ERR_MMF_VDEC_BASE)

/*************** jitter buffer error code define *******************/
#define ERR_MMF_JB_BASE \
                ERR_SUB_MODULE_BASE(MODULE_MMF, MMF_SUB_MODULE_JB)
/* #define ERR_MMF_JB_... */
/* 由于jitterbuffer中定义的错误代码较多，暂时先放在hi_jb_errorcode.h中 */


/*****************************************************************************
APP模块, 子模块错误代码定义
****************************************************************************/
#define ERR_APP_VPAI_BASE ERR_SUB_MODULE_BASE(MODULE_APP,  APP_SUB_MODULE_VAPI)

/* ERR_APP_VPAI_BASE */
#define ERR_APP_VAPI_ERROR         ERR_NUMBER(0, ERR_APP_VPAI_BASE)
#define ERR_APP_VAPI_NOT_INITED    ERR_NUMBER(1, ERR_APP_VPAI_BASE)
#define ERR_APP_VAPI_INIT_FAILED   ERR_NUMBER(2, ERR_APP_VPAI_BASE)





#define STRFMT_ERRCODE "%#010lX"

#ifdef DEBUG

#define HI_ERRNO(err)   \
    do{                 \
        (err)           \
         ? WRITE_LOG_DEBUG("<ERROR>%s:"STRFMT_ERRCODE"\n", #err, err ) \
         : (void)0 ;    \
         return (err);  \
    }while(0) 

#else
#define HI_ERRNO(err) return (err)
#endif

#ifdef DEBUG
#define EXIT(msg, errno) \
    WRITE_LOG_ERROR("%s exit:"STRFMT_ERRCODE".{%s:%d}\n", msg, errno,__FILE__, __LINE__); \
    printf("[END]\n"); \
    exit(errno)
    
#else
#define EXIT(msg, errno) \
	printf("[END]\n"); \
	(exit(errno))
#endif
#define HI_RETCHECK(err) \
    do{\
        (err) \
         ? WRITE_LOG_DEBUG("<ERROR>%s:"STRFMT_ERRCODE"\n", #err, err ) \
         : (void)0 ; \
        exit(err);\
    }while(0)    

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_ERROR_H__ */
