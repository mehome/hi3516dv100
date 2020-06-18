#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


#include "hi_common.h"
#include "hi_comm_video.h"
#include "hi_comm_sys.h"
#include "hi_comm_ive.h"

#include "mpi_vb.h"
#include "mpi_sys.h"
#include "mpi_ive.h"

#include "sample_comm_ive.h"

#define HI_CLIP(a, maxv, minv)		 (((a)>(maxv)) ? (maxv) : (((a) < (minv)) ? (minv) : (a)))

typedef struct hiSAMPLE_IVE_ANN_INFO_S
{
    IVE_MEM_INFO_S stSrc;
    IVE_MEM_INFO_S stDst;
    IVE_IMAGE_S stGray;
    IVE_LOOK_UP_TABLE_S stTable;
    IVE_ANN_MLP_MODEL_S stAnnModel;

} SAMPLE_IVE_ANN_INFO_S;

static HI_S32 SAMPLE_IVE_Round(HI_FLOAT fValue)
{
    if (fValue >= 0)
    {
        return (HI_S32)(fValue + 0.5);
    }
    else
    {
        return (HI_S32)(fValue - 0.5);
    }
}
/******************************************************************************
* function : Ann  mlp create table
******************************************************************************/
static HI_S32 SAMPLE_IVE_Ann_Mlp_CreateTable(IVE_LOOK_UP_TABLE_S* pstTable, HI_FLOAT fAlpha, HI_FLOAT fBeta)
{
    HI_U32 i;
    HI_S1Q15* ps1q15Tmp;
    HI_FLOAT  fExpIn;
    HI_DOUBLE dExpOut;
    //Check table size
    if (pstTable->stTable.u32Size < pstTable->u16ElemNum * sizeof(HI_S1Q15))
    {
        SAMPLE_PRT("Invalid table size\n");
        return HI_FAILURE;
    }

    ps1q15Tmp = (HI_S1Q15*)pstTable->stTable.pu8VirAddr;
    for (i = 0; i < pstTable->u16ElemNum; i++)
    {
        fExpIn  = (HI_FLOAT)i / (1 << pstTable->u8TabInPreci);
        dExpOut = (2 / (1 + exp(-fAlpha * fExpIn)) - 1) * fBeta * (1 << 15) / (1 << pstTable->u8TabOutNorm);
        ps1q15Tmp[i] = (HI_CLIP(SAMPLE_IVE_Round(dExpOut), (1 << 15) - 1, -(1 << 15)));
    }

    return HI_SUCCESS;
}
/******************************************************************************
* function : Ann  mlp binary feature
******************************************************************************/
static HI_VOID SAMPLE_IVE_Ann_Mlp_BinFeature(HI_U8* pu8GrayImg, HI_U16 u16Width, HI_U16 u16Height, HI_S16Q16* ps16q16BinFeature)
{
    HI_U32 u32Step = 4;
    HI_U32 u16Sum = 0;
    HI_U16 i, j;
    HI_U16 m, n;
    HI_U16 u16FeatureNum = 0;

    for (i = 0; i < u16Height - u32Step + 1; i += 4)
    {
        for (j = 0; j < u16Width -  u32Step + 1; j += 4)
        {
            u16Sum = 0;
            for (m = i; m < i + u32Step; m++)
            {
                for (n = j; n < j + u32Step; n++)
                {
                    u16Sum += pu8GrayImg[m * u16Width + n];
                }
            }
            ps16q16BinFeature[u16FeatureNum++] = u16Sum * 65536 / (u32Step * u32Step * 255);
        }
    }
}
/******************************************************************************
* function : Ann mlp uninit
******************************************************************************/
static HI_VOID SAMPLE_IVE_Ann_Mlp_Uninit(SAMPLE_IVE_ANN_INFO_S* pstAnnInfo)
{
    IVE_MMZ_FREE(pstAnnInfo->stTable.stTable.u32PhyAddr, pstAnnInfo->stTable.stTable.pu8VirAddr);
    HI_MPI_IVE_ANN_MLP_UnloadModel(&pstAnnInfo->stAnnModel);
    IVE_MMZ_FREE(pstAnnInfo->stSrc.u32PhyAddr, pstAnnInfo->stSrc.pu8VirAddr);
    IVE_MMZ_FREE(pstAnnInfo->stDst.u32PhyAddr, pstAnnInfo->stDst.pu8VirAddr);
    IVE_MMZ_FREE(pstAnnInfo->stGray.u32PhyAddr[0], pstAnnInfo->stGray.pu8VirAddr[0]);

}
/******************************************************************************
* function : Ann mlp init
******************************************************************************/
static HI_S32 SAMPLE_IVE_Ann_Mlp_Init(SAMPLE_IVE_ANN_INFO_S* pstAnnInfo, HI_CHAR* pchBinFileName)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Size;

    memset(pstAnnInfo, 0, sizeof(SAMPLE_IVE_ANN_INFO_S));

    pstAnnInfo->stTable.s32TabInLower = 0;
    pstAnnInfo->stTable.s32TabInUpper = 1;//1;
    pstAnnInfo->stTable.u8TabInPreci  = 8;//12;
    pstAnnInfo->stTable.u8TabOutNorm  = 2;
    pstAnnInfo->stTable.u16ElemNum = pstAnnInfo->stTable.s32TabInUpper << pstAnnInfo->stTable.u8TabInPreci;
    u32Size = pstAnnInfo->stTable.u16ElemNum * sizeof(HI_U16);
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstAnnInfo->stTable.stTable), u32Size);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateMemInfo fail\n");
        goto ANN_INIT_FAIL;
    }

    s32Ret = SAMPLE_IVE_Ann_Mlp_CreateTable(&(pstAnnInfo->stTable), 0.6667f, 1.7159f);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_IVE_Ann_Mlp_CreateTable fail\n");
        goto ANN_INIT_FAIL;
    }
    s32Ret = HI_MPI_IVE_ANN_MLP_LoadModel(pchBinFileName, &(pstAnnInfo->stAnnModel));
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("HI_MPI_IVE_ANN_MLP_LoadModel fail,Error(%#x)\n", s32Ret);
        goto ANN_INIT_FAIL;
    }
    u32Size = pstAnnInfo->stAnnModel.au16LayerCount[0] * sizeof(HI_S16Q16);
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstAnnInfo->stSrc), u32Size);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateMemInfo fail\n");
        goto ANN_INIT_FAIL;
    }
    u32Size = pstAnnInfo->stAnnModel.au16LayerCount[pstAnnInfo->stAnnModel.u8LayerNum - 1] * sizeof(HI_S16Q16);
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstAnnInfo->stDst), u32Size);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateMemInfo fail\n");
        goto ANN_INIT_FAIL;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstAnnInfo->stGray), IVE_IMAGE_TYPE_U8C1, 16, 32);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateImage fail\n");
        goto ANN_INIT_FAIL;
    }

ANN_INIT_FAIL:

    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_IVE_Ann_Mlp_Uninit(pstAnnInfo);
    }

    return s32Ret;

}
/******************************************************************************
* function : Ann mlp predict
******************************************************************************/
static HI_VOID SAMPLE_IVE_Ann_Mlp_Predict(SAMPLE_IVE_ANN_INFO_S* pstAnnInfo)
{
    HI_S32 i, k;
    HI_S32 s32Ret;
    HI_S32 s32ResponseCls;
    HI_U16 u16LayerCount;
    HI_S16Q16* ps16q16Dst;
    HI_S16Q16 s16q16Response;
    HI_BOOL bInstant = HI_TRUE;
    HI_BOOL bFinish;
    HI_BOOL bBlock = HI_TRUE;
    HI_CHAR achFileName[IVE_FILE_NAME_LEN];
    FILE* pFp = HI_NULL;
    IVE_HANDLE iveHandle;
    for (i = 0; i < 3; ++i)
    {
        ps16q16Dst = (HI_S16Q16*)pstAnnInfo->stDst.pu8VirAddr;
        s16q16Response = 0;
        s32ResponseCls = -1;

        snprintf(achFileName, IVE_FILE_NAME_LEN, "./data/input/ann/%d.yuv", i);
        pFp = fopen(achFileName, "rb");
        if (NULL == pFp)
        {
            SAMPLE_PRT("Open file fail,file %s\n", achFileName);
            break;
        }

        s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstAnnInfo->stGray), pFp);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("SAMPLE_COMM_IVE_ReadFile fail,file %s\n", achFileName);
            break;
        }
        IVE_CLOSE_FILE(pFp);

        SAMPLE_IVE_Ann_Mlp_BinFeature(pstAnnInfo->stGray.pu8VirAddr[0], pstAnnInfo->stGray.u16Width, \
                                      pstAnnInfo->stGray.u16Height, (HI_S16Q16*)pstAnnInfo->stSrc.pu8VirAddr);

        s32Ret = HI_MPI_IVE_ANN_MLP_Predict(&iveHandle, &(pstAnnInfo->stSrc), \
                                            & (pstAnnInfo->stTable), &(pstAnnInfo->stAnnModel), &(pstAnnInfo->stDst), bInstant);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("HI_MPI_IVE_ANN_MLP_Predict fail,Error(%#x)\n", s32Ret);
            break;
        }
        s32Ret = HI_MPI_IVE_Query(iveHandle, &bFinish, bBlock);
        while (HI_ERR_IVE_QUERY_TIMEOUT == s32Ret)
        {
            usleep(100);
            s32Ret = HI_MPI_IVE_Query(iveHandle, &bFinish, bBlock);
        }
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("HI_MPI_IVE_Query fail,Error(%#x)\n", s32Ret);
            break;
        }
        u16LayerCount = pstAnnInfo->stAnnModel.au16LayerCount[pstAnnInfo->stAnnModel.u8LayerNum - 1];
        for (k = 0; k < u16LayerCount; k++)
        {
            if (s16q16Response < ps16q16Dst[k])
            {
                s16q16Response = ps16q16Dst[k];
                s32ResponseCls = k;
            }
        }

        SAMPLE_PRT("%d.yuv belong to class %d.\n", i, s32ResponseCls);

    }

    IVE_CLOSE_FILE(pFp);

}
/******************************************************************************
* function : show ann sample
******************************************************************************/
HI_VOID SAMPLE_IVE_Ann(HI_VOID)
{
    HI_S32 s32Ret;
    SAMPLE_IVE_ANN_INFO_S stAnnInfo;
    HI_CHAR* pchBinFileName = "./data/input/ann/ann_char_rec.bin";

    SAMPLE_COMM_IVE_CheckIveMpiInit();

    //init
    s32Ret = SAMPLE_IVE_Ann_Mlp_Init(&stAnnInfo, pchBinFileName);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_IVE_Ann_Mlp_Init fail\n");
        goto ANN_FAIL;
    }
    //predict
    SAMPLE_IVE_Ann_Mlp_Predict(&stAnnInfo);

    //uninit
    SAMPLE_IVE_Ann_Mlp_Uninit(&stAnnInfo);

ANN_FAIL:
    SAMPLE_COMM_IVE_IveMpiExit();
}




