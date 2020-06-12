/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : isp_af.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/01/05
  Description   : 
  History       :
  1.Date        : 2013/01/05
    Author      : n00168968
    Modification: Created file

******************************************************************************/

#include <stdio.h>
#include "isp_alg.h"
#include "isp_ext_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

HI_S32 ISP_AfCtrl(ISP_DEV IspDev, HI_U32 u32Cmd, HI_VOID *pValue);
HI_S32 ISP_AfInit(ISP_DEV IspDev)
{
    HI_S32 i;
    ISP_AF_PARAM_S stAfParam;
    ISP_CTX_S *pstIspCtx = HI_NULL;
    ISP_LIB_NODE_S *pstLib = HI_NULL;
    
    ISP_GET_CTX(IspDev, pstIspCtx);
    
    stAfParam.SensorId = pstIspCtx->stBindAttr.SensorId;
    for (i=0; i<MAX_REGISTER_ALG_LIB_NUM; i++)
    {
        if (pstIspCtx->stAfLibInfo.astLibs[i].bUsed)
        {
            pstLib = &pstIspCtx->stAfLibInfo.astLibs[i];
            if (HI_NULL != pstLib->stAfRegsiter.stAfExpFunc.pfn_af_init)
            {
                pstLib->stAfRegsiter.stAfExpFunc.pfn_af_init(
                    pstLib->stAlgLib.s32Id, &stAfParam);
            }
        }
    }
    
    return HI_SUCCESS;
}

HI_S32 ISP_AfRun(ISP_DEV IspDev, const HI_VOID *pStatInfo,
    HI_VOID *pRegCfg, HI_S32 s32Rsv)
{
    HI_S32 s32Ret = HI_FAILURE;
    ISP_AF_INFO_S       stAfInfo = {0};
    ISP_AF_RESULT_S     stAfResult = {0};
    ISP_CTX_S          *pstIspCtx   = HI_NULL;
    ISP_LIB_NODE_S     *pstLib      = HI_NULL;
    
    ISP_GET_CTX(IspDev, pstIspCtx);
    pstLib = &pstIspCtx->stAfLibInfo.astLibs[pstIspCtx->stAfLibInfo.u32ActiveLib];

    if (pstIspCtx->stLinkage.bDefectPixel)
    {
        return HI_SUCCESS;
    }

    stAfInfo.u32FrameCnt = pstIspCtx->u32FrameCnt;

    stAfInfo.stAfStat = &((ISP_STAT_S *)pStatInfo)->stAfStat;
    
    if (HI_NULL != pstLib->stAfRegsiter.stAfExpFunc.pfn_af_run)
    {
        s32Ret = pstLib->stAfRegsiter.stAfExpFunc.pfn_af_run(
            pstLib->stAlgLib.s32Id, &stAfInfo, &stAfResult, 0);
        if (HI_SUCCESS != s32Ret)
        {
            printf("WARNING!! run af lib err 0x%x!\n", s32Ret);
        }
    }

    return s32Ret;
}

HI_S32 ISP_AfCtrl(ISP_DEV IspDev, HI_U32 u32Cmd, HI_VOID *pValue)
{    
    HI_S32  i, s32Ret = HI_FAILURE;
    ISP_CTX_S *pstIspCtx = HI_NULL;
    ISP_LIB_NODE_S *pstLib = HI_NULL;
    
    ISP_GET_CTX(IspDev, pstIspCtx);

    for (i=0; i<MAX_REGISTER_ALG_LIB_NUM; i++)
    {
        if (pstIspCtx->stAfLibInfo.astLibs[i].bUsed)
        {
            pstLib = &pstIspCtx->stAfLibInfo.astLibs[i];
            if (HI_NULL != pstLib->stAfRegsiter.stAfExpFunc.pfn_af_ctrl)
            {
                s32Ret = pstLib->stAfRegsiter.stAfExpFunc.pfn_af_ctrl(
                    pstLib->stAlgLib.s32Id, u32Cmd, pValue);
            }
        }
    }

    return s32Ret;
}

HI_S32 ISP_AfExit(ISP_DEV IspDev)
{
    HI_S32 i;
    ISP_CTX_S *pstIspCtx = HI_NULL;
    ISP_LIB_NODE_S *pstLib = HI_NULL;
    
    ISP_GET_CTX(IspDev, pstIspCtx);

    for (i=0; i<MAX_REGISTER_ALG_LIB_NUM; i++)
    {
        if (pstIspCtx->stAfLibInfo.astLibs[i].bUsed)
        {
            pstLib = &pstIspCtx->stAfLibInfo.astLibs[i];
            if (HI_NULL != pstLib->stAfRegsiter.stAfExpFunc.pfn_af_exit)
            {
                pstLib->stAfRegsiter.stAfExpFunc.pfn_af_exit(
                    pstLib->stAlgLib.s32Id);
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32 ISP_AlgRegisterAf(ISP_DEV IspDev)
{
    ISP_CTX_S *pstIspCtx = HI_NULL;
    ISP_ALG_NODE_S *pstAlgs = HI_NULL;
    
    ISP_GET_CTX(IspDev, pstIspCtx);

    pstAlgs = ISP_SearchAlg(pstIspCtx->astAlgs);
    ISP_CHECK_POINTER(pstAlgs);

    pstAlgs->enAlgType = ISP_ALG_AF;
    pstAlgs->stAlgFunc.pfn_alg_init = ISP_AfInit;
    pstAlgs->stAlgFunc.pfn_alg_run  = ISP_AfRun;
    pstAlgs->stAlgFunc.pfn_alg_ctrl = ISP_AfCtrl;
    pstAlgs->stAlgFunc.pfn_alg_exit = ISP_AfExit;
    pstAlgs->bUsed = HI_TRUE;

    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

