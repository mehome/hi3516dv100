/******************************************************************************
  A simple program of Hisilicon Hi35xx video input and output implementation.
  Copyright (C), 2010-2011, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
    Modification:  2011-8 Created
******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "sample_comm.h"


VIDEO_NORM_E gs_enNorm = VIDEO_ENCODING_MODE_PAL;
VO_INTF_TYPE_E g_enVoIntfType = VO_INTF_CVBS;
PIC_SIZE_E g_enPicSize = PIC_HD1080;

SAMPLE_VIDEO_LOSS_S gs_stVideoLoss;
HI_U32 gs_u32ViFrmRate = 0;

SAMPLE_VI_CONFIG_S g_stViChnConfig =
{
    PANASONIC_MN34220_SUBLVDS_1080P_30FPS,
    VIDEO_ENCODING_MODE_AUTO,

    ROTATE_NONE,
    VI_CHN_SET_NORMAL,
    WDR_MODE_NONE
};

/******************************************************************************
* function : show usage
******************************************************************************/
void SAMPLE_VIO_Usage(char* sPrgNm)
{
    printf("Usage : %s <index> <intf>\n", sPrgNm);
    printf("index:\n");
    printf("\t 0)online mode VI/VPSS,1080P; VO(0:SD0(CVBS), 1:BT1120). Embeded isp, phychn channel preview.\n");
    printf("\t 1)online mode VI(WDR)/VPSS,1080P); VO(0:SD0(CVBS), 1:BT1120).Embeded isp,phychn channel preview.\n");
    printf("\t 2)online mode VI(FPN)/VPSS,1080P; VO(0:SD0(CVBS), 1:BT1120).frame mode FPN,Embeded isp,phychn channel preview.\n");
    printf("\t 3)online mode VI/VPSS(LDC),1080P; VO(0:SD0(CVBS), 1:BT1120).Embeded isp, online LDC, phychn channel preview.\n");
    printf("\t 4)online mode VI/VPSS(ROTATE),1080P; VO(0:SD0(CVBS), 1:BT1120).Embeded isp, online, rotate, phychn channel preview.\n");
    printf("\t 5)offline mode VI(ROTATE),1080P; VO(0:SD0(CVBS), 1:BT1120).Embeded isp, offline, rotate, phychn channel preview.\n");
    printf("\t 6)offline mode VI(LDC),1080P; VO(0:SD0(CVBS), 1:BT1120).Embeded isp, offline, LDC, phychn channel preview.\n");
    printf("\t 7)offline mode VI(DIS),1080P; VO(0:SD0(CVBS), 1:BT1120).Embeded isp, offline, DIS, phychn channel preview.\n");
    printf("\t 8)offline mode VI: BT1120; VO(0:SD0(CVBS), 1:BT1120).Isp bypass, phychn channel preview.\n");
    printf("\t 9)offline mode VI; VO(0:SD0(CVBS), 1:BT1120).Embeded isp, resolution switch.\n");
    printf("intf:\n");
    printf("\t 0) vo cvbs output, default.\n");
    printf("\t 1) vo BT1120 output.\n");

    return;
}

/******************************************************************************
* function : to process abnormal case
******************************************************************************/
void SAMPLE_VIO_HandleSig(HI_S32 signo)
{
    if (SIGINT == signo || SIGTERM == signo)
    {
        SAMPLE_COMM_ISP_Stop();
        SAMPLE_COMM_SYS_Exit();
        printf("\033[0;31mprogram termination abnormally!\033[0;39m\n");
    }
    exit(-1);
}


/******************************************************************************
* function : vi/vpss: online mode VI: DC(1080P); VO: SD0(CVBS). Embeded isp, phychn channel preview.
******************************************************************************/
HI_S32 SAMPLE_VIO_1080P_PreView(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;
    VO_LAYER VoLayer = 0;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;
    VPSS_GRP VpssGrp = 0;
    VPSS_CHN VpssChn = 0;
    VPSS_GRP_ATTR_S stVpssGrpAttr;
    VPSS_CHN_ATTR_S stVpssChnAttr;
    VPSS_CHN_MODE_S stVpssChnMode;
    VPSS_EXT_CHN_ATTR_S stVpssExtChnAttr;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    ROTATE_E enRotate = ROTATE_NONE;

    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt  = u32ViChnCnt * 8;

    /******************************************
     step 2: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_0;
    }

    if (pstViConfig)
    {
        enRotate = pstViConfig->enRotate;
        if (ROTATE_90 == enRotate || ROTATE_270 == enRotate)
        {
            u32BlkSize = (CEILING_2_POWER(stSize.u32Width, SAMPLE_SYS_ALIGN_WIDTH) * \
                          CEILING_2_POWER(stSize.u32Height, SAMPLE_SYS_ALIGN_WIDTH) * \
                          ((PIXEL_FORMAT_YUV_SEMIPLANAR_422 == SAMPLE_PIXEL_FORMAT) ? 2 : 1.5));
            stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
            stVbConf.astCommPool[1].u32BlkCnt = 8;
        }
    }

    /******************************************
     step 3: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }

    stVpssGrpAttr.bDciEn    = HI_FALSE;
    stVpssGrpAttr.bHistEn   = HI_FALSE;
    stVpssGrpAttr.bIeEn     = HI_FALSE;
    stVpssGrpAttr.bNrEn     = HI_TRUE;
    stVpssGrpAttr.enDieMode = VPSS_DIE_MODE_NODIE;
    stVpssGrpAttr.enPixFmt  = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stVpssGrpAttr.u32MaxW = stSize.u32Width;
    stVpssGrpAttr.u32MaxH = stSize.u32Height;


    /******************************************
     step 5: start vpss group
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_StartGroup(VpssGrp, &stVpssGrpAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS GROUP failed!\n");
        goto END_1080P_1;
    }

    stVpssChnAttr.bBorderEn       = 0;
    stVpssChnAttr.bFlip           = 0;
    stVpssChnAttr.bMirror         = 0;
    stVpssChnAttr.bSpEn           = 0 ;
    stVpssChnAttr.s32DstFrameRate = -1;
    stVpssChnAttr.s32SrcFrameRate = -1;
    stVpssChnMode.bDouble         = HI_FALSE;
    stVpssChnMode.enChnMode       = VPSS_CHN_MODE_USER;
    stVpssChnMode.enCompressMode  = COMPRESS_MODE_SEG;
    stVpssChnMode.enPixelFormat   = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stVpssChnMode.u32Width        = stSize.u32Width;
    stVpssChnMode.u32Height       = stSize.u32Height;

    /******************************************
    step 6: start vpss chn
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, &stVpssChnAttr, &stVpssChnMode, &stVpssExtChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS CHN failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 7: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_1080P30;
        gs_u32ViFrmRate = 50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;

    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDev failed!\n");
        goto END_1080P_2;
    }

    stLayerAttr.bClusterMode = HI_FALSE;
    stLayerAttr.bDoubleFrame = HI_FALSE;
    stLayerAttr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stLayerAttr.stDispRect.s32X = 0;
    stLayerAttr.stDispRect.s32Y = 0;

    s32Ret = SAMPLE_COMM_VO_GetWH(stVoPubAttr.enIntfSync,
                                  &stLayerAttr.stDispRect.u32Width, &stLayerAttr.stDispRect.u32Height,
                                  &stLayerAttr.u32DispFrmRt);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_GetWH failed!\n");
        goto END_1080P_2;
    }

    stLayerAttr.stImageSize.u32Width  = stLayerAttr.stDispRect.u32Width;
    stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

    s32Ret = SAMPLE_COMM_VO_StartLayer(VoLayer, &stLayerAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1080P_3;
    }

    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_4;
    }


    s32Ret = SAMPLE_COMM_VO_BindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    //s32Ret = SAMPLE_COMM_VO_BindVi(VoDev, VoChn, ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVpss(vo:%d)-(VpssChn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_5;
    }

    VI_PAUSE();

    /******************************************
     step 8: exit process
    ******************************************/
END_1080P_5:
    SAMPLE_COMM_VO_UnBindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_4:
    SAMPLE_COMM_VO_StopLayer(VoLayer);
END_1080P_3:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_2:
    SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
    SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();
    return s32Ret;
}


/******************************************************************************
* function : vi/vpss: online mode VI(WDR): DC(1080P); VO: SD0(CVBS). Embeded isp, phychn channel preview.
******************************************************************************/
HI_S32 SAMPLE_VIO_LINE_WDR_PreView(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VI_DEV ViDev = 0;
    VI_CHN ViChn = 0;
    VI_DEV_ATTR_S stViDevAttr;
    ISP_DEV IspDev = 0;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;
    VO_LAYER VoLayer = 0;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;
    VPSS_GRP VpssGrp = 0;
    VPSS_CHN VpssChn = 0;
    ISP_WDR_MODE_S stWDRMode;
    VPSS_GRP_ATTR_S stVpssGrpAttr;
    VPSS_CHN_ATTR_S stVpssChnAttr;
    VPSS_CHN_MODE_S stVpssChnMode;
    VPSS_EXT_CHN_ATTR_S stVpssExtChnAttr;
    HI_U32 u32Mode = 0;
    WDR_MODE_E  enOldWDRMode;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    ROTATE_E enRotate = ROTATE_NONE;
	HI_U32 u32Times = 2;

    ISP_INNER_STATE_INFO_S stInnerStateInfo = {0};
    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 8;

    /******************************************
     step 2: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_0;
    }

    if (pstViConfig)
    {
        enRotate = pstViConfig->enRotate;
        if (ROTATE_90 == enRotate || ROTATE_270 == enRotate)
        {
            u32BlkSize = (CEILING_2_POWER(stSize.u32Width, SAMPLE_SYS_ALIGN_WIDTH) * \
                          CEILING_2_POWER(stSize.u32Height, SAMPLE_SYS_ALIGN_WIDTH) * \
                          ((PIXEL_FORMAT_YUV_SEMIPLANAR_422 == SAMPLE_PIXEL_FORMAT) ? 2 : 1.5));
            stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
            stVbConf.astCommPool[1].u32BlkCnt = 8;
        }
    }

    /******************************************
     step 3: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 4: isp wdr mode config;
    ******************************************/
#if 0
    stWdrMode.enWDRMode  = WDR_MODE_2To1_LINE;
    s32Ret = HI_MPI_ISP_SetWDRMode(0, &stWdrMode);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start WDR failed!\n");
        goto END_1080P_0;
    }
#endif

    /******************************************
     step 5: start vi dev & chn to capture
             vi wdr attr should be set;
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }

    stVpssGrpAttr.bDciEn    = HI_FALSE;
    stVpssGrpAttr.bHistEn   = HI_FALSE;
    stVpssGrpAttr.bIeEn     = HI_FALSE;
    stVpssGrpAttr.bNrEn     = HI_TRUE;
    stVpssGrpAttr.enDieMode = VPSS_DIE_MODE_NODIE;
    stVpssGrpAttr.enPixFmt  = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stVpssGrpAttr.u32MaxW   = stSize.u32Width;
    stVpssGrpAttr.u32MaxH   = stSize.u32Height;

    /******************************************
     step 5: start vpss group
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_StartGroup(VpssGrp, &stVpssGrpAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS GROUP failed!\n");
        goto END_1080P_1;
    }

    stVpssChnAttr.bBorderEn       = 0;
    stVpssChnAttr.bFlip           = 0;
    stVpssChnAttr.bMirror         = 0;
    stVpssChnAttr.bSpEn           = 0 ;
    stVpssChnAttr.s32DstFrameRate = -1;
    stVpssChnAttr.s32SrcFrameRate = -1;
    stVpssChnMode.bDouble         = HI_FALSE;
    stVpssChnMode.enChnMode       = VPSS_CHN_MODE_USER;
    stVpssChnMode.enCompressMode  = COMPRESS_MODE_SEG;
    stVpssChnMode.enPixelFormat   = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stVpssChnMode.u32Width        = stSize.u32Width;
    stVpssChnMode.u32Height       = stSize.u32Height;

    /******************************************
    step 6: start vpss chn
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, &stVpssChnAttr, &stVpssChnMode, &stVpssExtChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS CHN failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 7: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_1080P30;
        gs_u32ViFrmRate = 50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;

    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDev failed!\n");
        goto END_1080P_2;
    }

    stLayerAttr.bClusterMode = HI_FALSE;
    stLayerAttr.bDoubleFrame = HI_FALSE;
    stLayerAttr.enPixFormat  = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stLayerAttr.stDispRect.s32X = 0;
    stLayerAttr.stDispRect.s32Y = 0;

    s32Ret = SAMPLE_COMM_VO_GetWH(stVoPubAttr.enIntfSync,
                                  &stLayerAttr.stDispRect.u32Width, &stLayerAttr.stDispRect.u32Height,
                                  &stLayerAttr.u32DispFrmRt);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_GetWH failed!\n");
        goto END_1080P_2;
    }
    stLayerAttr.stImageSize.u32Width  = stLayerAttr.stDispRect.u32Width;
    stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

    s32Ret = SAMPLE_COMM_VO_StartLayer(VoLayer, &stLayerAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1080P_3;
    }

    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_4;
    }

    HI_MPI_SYS_GetViVpssMode(&u32Mode);
    if (!u32Mode)  //off-line
    {
        s32Ret = SAMPLE_COMM_VI_BindVpss(pstViConfig->enViMode);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("SAMPLE_COMM_VI_BindVpss failed with %#x!\n", s32Ret);
            goto END_1080P_5;
        }
    }

    s32Ret = SAMPLE_COMM_VO_BindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVpss(vo:%d)-(VpssChn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_6;
    }

    s32Ret = HI_MPI_VI_GetDevAttr(ViDev, &stViDevAttr);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_6;
    }

    enOldWDRMode = pstViConfig->enWDRMode;

    while (u32Times > 0)
    {
		u32Times--;
        VI_PAUSE();
        /* switch to linear mode */
        s32Ret = HI_MPI_ISP_SetFMWState(IspDev, ISP_FMW_STATE_FREEZE);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }
        s32Ret = HI_MPI_VI_DisableChn(ViChn);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        s32Ret = HI_MPI_VI_DisableDev(ViDev);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }
        pstViConfig->enWDRMode = WDR_MODE_NONE;
        s32Ret = SAMPLE_COMM_VI_StartMIPI(pstViConfig);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        s32Ret = HI_MPI_ISP_SetFMWState(IspDev, ISP_FMW_STATE_RUN);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        stWDRMode.enWDRMode = pstViConfig->enWDRMode;
        s32Ret = HI_MPI_ISP_SetWDRMode(IspDev, &stWDRMode);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        while (1)
        {
            HI_MPI_ISP_QueryInnerStateInfo(IspDev, &stInnerStateInfo);
            if (HI_TRUE == stInnerStateInfo.bWDRSwitchFinish)
            {
                SAMPLE_PRT("wdr switch finish!\n");
                break;
            }
            usleep(10000);
        }

        s32Ret = SAMPLE_COMM_VI_StartDev(ViDev, pstViConfig->enViMode);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        s32Ret = HI_MPI_VI_EnableChn(ViChn);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        VI_PAUSE();
        s32Ret = HI_MPI_ISP_SetFMWState(IspDev, ISP_FMW_STATE_FREEZE);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }
        /* switch to 2to1 line WDR mode */
        s32Ret = HI_MPI_VI_DisableChn(ViChn);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        s32Ret = HI_MPI_VI_DisableDev(ViDev);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }
        pstViConfig->enWDRMode = enOldWDRMode;
        s32Ret = SAMPLE_COMM_VI_StartMIPI(pstViConfig);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        s32Ret = HI_MPI_ISP_SetFMWState(IspDev, ISP_FMW_STATE_RUN);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        stWDRMode.enWDRMode = pstViConfig->enWDRMode;
        s32Ret = HI_MPI_ISP_SetWDRMode(IspDev, &stWDRMode);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        while (1)
        {
            HI_MPI_ISP_QueryInnerStateInfo(IspDev, &stInnerStateInfo);
            if (HI_TRUE == stInnerStateInfo.bWDRSwitchFinish)
            {
                SAMPLE_PRT("wdr switch finish!\n");
                break;
            }
            usleep(10000);
        }

        s32Ret = SAMPLE_COMM_VI_StartDev(ViDev, pstViConfig->enViMode);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        s32Ret = HI_MPI_VI_EnableChn(ViChn);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            goto END_1080P_6;
        }

        VI_PAUSE();
    }
    /******************************************
     step 8: exit process
    ******************************************/
END_1080P_6:
    SAMPLE_COMM_VO_UnBindVpss(VoDev, VoChn, VpssGrp, VpssChn);
END_1080P_5:
    if (!u32Mode)
    {
        SAMPLE_COMM_VI_UnBindVpss(pstViConfig->enViMode);
    }

    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_4:
    SAMPLE_COMM_VO_StopLayer(VoLayer);
END_1080P_3:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_2:
    SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
    SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();
    return s32Ret;
}


/******************************************************************************
* function : vi/vpss: online mode VI(FPN): DC(1080P); VO: SD0(CVBS). Embeded isp, phychn channel preview.
******************************************************************************/
HI_S32 SAMPLE_VIO_FRAME_FPN_PreView(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;
    VO_LAYER VoLayer = 0;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;
    VPSS_GRP VpssGrp = 0;
    VPSS_CHN VpssChn = 0;
    VPSS_GRP_ATTR_S stVpssGrpAttr;
    VPSS_CHN_ATTR_S stVpssChnAttr;
    VPSS_CHN_MODE_S stVpssChnMode;
    VPSS_EXT_CHN_ATTR_S stVpssExtChnAttr;


    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    ROTATE_E enRotate = ROTATE_NONE;

    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 PIXEL_FORMAT_YUV_SEMIPLANAR_422, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 8;

    /******************************************
     step 2: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_0;
    }

    if (pstViConfig)
    {
        enRotate = pstViConfig->enRotate;
        if (ROTATE_90 == enRotate || ROTATE_270 == enRotate)
        {
            u32BlkSize = (CEILING_2_POWER(stSize.u32Width, SAMPLE_SYS_ALIGN_WIDTH) * \
                          CEILING_2_POWER(stSize.u32Height, SAMPLE_SYS_ALIGN_WIDTH) * \
                          ((PIXEL_FORMAT_YUV_SEMIPLANAR_422 == SAMPLE_PIXEL_FORMAT) ? 2 : 1.5));
            stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
            stVbConf.astCommPool[1].u32BlkCnt = 8;
        }
    }

    /******************************************
     step 3: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }


    stVpssGrpAttr.bDciEn    = HI_FALSE;
    stVpssGrpAttr.bHistEn   = HI_FALSE;
    stVpssGrpAttr.bIeEn     = HI_FALSE;
    stVpssGrpAttr.bNrEn     = HI_TRUE;
    stVpssGrpAttr.enDieMode = VPSS_DIE_MODE_NODIE;
    stVpssGrpAttr.enPixFmt  = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stVpssGrpAttr.u32MaxW = stSize.u32Width;
    stVpssGrpAttr.u32MaxH = stSize.u32Height;

    /******************************************
     step 5: start vpss group
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_StartGroup(VpssGrp, &stVpssGrpAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS GROUP failed!\n");
        goto END_1080P_1;
    }

    stVpssChnAttr.bBorderEn       = 0;
    stVpssChnAttr.bFlip           = 0;
    stVpssChnAttr.bMirror         = 0;
    stVpssChnAttr.bSpEn           = 0 ;
    stVpssChnAttr.s32DstFrameRate = -1;
    stVpssChnAttr.s32SrcFrameRate = -1;
    stVpssChnMode.bDouble         = HI_FALSE;
    stVpssChnMode.enChnMode       = VPSS_CHN_MODE_USER;
    stVpssChnMode.enCompressMode  = COMPRESS_MODE_SEG;
    stVpssChnMode.enPixelFormat   = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stVpssChnMode.u32Width        = stSize.u32Width;
    stVpssChnMode.u32Height       = stSize.u32Height;

    /******************************************
     step 6: start vpss chn
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, &stVpssChnAttr, &stVpssChnMode, &stVpssExtChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS CHN failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 7: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_1080P30;
        gs_u32ViFrmRate = 50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;

    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDev failed!\n");
        goto END_1080P_2;
    }

    stLayerAttr.bClusterMode = HI_FALSE;
    stLayerAttr.bDoubleFrame = HI_FALSE;
    stLayerAttr.enPixFormat  = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stLayerAttr.stDispRect.s32X = 0;
    stLayerAttr.stDispRect.s32Y = 0;

    s32Ret = SAMPLE_COMM_VO_GetWH(stVoPubAttr.enIntfSync,
                                  &stLayerAttr.stDispRect.u32Width, &stLayerAttr.stDispRect.u32Height,
                                  &stLayerAttr.u32DispFrmRt);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_GetWH failed!\n");
        goto END_1080P_2;
    }

    stLayerAttr.stImageSize.u32Width  = stLayerAttr.stDispRect.u32Width;
    stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

    s32Ret = SAMPLE_COMM_VO_StartLayer(VoLayer, &stLayerAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1080P_3;
    }

    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_4;
    }

    s32Ret = SAMPLE_COMM_VO_BindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVpss(vo:%d)-(VpssChn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_5;
    }

    const char* fpn_file = "sample";   /* fpn file name */
    ISP_FPN_TYPE_E enFpnType = ISP_FPN_TYPE_FRAME; /* line/frame */
    PIXEL_FORMAT_E enPixelFormat = PIXEL_FORMAT_RGB_BAYER;
    COMPRESS_MODE_E	enCompressMode = COMPRESS_MODE_NONE;
    HI_U32 u32FrmNum = 16;
    HI_U32 u32Threshold = 4095;
    char fileName[FILE_NAME_LEN];
    VI_CHN_ATTR_S stTempChnAttr;
    VI_CHN ViChn = 0;


    /* fpn calibrate, save dark frame file */
    s32Ret = SAMPLE_COMM_VI_FPN_CALIBRATE_CONFIG(fpn_file, enFpnType,
             enPixelFormat, enCompressMode,
             u32FrmNum, u32Threshold);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("FPN calibrate failed %#x!\n", s32Ret);
        goto END_1080P_5;
    }

    ISP_OP_TYPE_E  enOpType = OP_TYPE_AUTO; /* auto/manual */
    HI_U32 u32Strength = 0X100;             /* strength */


    /* fpn correction, read dark frame file */
    s32Ret =  HI_MPI_VI_GetChnAttr(ViChn, &stTempChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("get vi chn attr failed!");
        goto END_1080P_5;
    }
    snprintf(fileName, FILE_NAME_LEN, "./%s_%d_%d_%dbit.raw", fpn_file, stTempChnAttr.stDestSize.u32Width,
            stTempChnAttr.stDestSize.u32Height , 16);
    s32Ret = SAMPLE_COMM_VI_CORRECTION_CONFIG(fileName, enFpnType, enOpType,
             u32Strength, enPixelFormat);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("FPN correction failed %#x!\n", s32Ret);
        goto END_1080P_5;
    }


    /******************************************
     step 8: exit process
    ******************************************/
END_1080P_5:
    SAMPLE_COMM_VO_UnBindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_4:
    SAMPLE_COMM_VO_StopLayer(VoLayer);
END_1080P_3:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_2:
    SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
    SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();
    return s32Ret;
}


/******************************************************************************
* function : vi/vpss: online mode VI: DC(1080P);VPSS(LDC) VO: SD0(CVBS). Embeded isp, phychn channel preview.
******************************************************************************/
HI_S32 SAMPLE_VI_VPSS_LDC_VO_1080P_PreView(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;
    VO_LAYER VoLayer = 0;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;
    VPSS_GRP VpssGrp = 0;
    VPSS_CHN VpssChn = 0;
    VPSS_GRP_ATTR_S stVpssGrpAttr;
    VPSS_CHN_ATTR_S stVpssChnAttr;
    VPSS_CHN_MODE_S stVpssChnMode;
    VPSS_EXT_CHN_ATTR_S stVpssExtChnAttr;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    ROTATE_E enRotate = ROTATE_NONE;
    VPSS_LDC_ATTR_S stLDCAttr;

    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 15;

    /******************************************
     step 2: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_0;
    }

    if (pstViConfig)
    {
        enRotate = pstViConfig->enRotate;
        if (ROTATE_90 == enRotate || ROTATE_270 == enRotate)
        {
            u32BlkSize = (CEILING_2_POWER(stSize.u32Width, SAMPLE_SYS_ALIGN_WIDTH) * \
                          CEILING_2_POWER(stSize.u32Height, SAMPLE_SYS_ALIGN_WIDTH) * \
                          ((PIXEL_FORMAT_YUV_SEMIPLANAR_422 == SAMPLE_PIXEL_FORMAT) ? 2 : 1.5));
            stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
            stVbConf.astCommPool[1].u32BlkCnt = 8;
        }
    }

    /******************************************
     step 3: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }


    stVpssGrpAttr.bDciEn    = HI_FALSE;
    stVpssGrpAttr.bHistEn   = HI_FALSE;
    stVpssGrpAttr.bIeEn     = HI_FALSE;
    stVpssGrpAttr.bNrEn     = HI_TRUE;
    stVpssGrpAttr.enDieMode = VPSS_DIE_MODE_NODIE;
    stVpssGrpAttr.enPixFmt  = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stVpssGrpAttr.u32MaxW   = stSize.u32Width;
    stVpssGrpAttr.u32MaxH   = stSize.u32Height;

    /******************************************
     step 5: start vpss group
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_StartGroup(VpssGrp, &stVpssGrpAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS GROUP failed!\n");
        goto END_1080P_1;
    }

    stVpssChnAttr.bBorderEn       = 0;
    stVpssChnAttr.bFlip           = 0;
    stVpssChnAttr.bMirror         = 0;
    stVpssChnAttr.bSpEn           = 0 ;
    stVpssChnAttr.s32DstFrameRate = -1;
    stVpssChnAttr.s32SrcFrameRate = -1;
    stVpssChnMode.bDouble         = HI_FALSE;
    stVpssChnMode.enChnMode       = VPSS_CHN_MODE_USER;
    stVpssChnMode.enCompressMode  = COMPRESS_MODE_NONE;
    stVpssChnMode.enPixelFormat   = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stVpssChnMode.u32Width        = stSize.u32Width;
    stVpssChnMode.u32Height       = stSize.u32Height;

    stLDCAttr.bEnable                 = HI_TRUE;
    stLDCAttr.stAttr.enViewType       = LDC_VIEW_TYPE_ALL;
    stLDCAttr.stAttr.s32CenterXOffset = 0;
    stLDCAttr.stAttr.s32CenterYOffset = 0;
    stLDCAttr.stAttr.s32Ratio         = 168;

    s32Ret =  HI_MPI_VPSS_SetLDCAttr(VpssGrp, VpssChn,  &stLDCAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("set LDC failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 6: start vpss chn
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, &stVpssChnAttr, &stVpssChnMode, &stVpssExtChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS CHN failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 7: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_1080P30;
        gs_u32ViFrmRate = 50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;

    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDev failed!\n");
        goto END_1080P_2;
    }

    stLayerAttr.bClusterMode = HI_FALSE;
    stLayerAttr.bDoubleFrame = HI_FALSE;
    stLayerAttr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stLayerAttr.stDispRect.s32X = 0;
    stLayerAttr.stDispRect.s32Y = 0;

    s32Ret = SAMPLE_COMM_VO_GetWH(stVoPubAttr.enIntfSync,
                                  &stLayerAttr.stDispRect.u32Width, &stLayerAttr.stDispRect.u32Height,
                                  &stLayerAttr.u32DispFrmRt);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_GetWH failed!\n");
        goto END_1080P_2;
    }
    stLayerAttr.stImageSize.u32Width  = stLayerAttr.stDispRect.u32Width;
    stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

    s32Ret = SAMPLE_COMM_VO_StartLayer(VoLayer, &stLayerAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1080P_3;
    }

    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_4;
    }

    s32Ret = SAMPLE_COMM_VO_BindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    //s32Ret = SAMPLE_COMM_VO_BindVi(VoDev, VoChn, ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVpss(vo:%d)-(VpssChn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_5;
    }

    VI_PAUSE();
    /******************************************
     step 8: exit process
    ******************************************/
END_1080P_5:
    SAMPLE_COMM_VO_UnBindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_4:
    SAMPLE_COMM_VO_StopLayer(VoLayer);
END_1080P_3:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_2:
    SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
    SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();
    return s32Ret;

}

/******************************************************************************
* function : vi/vpss: online mode VI: DC(1080P);VPSS(ROTATE);VO: SD0(CVBS). Embeded isp, phychn channel preview.
******************************************************************************/
HI_S32 SAMPLE_VI_VPSS_ROTATE_VO_1080P_PreView(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;
    VO_LAYER VoLayer = 0;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;
    VPSS_GRP VpssGrp = 0;
    VPSS_CHN VpssChn = 0;
    VPSS_GRP_ATTR_S stVpssGrpAttr;
    VPSS_CHN_ATTR_S stVpssChnAttr;
    VPSS_CHN_MODE_S stVpssChnMode;
    VPSS_EXT_CHN_ATTR_S stVpssExtChnAttr;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    ROTATE_E enRotate = ROTATE_90;

    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 8;

    /******************************************
     step 2: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_0;
    }

    if (pstViConfig)
    {
        //enRotate = pstViConfig->enRotate;
        if (ROTATE_90 == enRotate || ROTATE_270 == enRotate)
        {
            u32BlkSize = (CEILING_2_POWER(stSize.u32Width, SAMPLE_SYS_ALIGN_WIDTH) * \
                          CEILING_2_POWER(stSize.u32Height, SAMPLE_SYS_ALIGN_WIDTH) * \
                          ((PIXEL_FORMAT_YUV_SEMIPLANAR_422 == SAMPLE_PIXEL_FORMAT) ? 2 : 1.5));
            stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
            stVbConf.astCommPool[1].u32BlkCnt = 20;
        }
    }

    /******************************************
     step 3: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }

    stVpssGrpAttr.bDciEn    = HI_FALSE;
    stVpssGrpAttr.bHistEn   = HI_FALSE;
    stVpssGrpAttr.bIeEn     = HI_FALSE;
    stVpssGrpAttr.bNrEn     = HI_TRUE;
    stVpssGrpAttr.enDieMode = VPSS_DIE_MODE_NODIE;
    stVpssGrpAttr.enPixFmt  = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stVpssGrpAttr.u32MaxW   = stSize.u32Width;
    stVpssGrpAttr.u32MaxH   = stSize.u32Height;

    /******************************************
     step 5: start vpss group
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_StartGroup(VpssGrp, &stVpssGrpAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS GROUP failed!\n");
        goto END_1080P_1;
    }

    stVpssChnAttr.bBorderEn = 0;
    stVpssChnAttr.bFlip = 0;
    stVpssChnAttr.bMirror = 0;
    stVpssChnAttr.bSpEn = 0 ;
    stVpssChnAttr.s32DstFrameRate = -1;
    stVpssChnAttr.s32SrcFrameRate = -1;
    stVpssChnMode.bDouble = HI_FALSE;
    stVpssChnMode.enChnMode = VPSS_CHN_MODE_USER;
    stVpssChnMode.enCompressMode = COMPRESS_MODE_NONE;
    stVpssChnMode.enPixelFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stVpssChnMode.u32Width  = stSize.u32Width;
    stVpssChnMode.u32Height = stSize.u32Height;

    s32Ret =  HI_MPI_VPSS_SetRotate(VpssGrp, VpssChn,  enRotate);

    /******************************************
    step 6: start vpss chn
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, &stVpssChnAttr, &stVpssChnMode, &stVpssExtChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS CHN failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 7: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_1080P30;
        gs_u32ViFrmRate = 50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;

    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDev failed!\n");
        goto END_1080P_2;
    }

    stLayerAttr.bClusterMode = HI_FALSE;
    stLayerAttr.bDoubleFrame = HI_FALSE;
    stLayerAttr.enPixFormat  = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stLayerAttr.stDispRect.s32X = 0;
    stLayerAttr.stDispRect.s32Y = 0;

    s32Ret = SAMPLE_COMM_VO_GetWH(stVoPubAttr.enIntfSync,
                                  &stLayerAttr.stDispRect.u32Width, &stLayerAttr.stDispRect.u32Height,
                                  &stLayerAttr.u32DispFrmRt);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_GetWH failed!\n");
        goto END_1080P_2;
    }

    stLayerAttr.stImageSize.u32Width  = stLayerAttr.stDispRect.u32Width;
    stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

    s32Ret = SAMPLE_COMM_VO_StartLayer(VoLayer, &stLayerAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1080P_3;
    }

    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_4;
    }

    s32Ret = SAMPLE_COMM_VO_BindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    //s32Ret = SAMPLE_COMM_VO_BindVi(VoDev, VoChn, ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVpss(vo:%d)-(VpssChn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_5;
    }

    VI_PAUSE();
    /******************************************
     step 8: exit process
    ******************************************/
END_1080P_5:
    SAMPLE_COMM_VO_UnBindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_4:
    SAMPLE_COMM_VO_StopLayer(VoLayer);
END_1080P_3:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_2:
    SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
    SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();
    return s32Ret;
}



/******************************************************************************
* function : vi/vpss: offline mode VI: DC(1080P),ROTATE;VO: SD0(CVBS). Embeded isp, phychn channel preview.
******************************************************************************/
HI_S32 SAMPLE_VI_ROTATE_VO_1080P_PreView(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VI_CHN ViChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;
    VO_LAYER VoLayer = 0;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    ROTATE_E enRotate = ROTATE_90;


    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 8;

    /******************************************
     step 2: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_0;
    }

    if (pstViConfig)
    {
        enRotate = pstViConfig->enRotate;
        if (ROTATE_90 == enRotate || ROTATE_270 == enRotate)
        {
            u32BlkSize = (CEILING_2_POWER(stSize.u32Width, SAMPLE_SYS_ALIGN_WIDTH) * \
                          CEILING_2_POWER(stSize.u32Height, SAMPLE_SYS_ALIGN_WIDTH) * \
                          ((PIXEL_FORMAT_YUV_SEMIPLANAR_422 == SAMPLE_PIXEL_FORMAT) ? 2 : 1.5));
            stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
            stVbConf.astCommPool[1].u32BlkCnt = 8;
        }
    }

    /******************************************
     step 3: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }



    /******************************************
    step 7: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_1080P30;
        gs_u32ViFrmRate = 50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;

    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDev failed!\n");
        goto END_1080P_1;
    }

    stLayerAttr.bClusterMode = HI_FALSE;
    stLayerAttr.bDoubleFrame = HI_FALSE;
    stLayerAttr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stLayerAttr.stDispRect.s32X = 0;
    stLayerAttr.stDispRect.s32Y = 0;

    s32Ret = SAMPLE_COMM_VO_GetWH(stVoPubAttr.enIntfSync,
                                  &stLayerAttr.stDispRect.u32Width, &stLayerAttr.stDispRect.u32Height,
                                  &stLayerAttr.u32DispFrmRt);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_GetWH failed!\n");
        goto END_1080P_1;
    }

    stLayerAttr.stImageSize.u32Width  = stLayerAttr.stDispRect.u32Width;
    stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

    s32Ret = SAMPLE_COMM_VO_StartLayer(VoLayer, &stLayerAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1080P_2;
    }
    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_3;
    }

    //s32Ret = SAMPLE_COMM_VO_BindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    s32Ret = SAMPLE_COMM_VO_BindVi(VoDev, VoChn, ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVpss(vo:%d)-(VpssChn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_4;
    }

    VI_PAUSE();
    /******************************************
     step 8: exit process
    ******************************************/
END_1080P_4:
    SAMPLE_COMM_VO_UnBindVi(VoDev, VoChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_3:
    SAMPLE_COMM_VO_StopLayer(VoLayer);
END_1080P_2:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();

    return s32Ret;
}



/******************************************************************************
* function : vi/vpss: offline mode VI: DC(1080P),LDC;VO: SD0(CVBS). Embeded isp, phychn channel preview.
******************************************************************************/
HI_S32 SAMPLE_VI_LDC_VO_1080P_PreView(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VI_CHN ViChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;
    VO_LAYER VoLayer = 0;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    ROTATE_E enRotate = ROTATE_90;
    VI_LDC_ATTR_S stLDCAttr;

    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 8;

    /******************************************
     step 2: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_0;
    }

    if (pstViConfig)
    {
        //enRotate = pstViConfig->enRotate;
        if (ROTATE_90 == enRotate || ROTATE_270 == enRotate)
        {
            u32BlkSize = (CEILING_2_POWER(stSize.u32Width, SAMPLE_SYS_ALIGN_WIDTH) * \
                          CEILING_2_POWER(stSize.u32Height, SAMPLE_SYS_ALIGN_WIDTH) * \
                          ((PIXEL_FORMAT_YUV_SEMIPLANAR_422 == SAMPLE_PIXEL_FORMAT) ? 2 : 1.5));
            stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
            stVbConf.astCommPool[1].u32BlkCnt = 8;
        }
    }

    /******************************************
     step 3: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }



    stLDCAttr.bEnable = HI_TRUE;
    stLDCAttr.stAttr.enViewType = LDC_VIEW_TYPE_ALL;
    stLDCAttr.stAttr.s32CenterXOffset = 0;
    stLDCAttr.stAttr.s32CenterYOffset = 0;
    stLDCAttr.stAttr.s32Ratio = 168;

    s32Ret =  HI_MPI_VI_SetLDCAttr(ViChn, &stLDCAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("set LDC failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 7: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_1080P30;
        gs_u32ViFrmRate = 50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;

    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDev failed!\n");
        goto END_1080P_1;
    }

    stLayerAttr.bClusterMode = HI_FALSE;
    stLayerAttr.bDoubleFrame = HI_FALSE;
    stLayerAttr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stLayerAttr.stDispRect.s32X = 0;
    stLayerAttr.stDispRect.s32Y = 0;
    s32Ret = SAMPLE_COMM_VO_GetWH(stVoPubAttr.enIntfSync,
                                  &stLayerAttr.stDispRect.u32Width, &stLayerAttr.stDispRect.u32Height,
                                  &stLayerAttr.u32DispFrmRt);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_GetWH failed!\n");
        goto END_1080P_1;
    }

    stLayerAttr.stImageSize.u32Width  = stLayerAttr.stDispRect.u32Width;
    stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

    s32Ret = SAMPLE_COMM_VO_StartLayer(VoLayer, &stLayerAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1080P_2;
    }


    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_3;
    }

    //s32Ret = SAMPLE_COMM_VO_BindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    s32Ret = SAMPLE_COMM_VO_BindVi(VoDev, VoChn, ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVpss(vo:%d)-(VpssChn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_4;
    }

    printf("\nplease hit the Enter key, disable LDC\n\n");
    VI_PAUSE();
    stLDCAttr.bEnable = HI_FALSE;

    s32Ret =  HI_MPI_VI_SetLDCAttr(ViChn, &stLDCAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("set LDC failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }

    printf("\nplease hit the Enter key, enable LDC\n");
    VI_PAUSE();

    stLDCAttr.bEnable = HI_TRUE;

    s32Ret =  HI_MPI_VI_SetLDCAttr(ViChn, &stLDCAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("set LDC failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }

    VI_PAUSE();
    /******************************************
     step 8: exit process
    ******************************************/
END_1080P_4:
    SAMPLE_COMM_VO_UnBindVi(VoDev, VoChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_3:
    SAMPLE_COMM_VO_StopLayer(VoLayer);
END_1080P_2:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();

    return HI_SUCCESS;
}


/******************************************************************************
* function : vi/vpss: offline mode VI: DC(1080P),DIS; VPSS:3DNR; VO: SD0(CVBS). Embeded isp, phychn channel preview.
******************************************************************************/

HI_S32 SAMPLE_VI_DIS_VPSS_VO_1080P_PreView(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VI_CHN ViChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_2MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;
    VO_LAYER VoLayer = 0;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;
    VPSS_GRP VpssGrp = 0;
    VPSS_CHN VpssChn = 0;
    VPSS_GRP_ATTR_S stVpssGrpAttr;
    VPSS_CHN_ATTR_S stVpssChnAttr;
    VPSS_CHN_MODE_S stVpssChnMode;
    VI_CHN_ATTR_S stChnAttr;
    VPSS_EXT_CHN_ATTR_S stVpssExtChnAttr;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    ROTATE_E enRotate = ROTATE_NONE;

    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 15;

    /******************************************
     step 2: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_0;
    }

    if (pstViConfig)
    {
        enRotate = pstViConfig->enRotate;
        if (ROTATE_90 == enRotate || ROTATE_270 == enRotate)
        {
            u32BlkSize = (CEILING_2_POWER(stSize.u32Width, SAMPLE_SYS_ALIGN_WIDTH) * \
                          CEILING_2_POWER(stSize.u32Height, SAMPLE_SYS_ALIGN_WIDTH) * \
                          ((PIXEL_FORMAT_YUV_SEMIPLANAR_422 == SAMPLE_PIXEL_FORMAT) ? 2 : 1.5));
            stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
            stVbConf.astCommPool[1].u32BlkCnt = 8;
        }
    }

    /******************************************
     step 3: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }

    /* crop vi chn  */
    s32Ret =  HI_MPI_VI_DisableChn(ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("disable  vi chn failed!\n");
        goto END_1080P_0;
    }
    stChnAttr.stCapRect.s32X = 0;
    stChnAttr.stCapRect.s32Y = 0;
    stChnAttr.stCapRect.u32Width = 1180 + 100;
    stChnAttr.stCapRect.u32Height = 620 + 100;
    stChnAttr.bFlip = HI_FALSE;
    stChnAttr.bMirror = HI_FALSE;
    stChnAttr.enCapSel = VI_CAPSEL_BOTH;
    stChnAttr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stChnAttr.enCompressMode = COMPRESS_MODE_NONE;
    stChnAttr.s32SrcFrameRate = 30;
    stChnAttr.s32DstFrameRate = 30;

    stChnAttr.stDestSize.u32Width = stChnAttr.stCapRect.u32Width;
    stChnAttr.stDestSize.u32Height = stChnAttr.stCapRect.u32Height;
    s32Ret =  HI_MPI_VI_SetChnAttr(ViChn, &stChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("set vi chn failed!\n");
        goto END_1080P_0;
    }

    s32Ret =  HI_MPI_VI_EnableChn(ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("enable vi chn failed!\n");
        goto END_1080P_0;
    }

    stVpssGrpAttr.bDciEn = HI_FALSE;
    stVpssGrpAttr.bHistEn = HI_FALSE;
    stVpssGrpAttr.bIeEn = HI_FALSE;
    stVpssGrpAttr.bNrEn = HI_TRUE;
    stVpssGrpAttr.enDieMode = VPSS_DIE_MODE_NODIE;
    stVpssGrpAttr.enPixFmt = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stVpssGrpAttr.u32MaxH = 720 + 100;
    stVpssGrpAttr.u32MaxW = 1280 + 100;


    /******************************************
     step 5: start vpss group
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_StartGroup(VpssGrp, &stVpssGrpAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS GROUP failed!\n");
        goto END_1080P_1;
    }

    stVpssChnAttr.bBorderEn = 0;
    stVpssChnAttr.bFlip = 0;
    stVpssChnAttr.bMirror = 0;
    stVpssChnAttr.bSpEn = 0 ;
    stVpssChnAttr.s32DstFrameRate = -1;
    stVpssChnAttr.s32SrcFrameRate = -1;
    stVpssChnMode.bDouble = HI_FALSE;
    stVpssChnMode.enChnMode = VPSS_CHN_MODE_USER;
    stVpssChnMode.enCompressMode = COMPRESS_MODE_NONE;
    stVpssChnMode.enPixelFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    stVpssChnMode.u32Width  = 1180;
    stVpssChnMode.u32Height = 620;


    VPSS_CROP_INFO_S stVpssCropInfo;

    stVpssCropInfo.bEnable = HI_TRUE;
    stVpssCropInfo.enCropCoordinate = VPSS_CROP_ABS_COOR;
    stVpssCropInfo.stCropRect.s32X = 50;
    stVpssCropInfo.stCropRect.s32Y = 50;
    stVpssCropInfo.stCropRect.u32Width  = 1180;
    stVpssCropInfo.stCropRect.u32Height = 620;
    s32Ret = HI_MPI_VPSS_SetGrpCrop(VpssGrp, &stVpssCropInfo);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("set VPSS group crop failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 6: start vpss chn
    ******************************************/
    s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, &stVpssChnAttr, &stVpssChnMode, &stVpssExtChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start VPSS CHN failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 7: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_1080P30;
        gs_u32ViFrmRate = 50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;

    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDev failed!\n");
        goto END_1080P_2;
    }

    stLayerAttr.bClusterMode = HI_FALSE;
    stLayerAttr.bDoubleFrame = HI_FALSE;
    stLayerAttr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stLayerAttr.stDispRect.s32X = 0;
    stLayerAttr.stDispRect.s32Y = 0;

    s32Ret = SAMPLE_COMM_VO_GetWH(stVoPubAttr.enIntfSync,
                                  &stLayerAttr.stDispRect.u32Width, &stLayerAttr.stDispRect.u32Height,
                                  &stLayerAttr.u32DispFrmRt);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_GetWH failed!\n");
        goto END_1080P_2;
    }
    stLayerAttr.stImageSize.u32Width  = stLayerAttr.stDispRect.u32Width;
    stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

    s32Ret = SAMPLE_COMM_VO_StartLayer(VoLayer, &stLayerAttr, HI_FALSE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1080P_3;
    }

    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, enVoMode);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_4;
    }

    SAMPLE_COMM_VI_BindVpss(pstViConfig->enViMode);

    s32Ret = SAMPLE_COMM_VO_BindVpss(VoDev, VoChn + 1, VpssGrp, VpssChn);
    s32Ret = SAMPLE_COMM_VO_BindVi(VoDev, VoChn, ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVpss(vo:%d)-(VpssChn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_5;
    }


    ISP_DIS_ATTR_S stDisAttr;
    stDisAttr.bEnable = HI_TRUE;

    int IspDev = 0;
    s32Ret =  HI_MPI_ISP_SetDISAttr(IspDev, &stDisAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("set DIS atrr failed!\n");
        goto END_1080P_5;
    }

    printf("\n\npress key to disable dis ------\n");
    VI_PAUSE();

    s32Ret =  HI_MPI_ISP_GetDISAttr(IspDev, &stDisAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("get DIS atrr failed!\n");
        goto END_1080P_5;
    }
    stDisAttr.bEnable = HI_FALSE;
    s32Ret =  HI_MPI_ISP_SetDISAttr(IspDev, &stDisAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("set DIS atrr failed!\n");
        goto END_1080P_5;
    }
    printf("\n\npress key to enable dis ------\n");
    VI_PAUSE();

    s32Ret =  HI_MPI_ISP_GetDISAttr(IspDev, &stDisAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("get DIS atrr failed!\n");
        goto END_1080P_5;
    }

    stDisAttr.bEnable = HI_TRUE;
    s32Ret =  HI_MPI_ISP_SetDISAttr(IspDev, &stDisAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("set DIS atrr failed!\n");
        goto END_1080P_5;
    }
    VI_PAUSE();

    /******************************************
     step 8: exit process
    ******************************************/
END_1080P_5:
    SAMPLE_COMM_VO_UnBindVi(VoDev, VoChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_4:
    SAMPLE_COMM_VO_StopLayer(VoLayer);
END_1080P_3:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_2:
    SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
    SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();

    return s32Ret;
}



/******************************************************************************
* function :  VI: BT1120(1080I); VO: SD0(CVBS). bypass isp, phychn channel preview.
******************************************************************************/
HI_S32 SAMPLE_VIO_BT1120_1080P_PreView(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 1;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VI_CHN ViChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    VO_LAYER VoLayer = 0;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;


    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, PIC_HD1080,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 8;

    /******************************************
     step 2: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 3: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 5: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_1080P30;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;
    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDevLayer failed!\n");
        goto END_1080P_1;
    }

    stLayerAttr.bClusterMode = HI_FALSE;
    stLayerAttr.bDoubleFrame = HI_FALSE;
    stLayerAttr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stLayerAttr.stDispRect.s32X = 0;
    stLayerAttr.stDispRect.s32Y = 0;
    s32Ret = SAMPLE_COMM_VO_GetWH(stVoPubAttr.enIntfSync,
                                  &stLayerAttr.stDispRect.u32Width, &stLayerAttr.stDispRect.u32Height,
                                  &stLayerAttr.u32DispFrmRt);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_GetWH failed!\n");
        goto END_1080P_1;
    }
    stLayerAttr.stImageSize.u32Width  = stLayerAttr.stDispRect.u32Width;
    stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

    s32Ret = SAMPLE_COMM_VO_StartLayer(VoLayer, &stLayerAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1080P_2;
    }

    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_3;
    }

    s32Ret = SAMPLE_COMM_VO_BindVi(VoDev, VoChn, ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVi(vo:%d)-(vichn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_3;
    }

    VI_PAUSE();
    /******************************************
     step 6: exit process
    ******************************************/
END_1080P_3:
    SAMPLE_COMM_VO_UnBindVi(VoDev, VoChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
    SAMPLE_COMM_VO_StopLayer(VoLayer);
END_1080P_2:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();

    return s32Ret;
}

/******************************************************************************
* function :  VI: DC(720P); VO: SD0(CVBS). Embeded isp, one ExtChn preview.
******************************************************************************/
HI_S32 SAMPLE_VIO_720P_Extchn_Preview(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VI_CHN ViChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    VI_EXT_CHN_ATTR_S stExtChnAttr;
    VI_CHN ExtChn = 1;
    PIC_SIZE_E enPicSize = g_enPicSize;

    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 8;

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, PIC_D1,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[1].u32BlkCnt = 8;


    /******************************************
     step 2: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 3: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }

    stExtChnAttr.enPixFormat = SAMPLE_PIXEL_FORMAT;
    stExtChnAttr.s32BindChn = ViChn;
    stExtChnAttr.stDestSize.u32Width = 720;
    stExtChnAttr.stDestSize.u32Height = 576;
    stExtChnAttr.s32DstFrameRate = -1;
    stExtChnAttr.s32SrcFrameRate = -1;

    s32Ret = HI_MPI_VI_SetExtChnAttr(ExtChn, &stExtChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("HI_MPI_VI_SetExtChnAttr failed!\n");
        goto END_1080P_0;
    }
    s32Ret = HI_MPI_VI_EnableChn(ExtChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("HI_MPI_VI_EnableChn failed!\n");
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_1;
    }

    /******************************************
    step 5: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_720P50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;
    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDevLayer failed!\n");
        goto END_1080P_1;
    }

    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_2;
    }

    s32Ret = SAMPLE_COMM_VO_BindVi(VoDev, VoChn, ExtChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVi(vo:%d)-(vichn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_3;
    }

    VI_PAUSE();
    /******************************************
     step 6: exit process
    ******************************************/
END_1080P_3:
    SAMPLE_COMM_VO_UnBindVi(VoDev, VoChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_2:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_1:
    s32Ret = HI_MPI_VI_DisableChn(ExtChn);
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();

    return s32Ret;
}

/******************************************************************************************************
* function :  VI: DC(720P); VO: SD0(CVBS). Embeded isp,  linear/wdr change, phychn channel preview.
******************************************************************************************************/
HI_S32 SAMPLE_VIO_720P_SensorModeChange_Preview(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VI_CHN ViChn = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32GetC;
    HI_U8 u8Mode;
    HI_U32 u32BlkSize;
    SIZE_S stSize;
    ROTATE_E enRotate = ROTATE_NONE;

    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 8;

    /******************************************
     step 2: start vpss and vi bind vpss (subchn needn't bind vpss in this mode)
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_1080P_1;
    }

    if (pstViConfig)
    {
        enRotate = pstViConfig->enRotate;
        if (ROTATE_90 == enRotate || ROTATE_270 == enRotate)
        {
            u32BlkSize = (CEILING_2_POWER(stSize.u32Width, SAMPLE_SYS_ALIGN_WIDTH) * \
                          CEILING_2_POWER(stSize.u32Height, SAMPLE_SYS_ALIGN_WIDTH) * \
                          ((PIXEL_FORMAT_YUV_SEMIPLANAR_422 == SAMPLE_PIXEL_FORMAT) ? 2 : 1.5));
            stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
            stVbConf.astCommPool[1].u32BlkCnt = 8;
        }
    }

    /******************************************
     step 3: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }

    /******************************************
    step 5: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_720P50;
        gs_u32ViFrmRate = 50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;

    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDevLayer failed!\n");
        goto END_1080P_1;
    }

    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_2;
    }

    s32Ret = SAMPLE_COMM_VO_BindVi(VoDev, VoChn, ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVi(vo:%d)-(vichn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_3;
    }

    printf("---------quit(q)/linear(l)/wdr(w)---------\n");
    while ((s32GetC = (char)getchar()) != 'q')
    {
        if ('l' == s32GetC)
        {
            u8Mode = 0;
        }
        else if ('w' == s32GetC)
        {
            u8Mode = 1;
        }
        else
        {
            continue;
        }

        s32Ret = SAMPLE_COMM_ISP_ChangeSensorMode(u8Mode);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("SAMPLE_COMM_ISP_ChangeSensorMode failed!\n");
            break;
        }
    }


    /******************************************
     step 6: exit process
    ******************************************/
END_1080P_3:
    SAMPLE_COMM_VO_UnBindVi(VoDev, VoChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_2:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();

    return s32Ret;
}

HI_S32 SAMLE_VIO_ResolutionSwitch_Preview(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_U32 u32ViChnCnt = 2;
    VB_CONF_S stVbConf;
    VO_DEV VoDev = SAMPLE_VO_DEV_DSD0;;
    VO_CHN VoChn = 0;
    VI_DEV ViDev = 0;
    VI_CHN ViChn = 0;
    ISP_DEV IspDev = 0;
    VO_PUB_ATTR_S stVoPubAttr;
    ISP_INNER_STATE_INFO_S stInnerStateInfo;

    SIZE_S stTargetSize;
    RECT_S stCapRect;

    SAMPLE_VO_MODE_E enVoMode = VO_MODE_1MUX;
    PIC_SIZE_E enPicSize = g_enPicSize;
    VO_LAYER VoLayer = 0;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;
    ISP_PUB_ATTR_S stPubAttr;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32BlkSize;

    if ( PANASONIC_MN34220_SUBLVDS_1080P_30FPS == pstViConfig->enViMode
         || PANASONIC_MN34220_SUBLVDS_720P_120FPS == pstViConfig->enViMode
         || PANASONIC_MN34220_MIPI_1080P_30FPS == pstViConfig->enViMode
         || PANASONIC_MN34220_MIPI_720P_120FPS == pstViConfig->enViMode
         || SONY_IMX117_LVDS_1080P_30FPS == pstViConfig->enViMode 
         || SONY_IMX117_LVDS_720P_30FPS == pstViConfig->enViMode )
    {
        enPicSize = PIC_HD1080;
    }
    else if ( OMNIVISION_OV4689_MIPI_4M_30FPS == pstViConfig->enViMode
              || OMNIVISION_OV4689_MIPI_1080P_30FPS == pstViConfig->enViMode )
    {
        enPicSize = PIC_2592x1520;
    }
    else
    {
        SAMPLE_PRT("Not support this sensor type!\n");
        goto END_1080P;
    }

    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, enPicSize,
                 SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    /*ddr0 video buffer*/
    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt = u32ViChnCnt * 8;

    /******************************************
     step 3: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_1080P_0;
    }

    /******************************************
     step 4: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_1080P_0;
    }

    /******************************************
    step 5: start VO SD0 (bind * vi )
    ******************************************/
    stVoPubAttr.enIntfType = g_enVoIntfType;
    if (VO_INTF_BT1120 == g_enVoIntfType)
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_1080P30;
        gs_u32ViFrmRate = 50;
    }
    else
    {
        stVoPubAttr.enIntfSync = VO_OUTPUT_PAL;
    }
    stVoPubAttr.u32BgColor = 0x000000ff;

    /* In HD, this item should be set to HI_FALSE */
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDev failed!\n");
        goto END_1080P_1;
    }

    stLayerAttr.bClusterMode = HI_FALSE;
    stLayerAttr.bDoubleFrame = HI_FALSE;
    stLayerAttr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    stLayerAttr.stDispRect.s32X = 0;
    stLayerAttr.stDispRect.s32Y = 0;

    s32Ret = SAMPLE_COMM_VO_GetWH(stVoPubAttr.enIntfSync,
                                  &stLayerAttr.stDispRect.u32Width, &stLayerAttr.stDispRect.u32Height,
                                  &stLayerAttr.u32DispFrmRt);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_GetWH failed!\n");
        goto END_1080P_1;
    }

    stLayerAttr.stImageSize.u32Width  = stLayerAttr.stDispRect.u32Width;
    stLayerAttr.stImageSize.u32Height = stLayerAttr.stDispRect.u32Height;

    s32Ret = SAMPLE_COMM_VO_StartLayer(VoLayer, &stLayerAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1080P_2;
    }
    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1080P_3;
    }

    //s32Ret = SAMPLE_COMM_VO_BindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    s32Ret = SAMPLE_COMM_VO_BindVi(VoDev, VoChn, ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVpss(vo:%d)-(VpssChn:%d) failed with %#x!\n", VoDev, VoChn, s32Ret);
        goto END_1080P_4;
    }

    VI_PAUSE();

    s32Ret = HI_MPI_ISP_GetPubAttr(IspDev, &stPubAttr);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }

    SAMPLE_COMM_VI_SwitchResParam(pstViConfig, &stPubAttr, &stCapRect);

    s32Ret = HI_MPI_VI_DisableChn(ViChn);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }
    s32Ret = HI_MPI_VI_DisableDev(ViDev);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }
    s32Ret = SAMPLE_COMM_VI_StartMIPI(pstViConfig);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }

    s32Ret = HI_MPI_ISP_SetPubAttr(IspDev, &stPubAttr);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }
    while (1)
    {
        HI_MPI_ISP_QueryInnerStateInfo(IspDev, &stInnerStateInfo);
        if (HI_TRUE == stInnerStateInfo.bResSwitchFinish)
        {
            SAMPLE_PRT("Res switch finish!\n");
            break;
        }
        usleep(1000);
    }

    s32Ret = SAMPLE_COMM_VI_StartDev(ViDev, pstViConfig->enViMode);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }

    stTargetSize.u32Width = stCapRect.u32Width;
    stTargetSize.u32Height = stCapRect.u32Height;
    s32Ret = SAMPLE_COMM_VI_StartChn(ViChn, &stCapRect, &stTargetSize, pstViConfig);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }


    VI_PAUSE();
    s32Ret = HI_MPI_ISP_GetPubAttr(IspDev, &stPubAttr);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }

    SAMPLE_COMM_VI_SwitchResParam(pstViConfig, &stPubAttr, &stCapRect);

    s32Ret = HI_MPI_VI_DisableChn(ViChn);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }
    s32Ret = HI_MPI_VI_DisableDev(ViDev);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }
    s32Ret = SAMPLE_COMM_VI_StartMIPI(pstViConfig);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }
    s32Ret = HI_MPI_ISP_SetPubAttr(IspDev, &stPubAttr);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }

    while (1)
    {
        HI_MPI_ISP_QueryInnerStateInfo(IspDev, &stInnerStateInfo);
        if (HI_TRUE == stInnerStateInfo.bResSwitchFinish)
        {
            SAMPLE_PRT("Res switch finish!\n");
            break;
        }
        usleep(1000);
    }

    s32Ret = SAMPLE_COMM_VI_StartDev(ViDev, pstViConfig->enViMode);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }

    stTargetSize.u32Width = stCapRect.u32Width;
    stTargetSize.u32Height = stCapRect.u32Height;
    s32Ret = SAMPLE_COMM_VI_StartChn(ViChn, &stCapRect, &stTargetSize, pstViConfig);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        goto END_1080P_4;
    }
    VI_PAUSE();

    /******************************************
     step 8: exit process
    ******************************************/
END_1080P_4:
    SAMPLE_COMM_VO_UnBindVi(VoDev, VoChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
END_1080P_3:
    SAMPLE_COMM_VO_StopLayer(VoLayer);
END_1080P_2:
    SAMPLE_COMM_VO_StopDev(VoDev);
END_1080P_1:
    SAMPLE_COMM_VI_StopVi(pstViConfig);
END_1080P_0:
    SAMPLE_COMM_SYS_Exit();
END_1080P:
    return s32Ret;
}

/******************************************************************************
* function    : main()
* Description : video preview sample
******************************************************************************/
int main(int argc, char* argv[])
{
    HI_S32 s32Ret = HI_FAILURE;

    if ( (argc < 2) || (1 != strlen(argv[1])))
    {
        SAMPLE_VIO_Usage(argv[0]);
        return HI_FAILURE;
    }

    signal(SIGINT, SAMPLE_VIO_HandleSig);
    signal(SIGTERM, SAMPLE_VIO_HandleSig);

    if ((argc > 2) && *argv[2] == '1')  /* '1': VO_INTF_CVBS, else: BT1120 */
    {
        g_enVoIntfType = VO_INTF_BT1120;
    }

    g_stViChnConfig.enViMode = SENSOR_TYPE;
    SAMPLE_COMM_VI_GetSizeBySensor(&g_enPicSize);

    switch (*argv[1])
    {
            /* VI: DC(720P); VO: SD0(CVBS). Embeded isp, phychn channel preview. */
        case '0':
            s32Ret = SAMPLE_VIO_1080P_PreView(&g_stViChnConfig);
            break;

        case '1':
            if ((SENSOR_TYPE == PANASONIC_MN34220_SUBLVDS_1080P_30FPS)
                || (SENSOR_TYPE == PANASONIC_MN34220_SUBLVDS_720P_120FPS)
                || (SENSOR_TYPE == PANASONIC_MN34220_MIPI_1080P_30FPS)
                || (SENSOR_TYPE == PANASONIC_MN34220_MIPI_720P_120FPS)
                || (SENSOR_TYPE == SONY_IMX123_LVDS_QXGA_30FPS)
                || (SENSOR_TYPE == APTINA_AR0237_HISPI_1080P_30FPS))
            {
                g_stViChnConfig.enWDRMode = WDR_MODE_2To1_LINE;
            }
            else
            {
                g_stViChnConfig.enWDRMode = WDR_MODE_2To1_FRAME;
            }
            s32Ret = SAMPLE_VIO_LINE_WDR_PreView(&g_stViChnConfig);
            break;

        case '2':
            s32Ret = SAMPLE_VIO_FRAME_FPN_PreView(&g_stViChnConfig);
            break;

        case '3':
            s32Ret = SAMPLE_VI_VPSS_LDC_VO_1080P_PreView(&g_stViChnConfig);
            break;
        case '4':
            s32Ret = SAMPLE_VI_VPSS_ROTATE_VO_1080P_PreView(&g_stViChnConfig);
            break;
        case '5':
            g_stViChnConfig.enRotate = ROTATE_90;
            s32Ret = SAMPLE_VI_ROTATE_VO_1080P_PreView(&g_stViChnConfig);
            break;
        case '6':
            s32Ret = SAMPLE_VI_LDC_VO_1080P_PreView(&g_stViChnConfig);
            break;
        case '7':
            s32Ret = SAMPLE_VI_DIS_VPSS_VO_1080P_PreView(&g_stViChnConfig);
            break;

            /* VI: BT1120(1080I); VO:HD0(HDMI).  Isp bypass, phychn channel preview. */
        case '8':
            g_stViChnConfig.enViMode = SAMPLE_VI_MODE_BT1120_1080P;
            g_stViChnConfig.enNorm = VIDEO_ENCODING_MODE_PAL;
            s32Ret = SAMPLE_VIO_BT1120_1080P_PreView(&g_stViChnConfig);
            break;
        case '9':
            s32Ret = SAMLE_VIO_ResolutionSwitch_Preview(&g_stViChnConfig);
            break;
        default:
            SAMPLE_PRT("the index is invaild!\n");
            SAMPLE_VIO_Usage(argv[0]);
            return HI_FAILURE;
    }

    if (HI_SUCCESS == s32Ret)
    {
        SAMPLE_PRT("program exit normally!\n");
    }
    else
    {
        SAMPLE_PRT("program exit abnormally!\n");
    }
    exit(s32Ret);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

