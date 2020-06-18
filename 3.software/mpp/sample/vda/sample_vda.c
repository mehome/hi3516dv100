/******************************************************************************
  A simple program of Hisilicon Hi35xx vda implementation.
  the flow as follows:
    1) init mpp system.
    2) start vi( internal isp, ViDev 0, vichn0) and vo (HD)
    3) vda md & od start & print information
    4) stop vi vo and system.
  Copyright (C), 2010-2011, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
    Modification:  2011-2 Created
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

#include "sample_comm.h"
#include "loadbmp.h"

VIDEO_NORM_E gs_enNorm = VIDEO_ENCODING_MODE_PAL;
VO_INTF_TYPE_E  g_enVoIntfType = VO_INTF_CVBS;

SAMPLE_VI_CONFIG_S g_stViChnConfig =
{
    PANASONIC_MN34220_SUBLVDS_1080P_30FPS,
    VIDEO_ENCODING_MODE_AUTO,
    ROTATE_NONE,
    VI_CHN_SET_NORMAL,
    WDR_MODE_NONE
};
HI_U32    gs_u32ViFrmRate = 0;

/******************************************************************************
* function : to init vo parameters
******************************************************************************/
HI_S32 SAMPLE_VDA_GetVoAttr(VO_DEV VoDev, VO_INTF_SYNC_E enIntfSync, VO_PUB_ATTR_S* pstPubAttr,
                            VO_VIDEO_LAYER_ATTR_S* pstLayerAttr, HI_S32 s32SquareSort, VO_CHN_ATTR_S* astChnAttr)
{
    VO_INTF_TYPE_E enIntfType;
    HI_U32 /*u32Frmt, */u32Width, u32Height, j;
#if defined(CHIP_TYPE_hi3521v100) || defined(CHIP_TYPE_hi3520Dv100)
    switch (VoDev)
    {
        case 0:
            enIntfType = VO_INTF_VGA | VO_INTF_HDMI;
            break;
        case 1:
            enIntfType = VO_INTF_CVBS;
            break;
        case 2:
            enIntfType = VO_INTF_CVBS;
            break;
    }
#elif defined(CHIP_TYPE_hi3535v100)
    switch (VoDev)
    {
        case 0:
            enIntfType = VO_INTF_BT1120 | VO_INTF_HDMI;
            break;
        case 1:
            enIntfType = VO_INTF_BT1120;
            break;
        case 2:
            enIntfType = VO_INTF_CVBS;
            break;
        case 3:
            enIntfType = VO_INTF_CVBS;
            break;
    }
#elif defined(CHIP_TYPE_hi3516av100)
    enIntfType = VO_INTF_CVBS;
#endif
    enIntfType =  VO_INTF_BT1120;

    switch (enIntfSync)
    {
        case VO_OUTPUT_PAL      :
            u32Width = 720;
            u32Height = 576;  /*u32Frmt = 25;*/ break;
        case VO_OUTPUT_NTSC     :
            u32Width = 720;
            u32Height = 480;  /*u32Frmt = 30;*/ break;
        case VO_OUTPUT_1080P24  :
            u32Width = 1920;
            u32Height = 1080;/* u32Frmt = 24; */break;
        case VO_OUTPUT_1080P25  :
            u32Width = 1920;
            u32Height = 1080; /*u32Frmt = 25; */break;
        case VO_OUTPUT_1080P30  :
            u32Width = 1920;
            u32Height = 1080;/* u32Frmt = 30; */break;
        case VO_OUTPUT_720P50   :
            u32Width = 1280;
            u32Height = 720;  /*u32Frmt = 50;*/ break;
        case VO_OUTPUT_720P60   :
            u32Width = 1280;
            u32Height = 720;  /*u32Frmt = 60;*/ break;
        case VO_OUTPUT_1080I50  :
            u32Width = 1920;
            u32Height = 1080;/* u32Frmt = 50; */break;
        case VO_OUTPUT_1080I60  :
            u32Width = 1920;
            u32Height = 1080; /*u32Frmt = 60;*/ break;
        case VO_OUTPUT_1080P50  :
            u32Width = 1920;
            u32Height = 1080; /*u32Frmt = 50;*/ break;
        case VO_OUTPUT_1080P60  :
            u32Width = 1920;
            u32Height = 1080; /*u32Frmt = 60; */break;
        case VO_OUTPUT_576P50   :
            u32Width = 720;
            u32Height = 576;  /*u32Frmt = 50; */break;
        case VO_OUTPUT_480P60   :
            u32Width = 720;
            u32Height = 480;  /*u32Frmt = 60; */break;
        case VO_OUTPUT_800x600_60:
            u32Width = 800;
            u32Height = 600; /* u32Frmt = 60;*/ break;
        case VO_OUTPUT_1024x768_60:
            u32Width = 1024;
            u32Height = 768;  /*u32Frmt = 60;*/ break;
        case VO_OUTPUT_1280x1024_60:
            u32Width = 1280;
            u32Height = 1024; /*u32Frmt = 60;*/ break;
        case VO_OUTPUT_1366x768_60:
            u32Width = 1366;
            u32Height = 768;  /*u32Frmt = 60; */break;
        case VO_OUTPUT_1440x900_60:
            u32Width = 1440;
            u32Height = 900;  /*u32Frmt = 60;*/ break;
        case VO_OUTPUT_1280x800_60:
            u32Width = 1280;
            u32Height = 800;  /*u32Frmt = 60;*/ break;

        default:
            return HI_FAILURE;
    }
    //  printf();
    if (NULL != pstPubAttr)
    {
        pstPubAttr->enIntfSync = enIntfSync;
        pstPubAttr->u32BgColor = 0; //0xFF; //BLUE
        //pstPubAttr->bDoubleFrame = HI_FALSE;
        pstPubAttr->enIntfType = enIntfType;
    }

    if (NULL != pstLayerAttr)
    {
        pstLayerAttr->stDispRect.s32X       = 0;
        pstLayerAttr->stDispRect.s32Y       = 0;
        pstLayerAttr->stDispRect.u32Width   = u32Width;
        pstLayerAttr->stDispRect.u32Height  = u32Height;
        pstLayerAttr->stImageSize.u32Width  = u32Width;
        pstLayerAttr->stImageSize.u32Height = u32Height;
        //pstLayerAttr->u32DispFrmRt          = u32Frmt;
        pstLayerAttr->bDoubleFrame          = HI_FALSE;
        pstLayerAttr->u32DispFrmRt          = 25;
        pstLayerAttr->enPixFormat           = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
        pstLayerAttr->bClusterMode = HI_FALSE;
    }

    if (NULL != astChnAttr)
    {
        for (j = 0; j < (s32SquareSort * s32SquareSort); j++)
        {
            astChnAttr[j].stRect.s32X       = ALIGN_BACK((u32Width / s32SquareSort) * (j % s32SquareSort), 4);
            astChnAttr[j].stRect.s32Y       = ALIGN_BACK((u32Height / s32SquareSort) * (j / s32SquareSort), 4);
            astChnAttr[j].stRect.u32Width   = ALIGN_BACK(u32Width / s32SquareSort, 4);
            astChnAttr[j].stRect.u32Height  = ALIGN_BACK(u32Height / s32SquareSort, 4);
            astChnAttr[j].u32Priority       = 0;
            astChnAttr[j].bDeflicker        = HI_FALSE;
        }
    }

    return HI_SUCCESS;
}

/******************************************************************************
* function : to process abnormal case
******************************************************************************/
void SAMPLE_VDA_HandleSig(HI_S32 signo)
{
    if (SIGINT == signo || SIGTERM == signo)
    {
        SAMPLE_COMM_ISP_Stop();
        SAMPLE_COMM_SYS_Exit();
        printf("\033[0;31mprogram exit abnormally!\033[0;39m\n");
    }

    exit(0);
}
/******************************************************************************
* function : show usage
******************************************************************************/
void SAMPLE_VDA_Usage(char* sPrgNm)
{
    printf("Usage : %s <index>\n", sPrgNm);
    printf("index:\n");
    printf("\t 0) MD.(QVGA)\n");
    printf("\t 1) OD.(QVGA)\n");
    return;
}

/******************************************************************************
* function      : main()
* Description : Vi/VO + VDA(MD&OD)
*               DC -> VI-PortA ViChn0(1080p)
*                              ViChn1(VGA)    -> VdaChn0 MD
*                                            	  -> VdaChn1 OD
*								 ->VO (CVBS D1)
******************************************************************************/
HI_S32 SAMPLE_Vda_QVGA(HI_BOOL bVdaMd)
{
    HI_S32 s32Ret = HI_SUCCESS;
    VI_CHN ViChn_Md , ViChn_Od ;
    VDA_CHN VdaChn_Md = 0, VdaChn_Od = 1;
    VB_CONF_S stVbConf = {0};	/* vb config define */
    PIC_SIZE_E enSize_Md = PIC_QVGA, enSize_Od = PIC_QVGA; 	/* vda picture size */

    //VI_CHN ViExtChn = 1;
    //VI_EXT_CHN_ATTR_S stViExtChnAttr;

    VPSS_GRP VpssGrp;
    VPSS_CHN VpssChn;
    VPSS_GRP_ATTR_S stVpssGrpAttr;
    VPSS_CHN_ATTR_S stVpssChnAttr;
    VPSS_CHN_MODE_S stVpssMode = {VPSS_CHN_MODE_USER, 1920, 1080, HI_FALSE, PIXEL_FORMAT_YUV_SEMIPLANAR_420};

    VO_DEV VoDev;
    VO_CHN VoChn;
    VO_PUB_ATTR_S stVoPubAttr;
    SAMPLE_VO_MODE_E enVoMode;
    VO_VIDEO_LAYER_ATTR_S stLayerAttr;
    VO_CHN_ATTR_S astChnAttr[16];

    HI_U32 u32BlkSize;
    SIZE_S stSize;
    PIC_SIZE_E enPicSize = PIC_HD1080;

    /******************************************
     step  1: init global  variable
    ******************************************/
    gs_u32ViFrmRate = (VIDEO_ENCODING_MODE_PAL == gs_enNorm) ? 25 : 30;
    g_stViChnConfig.enViMode = SENSOR_TYPE;

    SAMPLE_COMM_VI_GetSizeBySensor(&enPicSize);

    memset(&stVbConf, 0, sizeof(VB_CONF_S));

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, \
                 enPicSize, SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.u32MaxPoolCnt = 128;

    stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[0].u32BlkCnt  =  10;

    u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(gs_enNorm, \
                 PIC_QVGA, SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
    stVbConf.astCommPool[1].u32BlkSize = u32BlkSize;
    stVbConf.astCommPool[1].u32BlkCnt  = 10;

    /******************************************
     step 2: mpp system init.
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("system init failed with %d!\n", s32Ret);
        goto END_0;
    }

    /******************************************
     step 3: start vi dev & chn to capture
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartVi(&g_stViChnConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("start vi failed!\n");
        goto END_0;
    }

    /******************************************
     step 4: start vpss and vi bind vpss
    ******************************************/
    s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enPicSize, &stSize);
    printf("\nstSize's width is %d, heigh is %d!!!\n", stSize.u32Width, stSize.u32Height);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
        goto END_2;
    }

    VpssGrp = 0;
    stVpssGrpAttr.u32MaxW   = stSize.u32Width;
    stVpssGrpAttr.u32MaxH   = stSize.u32Height;
    stVpssGrpAttr.bIeEn     = HI_FALSE;
    stVpssGrpAttr.bNrEn     = HI_FALSE;
    stVpssGrpAttr.bHistEn   = HI_FALSE;
    stVpssGrpAttr.bDciEn    = HI_FALSE;
    stVpssGrpAttr.enDieMode = VPSS_DIE_MODE_NODIE;
    stVpssGrpAttr.enPixFmt  = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

    s32Ret = SAMPLE_COMM_VPSS_StartGroup(VpssGrp, &stVpssGrpAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("Start Vpss failed!\n");
        goto END_2;
    }

    s32Ret = SAMPLE_COMM_VI_BindVpss(g_stViChnConfig.enViMode);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("Vi bind Vpss failed!\n");
        goto END_2;
    }


    VpssChn = 0;
    memset(&stVpssChnAttr, 0, sizeof(stVpssChnAttr));
    stVpssChnAttr.s32SrcFrameRate = -1;
    stVpssChnAttr.s32DstFrameRate = -1;
    stVpssMode.u32Width  = stSize.u32Width;
    stVpssMode.u32Height = stSize.u32Height;
    s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, &stVpssChnAttr, &stVpssMode, HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("Enable vpss chn failed!\n");
        goto END_2;
    }
    /******************************************
         step 5: start VO to preview
    ******************************************/
    VoDev = SAMPLE_VO_DEV_DSD0;
    VoChn  = 0;
    enVoMode = VO_MODE_1MUX;

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

    //printf("\nbreak 1!!!\n");
    //getchar();
    SAMPLE_VDA_GetVoAttr(VoDev, VO_OUTPUT_1080P30, &stVoPubAttr,
                         &stLayerAttr, 1, astChnAttr);

    //printf("\nbreak 2!!!\n");
    //getchar();
    s32Ret = SAMPLE_COMM_VO_StartDev(VoDev, &stVoPubAttr);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartDevLayer failed!\n");
        goto END_1;
    }
    //printf("\nbreak 3!!!\n");
    //getchar();
    s32Ret = SAMPLE_COMM_VO_StartLayer(VoDev, &stLayerAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed!\n");
        goto END_1;
    }
    //printf("\nbreak 4!!!\n");
    //getchar();
    s32Ret = SAMPLE_COMM_VO_StartChn(VoDev, VO_MODE_1MUX);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed!\n");
        goto END_1;
    }
    //printf("\nbreak 5!!!\n");
    //getchar();
    s32Ret = SAMPLE_COMM_VO_BindVpss(VoDev, VoChn, VpssGrp, VpssChn);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VO_BindVpss failed!\n");
        goto END_1;
    }
    //printf("\nbreak 6!!!\n");
    //getchar();

    /******************************************
     step  5: VDA process
    ******************************************/
    sleep(2);

    if (HI_TRUE == bVdaMd)
    {
        s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enSize_Md, &stSize);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
            goto END_3;
        }
        ViChn_Md = VpssChn;
        s32Ret = SAMPLE_COMM_VDA_MdStart(VdaChn_Md, ViChn_Md, &stSize);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("VDA Md Start failed!\n");
            goto END_3;
        }

        printf("Press the Enter key to stop!\n");
        getchar();
        SAMPLE_COMM_VDA_MdStop(VdaChn_Md, ViChn_Md);
    }
    else
    {
        s32Ret = SAMPLE_COMM_SYS_GetPicSize(gs_enNorm, enSize_Od, &stSize);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("SAMPLE_COMM_SYS_GetPicSize failed!\n");
            goto END_3;
        }
        ViChn_Od = VpssChn;
        s32Ret = SAMPLE_COMM_VDA_OdStart(VdaChn_Od, ViChn_Od, &stSize);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("VDA OD Start failed!\n");
            goto END_3;
        }

        printf("Press the Enter key to stop!\n");
        getchar();
        SAMPLE_COMM_VDA_OdStop(VdaChn_Od, ViChn_Od);
    }

    /******************************************
     step 6: exit process
    ******************************************/

END_3:    // vo unbind and stop
    SAMPLE_COMM_VO_UnBindVi(VoDev, VoChn);
    SAMPLE_COMM_VO_StopChn(VoDev, enVoMode);
    SAMPLE_COMM_VO_StopLayer(VoDev);
    SAMPLE_COMM_VO_StopDev(VoDev);
END_2:    //vpss stop
    VpssGrp = 0;
    VpssChn = 0;
    SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);
    SAMPLE_COMM_VI_UnBindVpss(g_stViChnConfig.enViMode);
    SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
END_1:    // vi stop
    HI_MPI_VI_DisableChn(0);
    SAMPLE_COMM_VI_StopVi(&g_stViChnConfig);
END_0:    // system exit
    SAMPLE_COMM_SYS_Exit();

    return s32Ret;
}

/******************************************************************************
* function    : main()
* Description : video preview sample
******************************************************************************/
int main(int argc, char* argv[])
{
    HI_S32 s32Ret;

    if ( (argc < 2) || (1 != strlen(argv[1])))
    {
        SAMPLE_VDA_Usage(argv[0]);
        return HI_FAILURE;
    }

    signal(SIGINT, SAMPLE_VDA_HandleSig);
    signal(SIGTERM, SAMPLE_VDA_HandleSig);

    switch (*argv[1])
    {
        case '0': /* QVGA MD  */
            s32Ret = SAMPLE_Vda_QVGA(HI_TRUE);
            break;
        case '1': /* QVGA OD  */
            s32Ret = SAMPLE_Vda_QVGA(HI_FALSE);
            break;
        default:
            SAMPLE_VDA_Usage(argv[0]);
            return HI_FAILURE;
    }

    if (HI_SUCCESS == s32Ret)
    { printf("program exit normally!\n"); }
    else
    { printf("program exit abnormally!\n"); }
    exit(s32Ret);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
