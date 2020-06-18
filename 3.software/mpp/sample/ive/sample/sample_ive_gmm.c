#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <pthread.h>


#include "hi_common.h"
#include "hi_comm_video.h"
#include "hi_comm_sys.h"
#include "hi_comm_ive.h"
#include "hi_comm_vgs.h"
#include "hi_comm_vi.h"
#include "hi_comm_vo.h"

#include "mpi_vb.h"
#include "mpi_sys.h"
#include "mpi_ive.h"
#include "mpi_vgs.h"
#include "mpi_vi.h"
#include "mpi_vo.h"


#include "sample_comm_ive.h"
#include "sample_comm.h"
//#include "sample_comm_venc.h"

typedef struct hiSAMPLE_IVE_GMM_S
{
    IVE_SRC_IMAGE_S stSrc;
    IVE_DST_IMAGE_S stFg;
    IVE_DST_IMAGE_S stBg;
    IVE_MEM_INFO_S  stModel;
    IVE_IMAGE_S	stImg1;
    IVE_IMAGE_S	stImg2;
    IVE_DST_MEM_INFO_S stBlob;
    IVE_GMM_CTRL_S  stGmmCtrl;
    IVE_CCL_CTRL_S  stCclCtrl;
    IVE_FILTER_CTRL_S stFltCtrl;
    IVE_DILATE_CTRL_S stDilateCtrl;
    IVE_ERODE_CTRL_S stErodeCtrl;
    SAMPLE_RECT_ARRAY_S stRegion;
} SAMPLE_IVE_GMM_S;

typedef struct hiSAMPLE_IVE_GMM_INFO_S
{
    SAMPLE_IVE_GMM_S stGmm;
    HI_BOOL bEncode;
    HI_BOOL bVo;
} SAMPLE_IVE_GMM_INFO_S;

static HI_BOOL s_bStopSignal = HI_FALSE;

static HI_VOID SAMPLE_IVE_Gmm_Uninit(SAMPLE_IVE_GMM_S* pstGmm)
{
    IVE_MMZ_FREE(pstGmm->stSrc.u32PhyAddr[0], pstGmm->stSrc.pu8VirAddr[0]);
    IVE_MMZ_FREE(pstGmm->stFg.u32PhyAddr[0], pstGmm->stFg.pu8VirAddr[0]);
    IVE_MMZ_FREE(pstGmm->stBg.u32PhyAddr[0], pstGmm->stBg.pu8VirAddr[0]);
    IVE_MMZ_FREE(pstGmm->stModel.u32PhyAddr, pstGmm->stModel.pu8VirAddr);
    IVE_MMZ_FREE(pstGmm->stImg1.u32PhyAddr[0], pstGmm->stImg1.pu8VirAddr[0]);
    IVE_MMZ_FREE(pstGmm->stImg2.u32PhyAddr[0], pstGmm->stImg2.pu8VirAddr[0]);
    IVE_MMZ_FREE(pstGmm->stBlob.u32PhyAddr, pstGmm->stBlob.pu8VirAddr);
}


static HI_S32 SAMPLE_IVE_Gmm_Init(SAMPLE_IVE_GMM_S* pstGmm, HI_U16 u16Width, HI_U16 u16Height)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Size = 0;
    HI_S8 as8Mask[25] = {1, 2, 3, 2, 1,
                         2, 5, 6, 5, 2,
                         3, 6, 8, 6, 3,
                         2, 5, 6, 5, 2,
                         1, 2, 3, 2, 1
                        };

    memset(pstGmm, 0, sizeof(SAMPLE_IVE_GMM_S));

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstGmm->stSrc), IVE_IMAGE_TYPE_U8C1, u16Width, u16Height);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateImage fail\n");
        goto GMM_INIT_FAIL;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstGmm->stFg), IVE_IMAGE_TYPE_U8C1, u16Width, u16Height);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateImage fail\n");
        goto GMM_INIT_FAIL;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstGmm->stBg), IVE_IMAGE_TYPE_U8C1, u16Width, u16Height);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateImage fail\n");
        goto GMM_INIT_FAIL;
    }

    pstGmm->stGmmCtrl.u0q16InitWeight = 3276; //0.05
    pstGmm->stGmmCtrl.u0q16BgRatio = 52428;   //0.8
    pstGmm->stGmmCtrl.u22q10MaxVar = (2000 << 10);
    pstGmm->stGmmCtrl.u22q10MinVar = (200 << 10);
    pstGmm->stGmmCtrl.u22q10NoiseVar = (225 << 10);
    pstGmm->stGmmCtrl.u8q8VarThr = 1600;
    pstGmm->stGmmCtrl.u8ModelNum = 3;
    pstGmm->stGmmCtrl.u0q16LearnRate = 327;

    u32Size = pstGmm->stSrc.u16Width * pstGmm->stSrc.u16Height * pstGmm->stGmmCtrl.u8ModelNum * 7;
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&pstGmm->stModel, u32Size);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateMemInfo fail\n");
        goto GMM_INIT_FAIL;
    }
    memset(pstGmm->stModel.pu8VirAddr, 0, pstGmm->stModel.u32Size);

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstGmm->stImg1), IVE_IMAGE_TYPE_U8C1, u16Width, u16Height);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateImage fail\n");
        goto GMM_INIT_FAIL;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstGmm->stImg2), IVE_IMAGE_TYPE_U8C1, u16Width, u16Height);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateImage fail\n");
        goto GMM_INIT_FAIL;
    }

    u32Size = sizeof(IVE_CCBLOB_S);
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&pstGmm->stBlob, u32Size);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateMemInfo fail\n");
        goto GMM_INIT_FAIL;
    }

    memcpy(pstGmm->stFltCtrl.as8Mask, as8Mask, 25);
    pstGmm->stFltCtrl.u8Norm = 7;
    memset(pstGmm->stDilateCtrl.au8Mask, 255, 25);
    memset(pstGmm->stErodeCtrl.au8Mask, 255, 25);
    pstGmm->stCclCtrl.u16InitAreaThr = 16;
    pstGmm->stCclCtrl.u16Step = 4;

GMM_INIT_FAIL:

    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_IVE_Gmm_Uninit(pstGmm);
    }
    return s32Ret;
}

static HI_S32 SAMPLE_IVE_GmmProc(SAMPLE_IVE_GMM_INFO_S* pstGmmInfo, VIDEO_FRAME_INFO_S* pstExtFrameInfo)
{
    HI_S32 s32Ret;
    SAMPLE_IVE_GMM_S* pstGmm;
    IVE_DATA_S stSrc;
    IVE_DATA_S stDst;
    IVE_HANDLE IveHandle;
    HI_BOOL bFinish = HI_FALSE;
    HI_BOOL bBlock = HI_TRUE;
    HI_BOOL bInstant = HI_TRUE;
    IVE_CCBLOB_S* pstBlob;
    IVE_DMA_CTRL_S stDmaCtrl = {IVE_DMA_MODE_DIRECT_COPY, 0};

    pstGmm = &pstGmmInfo->stGmm;
    pstBlob = (IVE_CCBLOB_S*)pstGmm->stBlob.pu8VirAddr;

    //1.Get Y
    stSrc.pu8VirAddr = (HI_U8*)pstExtFrameInfo->stVFrame.pVirAddr[0];
    stSrc.u32PhyAddr = pstExtFrameInfo->stVFrame.u32PhyAddr[0];
    stSrc.u16Stride = (HI_U16)pstExtFrameInfo->stVFrame.u32Stride[0];
    stSrc.u16Width = (HI_U16)pstExtFrameInfo->stVFrame.u32Width;
    stSrc.u16Height = pstExtFrameInfo->stVFrame.u32Height;

    stDst.pu8VirAddr = pstGmm->stSrc.pu8VirAddr[0];
    stDst.u32PhyAddr = pstGmm->stSrc.u32PhyAddr[0];
    stDst.u16Stride 	= pstGmm->stSrc.u16Stride[0];
    stDst.u16Width 	= pstGmm->stSrc.u16Width;
    stDst.u16Height 	= pstGmm->stSrc.u16Height;
    bInstant = HI_FALSE;
    stDmaCtrl.enMode = IVE_DMA_MODE_DIRECT_COPY;
    s32Ret = HI_MPI_IVE_DMA(&IveHandle, &stSrc, &stDst, &stDmaCtrl, bInstant);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("HI_MPI_IVE_DMA fail,Error(%#x)\n", s32Ret);
        return s32Ret;
    }
    //2.Filter
    s32Ret = HI_MPI_IVE_Filter(&IveHandle, &pstGmm->stSrc, &pstGmm->stImg1, &pstGmm->stFltCtrl, bInstant);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("HI_MPI_IVE_Filter fail,Error(%#x)\n", s32Ret);
        return s32Ret;
    }
    //3.Gmm
    s32Ret = HI_MPI_IVE_GMM(&IveHandle, &pstGmm->stImg1, &pstGmm->stFg, &pstGmm->stBg, &pstGmm->stModel, &pstGmm->stGmmCtrl, bInstant);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("HI_MPI_IVE_GMM fail,Error(%#x)\n", s32Ret);
        return s32Ret;
    }
    //4.Dilate
    s32Ret = HI_MPI_IVE_Dilate(&IveHandle, &pstGmm->stFg, &pstGmm->stImg1, &pstGmm->stDilateCtrl, bInstant);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("HI_MPI_IVE_Dilate fail,Error(%#x)\n", s32Ret);
        return s32Ret;
    }
    //5.Erode
    s32Ret = HI_MPI_IVE_Erode(&IveHandle, &pstGmm->stImg1, &pstGmm->stImg2, &pstGmm->stErodeCtrl, bInstant);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("HI_MPI_IVE_Erode fail,Error(%#x)\n", s32Ret);
        return s32Ret;
    }
    //6.CCL
    bInstant = HI_TRUE;
    s32Ret = HI_MPI_IVE_CCL(&IveHandle, &pstGmm->stImg2, &pstGmm->stBlob, &pstGmm->stCclCtrl, bInstant);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("HI_MPI_IVE_CCL fail,Error(%#x)\n", s32Ret);
        return s32Ret;
    }
    //Wait task finish
    s32Ret = HI_MPI_IVE_Query(IveHandle, &bFinish, bBlock);
    while (HI_ERR_IVE_QUERY_TIMEOUT == s32Ret)
    {
        usleep(100);
        s32Ret = HI_MPI_IVE_Query(IveHandle, &bFinish, bBlock);
    }
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("HI_MPI_IVE_Query fail,Error(%#x)\n", s32Ret);
        return s32Ret;
    }

    SAMPLE_COMM_IVE_BlobToRect(pstBlob, &(pstGmm->stRegion), 50, 8, 1280, 720);

    return HI_SUCCESS;
}


static HI_VOID* SAMPLE_IVE_ViToVo(HI_VOID* pArgs)
{
    HI_S32 s32Ret;
    SAMPLE_IVE_GMM_INFO_S* pstGmmInfo;
    SAMPLE_IVE_GMM_S* pstGmm;
    VIDEO_FRAME_INFO_S stFrameInfo;
    VIDEO_FRAME_INFO_S stExtFrameInfo;
    HI_S32 s32GetFrameMilliSec = 20000;
    HI_S32 s32SetFrameMilliSec = 20000;
    VO_LAYER voLayer = 0;
    VI_CHN viChn = 0;
    VI_CHN viExtChn = 1;
    VO_CHN voChn = 0;
    VENC_CHN vencChn = 0;
    HI_BOOL bEncode;
    HI_BOOL bVo;

    pstGmmInfo = (SAMPLE_IVE_GMM_INFO_S*)pArgs;
    pstGmm = &(pstGmmInfo->stGmm);
    bEncode = pstGmmInfo->bEncode;
    bVo = pstGmmInfo->bVo;

    while (HI_FALSE == s_bStopSignal)
    {

        s32Ret = HI_MPI_VI_GetFrame(viExtChn, &stExtFrameInfo, s32GetFrameMilliSec);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("HI_MPI_VI_GetFrame fail,ViChn(%d),Error(%#x)\n", viExtChn, s32Ret);
            continue;
        }
        s32Ret = SAMPLE_IVE_GmmProc(pstGmmInfo, &stExtFrameInfo);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("SAMPLE_IVE_MdProc fail,Error(%#x)\n", s32Ret);
        }
        s32Ret = HI_MPI_VI_ReleaseFrame(viExtChn, &stExtFrameInfo);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("HI_MPI_VI_ReleaseFrame fail,ViChn(%d),Error(%#x)\n", viExtChn, s32Ret);
        }

        s32Ret = HI_MPI_VI_GetFrame(viChn, &stFrameInfo, s32GetFrameMilliSec);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("HI_MPI_VI_GetFrame fail,ViChn(%d),Error(%#x)\n", viChn, s32Ret);
            continue;
        }
        //Draw rect
        s32Ret = SAMPLE_COMM_VGS_FillRect(&stFrameInfo, &pstGmm->stRegion, 0x0000FF00);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("SAMPLE_COMM_VGS_FillRect fail,Error(%#x)\n", s32Ret);
            (HI_VOID)HI_MPI_VI_ReleaseFrame(viChn, &stFrameInfo);
            continue;
        }
        //Venc
        if (HI_TRUE == bEncode)
        {
            s32Ret = HI_MPI_VENC_SendFrame(vencChn, &stFrameInfo, s32SetFrameMilliSec);
            if (HI_SUCCESS != s32Ret)
            {
                SAMPLE_PRT("HI_MPI_VENC_SendFrame fail,Error(%#x)\n", s32Ret);
            }
        }

        //Vo
        if (HI_TRUE == bVo)
        {
            s32Ret = HI_MPI_VO_SendFrame(voLayer, voChn, &stFrameInfo, s32SetFrameMilliSec);
            if (HI_SUCCESS != s32Ret)
            {
                SAMPLE_PRT("HI_MPI_VO_SendFrame fail,Error(%#x)\n", s32Ret);
            }
        }

        //Release frame
        s32Ret = HI_MPI_VI_ReleaseFrame(viChn, &stFrameInfo);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("HI_MPI_VI_ReleaseFrame fail,ViChn(%d),Error(%#x)\n", viChn, s32Ret);
        }
    }
    return HI_NULL;
}


/******************************************************************************
* function : show Gmm sample
******************************************************************************/
HI_VOID SAMPLE_IVE_Gmm(HI_CHAR chEncode, HI_CHAR chVo)
{

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U16 u16Width = VIDEO_WIDTH;
    HI_U16 u16Height = VIDEO_HEIGHT;
    SAMPLE_IVE_GMM_INFO_S stGmmInfo;
    SAMPLE_IVE_VI_VO_CONFIG_S stViVoConfig;
    pthread_t hIveThread;

    SAMPLE_COMM_IVE_CheckIveMpiInit();

    s_bStopSignal = HI_FALSE;
    stViVoConfig.enPicSize = PIC_HD720;
    stViVoConfig.enNorm =	VIDEO_ENCODING_MODE_PAL;
    stViVoConfig.enVoIntfType = VO_INTF_BT1120;
    stViVoConfig.stViConfig.enViMode = SAMPLE_VI_MODE_BT1120_720P;
    stViVoConfig.stViConfig.enNorm = VIDEO_ENCODING_MODE_PAL;
    stViVoConfig.stViConfig.enRotate = ROTATE_NONE;
    stViVoConfig.stViConfig.enViChnSet = VI_CHN_SET_NORMAL;
    stViVoConfig.stViConfig.enWDRMode = WDR_MODE_NONE;
    s32Ret = SAMPLE_IVE_Gmm_Init(&stGmmInfo.stGmm, u16Width, u16Height);;
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("Md init fail\n");
        goto GMM_END_0;
    }


    stGmmInfo.bEncode = '1' == chEncode ? HI_TRUE : HI_FALSE;
    stGmmInfo.bVo = '1' == chVo ? HI_TRUE : HI_FALSE;

    s32Ret = SAMPLE_COMM_IVE_BT1120_720P_PreView(&stViVoConfig, HI_TRUE, stGmmInfo.bVo, stGmmInfo.bEncode);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_BT1120_720P_PreView fail\n");
        goto GMM_END_1;
    }

    //Start vi to vo thread
    pthread_create(&hIveThread, 0, SAMPLE_IVE_ViToVo, (HI_VOID*)&stGmmInfo);

    SAMPLE_VI_PAUSE();

    s_bStopSignal = HI_TRUE;
    pthread_join(hIveThread, HI_NULL);
    SAMPLE_COMM_IVE_BT1120_720P_Stop(&stViVoConfig, HI_TRUE, stGmmInfo.bVo, stGmmInfo.bEncode);
GMM_END_1:
    SAMPLE_IVE_Gmm_Uninit(&stGmmInfo.stGmm);
GMM_END_0:
    SAMPLE_COMM_IVE_IveMpiExit();
}


