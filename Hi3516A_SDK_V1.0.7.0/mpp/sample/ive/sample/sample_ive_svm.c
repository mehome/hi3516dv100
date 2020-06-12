#include "hi_common.h"
#include "hi_comm_video.h"
#include "hi_comm_sys.h"
#include "hi_comm_ive.h"

#include "mpi_vb.h"
#include "mpi_sys.h"
#include "mpi_ive.h"
#include <math.h>

#include "sample_comm_ive.h"

#define HI_SVM_PLATE_CLASS_COUNT          2
#define HI_SVM_PLATE_CLASS_DES_NUM        8

#define HI_CLIP(a, maxv, minv)		 (((a)>(maxv)) ? (maxv) : (((a) < (minv)) ? (minv) : (a)))

typedef struct hiSAMPLE_IVE_SVM_INFO_S
{
    IVE_MEM_INFO_S stSrc;
    IVE_MEM_INFO_S stVote;
    IVE_IMAGE_S stGrayImg;
    IVE_LOOK_UP_TABLE_S stTable;
    IVE_SVM_MODEL_S stSvmModel ;
} SAMPLE_IVE_SVM_INFO_S, *SAMPLE_IVE_SVM_INFO_S_PTR;

/******************************************************************************
* function : SVM create table
******************************************************************************/
static HI_S32 SAMPLE_IVE_Svm_CreateTable(IVE_LOOK_UP_TABLE_S* pstTable, HI_FLOAT fGamma)
{
    HI_U32 i;
    HI_DOUBLE tmp;
    HI_S1Q15* ps1q15Tmp;
    HI_FLOAT  f32ExpIn;
    HI_DOUBLE d32ExpOut;

    if (pstTable->stTable.u32Size < pstTable->u16ElemNum * sizeof(HI_S1Q15))
    {
        SAMPLE_PRT("Invalid table size\n");
        return HI_FAILURE;
    }

    ps1q15Tmp = (HI_S1Q15*)pstTable->stTable.pu8VirAddr;
    for (i = 0; i < pstTable->u16ElemNum; i++)
    {
        f32ExpIn  = pstTable->s32TabInLower + (HI_FLOAT)i / (1 << pstTable->u8TabInPreci);
        d32ExpOut = (exp(-fGamma * f32ExpIn) / (1 << pstTable->u8TabOutNorm)) * (1 << 15);
        tmp = (HI_CLIP(d32ExpOut, (1 << 15) - 1, 0));
        ps1q15Tmp[i] = (HI_S1Q15)(tmp + 0.5f);
    }
    return HI_SUCCESS;
}


/******************************************************************************
* function : SVM uninit
******************************************************************************/
static HI_VOID SAMPLE_IVE_Svm_Uninit(SAMPLE_IVE_SVM_INFO_S* pstSVMInfo)
{
    IVE_MMZ_FREE(pstSVMInfo->stTable.stTable.u32PhyAddr, pstSVMInfo->stTable.stTable.pu8VirAddr);
    HI_MPI_IVE_SVM_UnloadModel(&pstSVMInfo->stSvmModel);
    IVE_MMZ_FREE(pstSVMInfo->stSrc.u32PhyAddr, pstSVMInfo->stSrc.pu8VirAddr);
    IVE_MMZ_FREE(pstSVMInfo->stVote.u32PhyAddr, pstSVMInfo->stVote.pu8VirAddr);
    IVE_MMZ_FREE(pstSVMInfo->stGrayImg.u32PhyAddr[0], pstSVMInfo->stGrayImg.pu8VirAddr[0]);
}



/****************************************************************************
* function : SVM init
*****************************************************************************/
static HI_S32 SAMPLE_IVE_Svm_Init(SAMPLE_IVE_SVM_INFO_S* pStSvmInfo, HI_CHAR* pchBinFileName)
{

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Size;
    HI_FLOAT	 fGamma = 0.05f;
    HI_U16 u16Width = 16;
    HI_U16 u16Height = 32;

    memset(pStSvmInfo, 0, sizeof(SAMPLE_IVE_SVM_INFO_S));

    pStSvmInfo->stTable.s32TabInLower = 0;
    pStSvmInfo->stTable.s32TabInUpper = 64;
    pStSvmInfo->stTable.u8TabInPreci  = 3;
    pStSvmInfo->stTable.u8TabOutNorm  = 0;
    pStSvmInfo->stTable.u16ElemNum = (pStSvmInfo->stTable.s32TabInUpper - pStSvmInfo->stTable.s32TabInLower) << pStSvmInfo->stTable.u8TabInPreci;
    pStSvmInfo->stTable.stTable.u32Size = pStSvmInfo->stTable.u16ElemNum * sizeof(HI_U16);
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pStSvmInfo->stTable.stTable), pStSvmInfo->stTable.stTable.u32Size);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateMemInfo fail\n");
        goto SVM_INIT_FAIL;
    }

    s32Ret = SAMPLE_IVE_Svm_CreateTable(&(pStSvmInfo->stTable), fGamma);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_IVE_Svm_CreateTable fail\n");
        goto SVM_INIT_FAIL;
    }

    s32Ret = HI_MPI_IVE_SVM_LoadModel(pchBinFileName, &(pStSvmInfo->stSvmModel));
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("HI_MPI_IVE_SVM_LoadModel fail,Error(%#x)\n", s32Ret);
        goto SVM_INIT_FAIL;
    }

    pStSvmInfo ->stSvmModel.enType = IVE_SVM_TYPE_C_SVC;
    pStSvmInfo->stSvmModel.enKernelType = IVE_SVM_KERNEL_TYPE_RBF;


    u32Size = pStSvmInfo->stSvmModel.u16FeatureDim * sizeof(HI_S16Q16);
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pStSvmInfo->stSrc), u32Size);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateMemInfo fail\n");
        goto SVM_INIT_FAIL;
    }

    u32Size = pStSvmInfo->stSvmModel.u8ClassCount * sizeof(HI_U16);
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pStSvmInfo->stVote), u32Size);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateMemInfo fail\n");
        goto SVM_INIT_FAIL;
    }

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pStSvmInfo->stGrayImg), IVE_IMAGE_TYPE_U8C1, u16Width, u16Height);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("SAMPLE_COMM_IVE_CreateImage fail\n");
        goto SVM_INIT_FAIL;
    }

SVM_INIT_FAIL:
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_IVE_Svm_Uninit(pStSvmInfo);
    }
    return s32Ret;
}


/******************************************************************************
* function : Svm graysacle feature
******************************************************************************/
static HI_VOID SAMPLE_IVE_Svm_Feature(HI_U8* pu8GrayImg, HI_U16 u16Width, HI_U16 u16Height, HI_S16Q16* ps16q16Feature)
{
    HI_U32  step = 4;
    HI_U16 i, j, m, n;
    HI_U16 u16FeatureNum = 0;
    HI_FLOAT fFeature;
    HI_U32 sum = 0;
    for (i = 0; i < u16Height - step + 1; i += 4)
    {
        for (j = 0; j < u16Width - step + 1; j += 4)
        {
            sum = 0;
            for (m = i; m < i + step; m++)
            {
                for (n = j; n < j + step; n++)
                {
                    sum += pu8GrayImg[m * u16Width + n];
                }
            }
            fFeature = (HI_FLOAT)sum / (step * step * 255);
            ps16q16Feature[u16FeatureNum++] = (HI_S16Q16)(fFeature * (1 << 16) + 0.5f);
        }
    }

}


/******************************************************************************
* function : SVM predict
******************************************************************************/
static HI_VOID SAMPLE_IVE_Svm_Predict(SAMPLE_IVE_SVM_INFO_S* pstSvmInfo)
{

    HI_S32 i, j;
    HI_S32 s32Ret;
    HI_U16*		pu16Vote;
    HI_U8		u8MaxVoteIdx;
    HI_BOOL bInstant = HI_TRUE;
    HI_BOOL bFinish;
    HI_BOOL bBlock = HI_TRUE;
    HI_CHAR achFileName[IVE_FILE_NAME_LEN];
    FILE* pFp = HI_NULL;
    IVE_HANDLE iveHandle;

    for ( i = 0; i < 4; i++)
    {

        snprintf(achFileName, IVE_FILE_NAME_LEN, "./data/input/svm/%d.yuv", i);
        pFp = fopen(achFileName, "rb");
        if (NULL == pFp)
        {
            SAMPLE_PRT("Open file %s fail\n", achFileName);
            break;
        }
        s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstSvmInfo->stGrayImg), pFp);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("SAMPLE_COMM_IVE_ReadFile fail, file %s\n", achFileName);
            break;
        }
        IVE_CLOSE_FILE(pFp);

        SAMPLE_IVE_Svm_Feature(pstSvmInfo->stGrayImg.pu8VirAddr[0], pstSvmInfo->stGrayImg.u16Width, \
                               pstSvmInfo->stGrayImg.u16Height, (HI_S16Q16*)pstSvmInfo->stSrc.pu8VirAddr);

        s32Ret = HI_MPI_IVE_SVM_Predict(&iveHandle, &(pstSvmInfo->stSrc), &(pstSvmInfo->stTable), \
                                        & (pstSvmInfo->stSvmModel), &(pstSvmInfo->stVote), bInstant);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("HI_MPI_IVE_SVM_Predict fail,Error(%#x)\n", s32Ret);
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

        pu16Vote = (HI_U16*)pstSvmInfo->stVote.pu8VirAddr;
        u8MaxVoteIdx = 0;

        for ( j = 0; j < pstSvmInfo->stSvmModel.u8ClassCount; j++)
        {
            if (pu16Vote[u8MaxVoteIdx] < pu16Vote[j])
            { u8MaxVoteIdx = j; }
        }

        SAMPLE_PRT("%d.yuv belong to class %d.\n", i, u8MaxVoteIdx);

    }
    IVE_CLOSE_FILE(pFp);
}




/******************************************************************************
* function : show svm sample
******************************************************************************/

HI_VOID SAMPLE_IVE_Svm(HI_VOID)
{
    HI_S32 s32Ret;
    SAMPLE_IVE_SVM_INFO_S stSvmInfo;
    HI_CHAR*	pchBinFileName = "./data/input/svm/svm_char_rec.bin";

    SAMPLE_COMM_IVE_CheckIveMpiInit();

    //Init
    s32Ret = SAMPLE_IVE_Svm_Init(&stSvmInfo, pchBinFileName);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_IVE_Svm_Init fail");
        goto SVM_FAIL;
    }

    //Predict
    SAMPLE_IVE_Svm_Predict(&stSvmInfo);

    //Uninit
    SAMPLE_IVE_Svm_Uninit(&stSvmInfo);
SVM_FAIL:
    SAMPLE_COMM_IVE_IveMpiExit();
}



