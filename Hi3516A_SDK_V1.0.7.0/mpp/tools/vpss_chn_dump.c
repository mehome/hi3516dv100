#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "hi_common.h"
#include "hi_comm_video.h"
#include "hi_comm_sys.h"
#include "mpi_sys.h"
#include "hi_comm_vb.h"
#include "mpi_vb.h"
#include "hi_comm_vpss.h"
#include "mpi_vpss.h"
#include "mpi_vgs.h"

#define MAX_FRM_WIDTH   4608

#define VALUE_BETWEEN(x,min,max) (((x)>=(min)) && ((x) <= (max)))

typedef struct hiDUMP_MEMBUF_S
{
    VB_BLK  hBlock;
    VB_POOL hPool;
    HI_U32  u32PoolId;

    HI_U32  u32PhyAddr;
    HI_U8*   pVirAddr;
    HI_S32  s32Mdev;
} DUMP_MEMBUF_S;

static HI_U32 u32VpssDepthFlag = 0;
static HI_U32 u32SignalFlag = 0;

static VPSS_GRP VpssGrp = 0;
static VPSS_CHN VpssChn = 0;
static HI_U32 u32OrigDepth = 0;

#define MAX_FRM_CNT             1024
static VIDEO_FRAME_INFO_S stFrame;
static VIDEO_FRAME_INFO_S astFrame[MAX_FRM_CNT];

static VB_POOL hPool  = VB_INVALID_POOLID;
static DUMP_MEMBUF_S stMem = {0};
static VGS_HANDLE hHandle = -1;
static HI_U32  u32BlkSize = 0;

static HI_CHAR* pUserPageAddr[2] = {HI_NULL,HI_NULL};
static HI_U32 u32Size = 0;

static FILE* pfd = HI_NULL;



/*When saving a file,sp420 will be denoted by p420 and sp422 will be denoted by p422 in the name of the file */
void sample_yuv_dump(VIDEO_FRAME_S* pVBuf, FILE* pfd)
{
    unsigned int w, h;
    char* pVBufVirt_Y;
    char* pVBufVirt_C;
    char* pMemContent;
    unsigned char TmpBuff[MAX_FRM_WIDTH];                //If this value is too small and the image is big, this memory may not be enough
    													
    HI_U32 phy_addr;
    PIXEL_FORMAT_E  enPixelFormat = pVBuf->enPixelFormat;
    HI_U32 u32UvHeight;/*When the storage format is a planar format, this variable is used to keep the height of the UV component */

    if (PIXEL_FORMAT_YUV_SEMIPLANAR_420 == enPixelFormat)
    {
        u32Size = (pVBuf->u32Stride[0]) * (pVBuf->u32Height) * 3 / 2;
        u32UvHeight = pVBuf->u32Height / 2;
    }
    else if(PIXEL_FORMAT_YUV_SEMIPLANAR_422 == enPixelFormat)
    {
        u32Size = (pVBuf->u32Stride[0]) * (pVBuf->u32Height) * 2;
        u32UvHeight = pVBuf->u32Height;
    }
    else if(PIXEL_FORMAT_YUV_400 == enPixelFormat)
    {
        u32Size = (pVBuf->u32Stride[0]) * (pVBuf->u32Height);
        u32UvHeight = pVBuf->u32Height;
    }

    phy_addr = pVBuf->u32PhyAddr[0];

    //printf("phy_addr:%x, size:%d\n", phy_addr, size);
    pUserPageAddr[0] = (HI_CHAR*) HI_MPI_SYS_Mmap(phy_addr, u32Size);
    if (HI_NULL == pUserPageAddr[0])
    {
        return;
    }
    //printf("stride: %d,%d\n",pVBuf->u32Stride[0],pVBuf->u32Stride[1] );

    pVBufVirt_Y = pUserPageAddr[0];
    pVBufVirt_C = pVBufVirt_Y + (pVBuf->u32Stride[0]) * (pVBuf->u32Height);

    /* save Y ----------------------------------------------------------------*/
    fprintf(stderr, "saving......Y......");
    fflush(stderr);
    for (h = 0; h < pVBuf->u32Height; h++)
    {
        pMemContent = pVBufVirt_Y + h * pVBuf->u32Stride[0];
        fwrite(pMemContent, pVBuf->u32Width, 1, pfd);
    }

    if(PIXEL_FORMAT_YUV_400 != enPixelFormat)
    {
        fflush(pfd);
        /* save U ----------------------------------------------------------------*/
        fprintf(stderr, "U......");
        fflush(stderr);
    
        for (h = 0; h < u32UvHeight; h++)
        {
            pMemContent = pVBufVirt_C + h * pVBuf->u32Stride[1];

            pMemContent += 1;

            for (w = 0; w < pVBuf->u32Width / 2; w++)
            {
                TmpBuff[w] = *pMemContent;
                pMemContent += 2;
            }
            fwrite(TmpBuff, pVBuf->u32Width / 2, 1, pfd);
        }
        fflush(pfd);

        /* save V ----------------------------------------------------------------*/
        fprintf(stderr, "V......");
        fflush(stderr);
        for (h = 0; h < u32UvHeight; h++)
        {
            pMemContent = pVBufVirt_C + h * pVBuf->u32Stride[1];

            for (w = 0; w < pVBuf->u32Width / 2; w++)
            {
                TmpBuff[w] = *pMemContent;
                pMemContent += 2;
            }
            fwrite(TmpBuff, pVBuf->u32Width / 2, 1, pfd);
        }
    }
    fflush(pfd);

    fprintf(stderr, "done %d, 0x%x!\n", pVBuf->u32TimeRef, pVBuf->u32PhyAddr[0]);
    fflush(stderr);

    HI_MPI_SYS_Munmap(pUserPageAddr[0], u32Size);
    pUserPageAddr[0] = HI_NULL;
}

HI_S32 VPSS_Restore(VPSS_GRP VpssGrp, VPSS_CHN VpssChn)
{
    if(VB_INVALID_POOLID != stFrame.u32PoolId)
    {
        HI_MPI_VPSS_ReleaseChnFrame(VpssGrp, VpssChn, &stFrame);
        stFrame.u32PoolId = VB_INVALID_POOLID;
    }
    if(-1 != hHandle)
    {
        HI_MPI_VGS_CancelJob(hHandle);
        hHandle = -1;
    }   
    if(HI_NULL != stMem.pVirAddr)
    {
        HI_MPI_SYS_Munmap((HI_VOID*)stMem.pVirAddr, u32BlkSize );
        stMem.u32PhyAddr = HI_NULL;
    }
    if(VB_INVALID_POOLID != stMem.hPool)
    {
        HI_MPI_VB_ReleaseBlock(stMem.hBlock);
        stMem.hPool = VB_INVALID_POOLID;
    }

    if (VB_INVALID_POOLID != hPool)
    {
        HI_MPI_VB_DestroyPool( hPool );
        hPool = VB_INVALID_POOLID;
    }

    if(HI_NULL != pUserPageAddr[0])
    {
        HI_MPI_SYS_Munmap(pUserPageAddr[0], u32Size);
        pUserPageAddr[0] = HI_NULL;
    }
    
    if(pfd)
    {
        fclose(pfd);
        pfd = HI_NULL;
    }

    if(u32VpssDepthFlag)
    {
        if (HI_MPI_VPSS_SetDepth(VpssGrp, VpssChn, u32OrigDepth) != HI_SUCCESS)
        {
            printf("set depth error!!!\n");
        }
        u32VpssDepthFlag = 0;
    }

    return HI_SUCCESS;
}

void VPSS_Chn_Dump_HandleSig(HI_S32 signo)
{
    if(u32SignalFlag)
    {
        exit(-1);
    }
    
    if (SIGINT == signo || SIGTERM == signo)
    {
        u32SignalFlag++;
        VPSS_Restore(VpssGrp, VpssChn);
        u32SignalFlag--;
        printf("\033[0;31mprogram termination abnormally!\033[0;39m\n");
    }
    exit(-1);
}


HI_VOID* SAMPLE_MISC_VpssDump(VPSS_GRP Grp, VPSS_CHN Chn, HI_U32 u32FrameCnt)
{
    HI_CHAR szYuvName[128];
    HI_CHAR szPixFrm[10];
    HI_U32 u32Cnt = u32FrameCnt;
    HI_U32 u32Depth = 2;
    HI_S32 s32MilliSec = 200;
    HI_S32 s32Times = 10;
    HI_BOOL bSendToVgs = HI_FALSE;
    VIDEO_FRAME_INFO_S stFrmInfo;
    VGS_TASK_ATTR_S stTask;
    HI_U32 u32LumaSize = 0;
    HI_U32 u32ChrmSize = 0;
    HI_U32 u32PicLStride = 0;
    HI_U32 u32PicCStride = 0;
    HI_U32 u32Width = 0;
    HI_U32 u32Height = 0;
    HI_S32 i = 0;
    HI_S32 s32Ret;
    HI_S32 s32CapCnt = 0;
    
    if (HI_MPI_VPSS_GetDepth(Grp, Chn, &u32OrigDepth) != HI_SUCCESS)
    {
        printf("get depth error!!!\n");
        return (HI_VOID*) - 1;
    }

    if (HI_MPI_VPSS_SetDepth(Grp, Chn, u32Depth) != HI_SUCCESS)
    {
        printf("set depth error!!!\n");
        VPSS_Restore(Grp, Chn);
        return (HI_VOID*) - 1;
    }
    u32VpssDepthFlag = 1;

    memset(&stFrame, 0, sizeof(stFrame));
    stFrame.u32PoolId = VB_INVALID_POOLID;
    while (HI_MPI_VPSS_GetChnFrame(Grp, Chn, &stFrame, s32MilliSec) != HI_SUCCESS)
    {
        s32Times--;
        if(0 >= s32Times)
        {
            printf("get frame error for 10 times,now exit !!!\n");
            VPSS_Restore(Grp, Chn);
            return (HI_VOID*) - 1;
        }
        usleep(40000);
    }
 	
	switch (stFrame.stVFrame.enPixelFormat)
	{
		case PIXEL_FORMAT_YUV_SEMIPLANAR_420:
			snprintf(szPixFrm, 10, "P420");
			break;
		case PIXEL_FORMAT_YUV_SEMIPLANAR_422:
			snprintf(szPixFrm, 10, "P422");
			break;
		case PIXEL_FORMAT_YUV_400:
			snprintf(szPixFrm, 10, "P400");
			break;
		default:
			snprintf(szPixFrm, 10, "--");
			break;
	}

    /* make file name */
    sprintf(szYuvName, "./vpss_grp%d_chn%d_w%d_h%d_%s_%d.yuv", Grp, Chn,
            stFrame.stVFrame.u32Width, stFrame.stVFrame.u32Height, szPixFrm, u32Cnt);
    printf("Dump YUV frame of vpss chn %d  to file: \"%s\"\n", Chn, szYuvName);
    fflush(stdout);

    HI_MPI_VPSS_ReleaseChnFrame(Grp, Chn, &stFrame);
    stFrame.u32PoolId = VB_INVALID_POOLID;
     /* open file */
    pfd = fopen(szYuvName, "wb");

    if (HI_NULL == pfd)
    {
        printf("open file failed:%s!\n", strerror(errno));
        VPSS_Restore(Grp, Chn);
        return (HI_VOID*) - 1;
    }

    /* get frame first */
    while (u32Cnt--)
    {
        if (HI_MPI_VPSS_GetChnFrame(Grp, Chn, &astFrame[s32CapCnt], s32MilliSec) != HI_SUCCESS)
        {
            printf("Get frame fail, real capture frame cnt: %d.\n", s32CapCnt);
            break;
        }
        s32CapCnt++;
    }

    printf("real capture frame cnt: %d\n", s32CapCnt);
    
    int j = 0;
    /* store yuv frames */
    for (j = 0; j < s32CapCnt; j++)
    {        
        bSendToVgs = ((astFrame[j].stVFrame.enCompressMode > 0) || (astFrame[j].stVFrame.enVideoFormat > 0));
        
        if (bSendToVgs)
        {
            u32PicLStride = astFrame[j].stVFrame.u32Stride[0];
            u32PicCStride = astFrame[j].stVFrame.u32Stride[0];
            u32LumaSize = astFrame[j].stVFrame.u32Stride[0] * astFrame[j].stVFrame.u32Height;
            u32Width    = astFrame[j].stVFrame.u32Width;
            u32Height   = astFrame[j].stVFrame.u32Height;

            if(PIXEL_FORMAT_YUV_SEMIPLANAR_420 == astFrame[j].stVFrame.enPixelFormat)
            {
                u32BlkSize = astFrame[j].stVFrame.u32Stride[0] * astFrame[j].stVFrame.u32Height * 3 >> 1;
                u32ChrmSize = astFrame[j].stVFrame.u32Stride[0] * astFrame[j].stVFrame.u32Height >> 2;
            }
            else if(PIXEL_FORMAT_YUV_SEMIPLANAR_422 == astFrame[j].stVFrame.enPixelFormat)
            {
                u32BlkSize = astFrame[j].stVFrame.u32Stride[0] * astFrame[j].stVFrame.u32Height * 2; 
                u32ChrmSize = astFrame[j].stVFrame.u32Stride[0] * astFrame[j].stVFrame.u32Height >> 1;
            }
            else if(PIXEL_FORMAT_YUV_400 == astFrame[j].stVFrame.enPixelFormat)
            {
                u32BlkSize = astFrame[j].stVFrame.u32Stride[0] * astFrame[j].stVFrame.u32Height;
                u32ChrmSize = 0;
            }
            else
            {
                printf("Unsupported pixelformat %d\n",astFrame[j].stVFrame.enPixelFormat);
                VPSS_Restore(Grp, Chn);
                return (HI_VOID*) - 1;
            }
            
            /*create comm vb pool*/
            hPool   = HI_MPI_VB_CreatePool( u32BlkSize, 1, HI_NULL);
            if (hPool == VB_INVALID_POOLID)
            {
                printf("HI_MPI_VB_CreatePool failed! \n");
                VPSS_Restore(Grp, Chn);
                return (HI_VOID*) - 1;
            }
            stMem.hPool = hPool;

            while ((stMem.hBlock = HI_MPI_VB_GetBlock(stMem.hPool, u32BlkSize, HI_NULL)) == VB_INVALID_HANDLE)
            {
                ;
            }
            stMem.u32PhyAddr = HI_MPI_VB_Handle2PhysAddr(stMem.hBlock);
            
            stMem.pVirAddr = (HI_U8*) HI_MPI_SYS_Mmap( stMem.u32PhyAddr, u32BlkSize );
            if (stMem.pVirAddr == HI_NULL)
            {
                printf("Mem dev may not open\n");
                VPSS_Restore(Grp, Chn);
                return (HI_VOID*) - 1;
            }

            memset(&stFrmInfo.stVFrame, 0, sizeof(VIDEO_FRAME_S));
            stFrmInfo.stVFrame.u32PhyAddr[0] = stMem.u32PhyAddr;
            stFrmInfo.stVFrame.u32PhyAddr[1] = stFrmInfo.stVFrame.u32PhyAddr[0] + u32LumaSize;
            stFrmInfo.stVFrame.u32PhyAddr[2] = stFrmInfo.stVFrame.u32PhyAddr[1] + u32ChrmSize;

            stFrmInfo.stVFrame.pVirAddr[0] = stMem.pVirAddr;
            stFrmInfo.stVFrame.pVirAddr[1] = (HI_U8*) stFrmInfo.stVFrame.pVirAddr[0] + u32LumaSize;
            stFrmInfo.stVFrame.pVirAddr[2] = (HI_U8*) stFrmInfo.stVFrame.pVirAddr[1] + u32ChrmSize;

            stFrmInfo.stVFrame.u32Width     = u32Width;
            stFrmInfo.stVFrame.u32Height    = u32Height;
            stFrmInfo.stVFrame.u32Stride[0] = u32PicLStride;
            stFrmInfo.stVFrame.u32Stride[1] = u32PicCStride;
            stFrmInfo.stVFrame.u32Stride[2] = u32PicCStride;

            stFrmInfo.stVFrame.enCompressMode = COMPRESS_MODE_NONE;
            stFrmInfo.stVFrame.enPixelFormat  = astFrame[j].stVFrame.enPixelFormat;
            stFrmInfo.stVFrame.enVideoFormat  = VIDEO_FORMAT_LINEAR;

            stFrmInfo.stVFrame.u64pts     = astFrame[j].stVFrame.u64pts;
            stFrmInfo.stVFrame.u32TimeRef = astFrame[j].stVFrame.u32TimeRef;

            stFrmInfo.u32PoolId = hPool;

            s32Ret = HI_MPI_VGS_BeginJob(&hHandle);
            if (s32Ret != HI_SUCCESS)
            {
                printf("HI_MPI_VGS_BeginJob failed\n");
                hHandle = -1;
                VPSS_Restore(Grp, Chn);
                return (HI_VOID*) - 1;
            }
            memcpy(&stTask.stImgIn, &astFrame[j].stVFrame, sizeof(VIDEO_FRAME_INFO_S));
            
            memcpy(&stTask.stImgOut , &stFrmInfo, sizeof(VIDEO_FRAME_INFO_S));
            s32Ret = HI_MPI_VGS_AddScaleTask(hHandle, &stTask);
            if (s32Ret != HI_SUCCESS)
            {
                printf("HI_MPI_VGS_AddScaleTask failed\n");
                VPSS_Restore(Grp, Chn);
                return (HI_VOID*) - 1;
            }

            s32Ret = HI_MPI_VGS_EndJob(hHandle);
            if (s32Ret != HI_SUCCESS)
            {
                printf("HI_MPI_VGS_EndJob failed\n");
                VPSS_Restore(Grp, Chn);
                return (HI_VOID*) - 1;
            }
            hHandle = -1;
            /* save VGS frame to file */
            sample_yuv_dump(&stFrmInfo.stVFrame, pfd);

            HI_MPI_VB_ReleaseBlock(stMem.hBlock);

            stMem.hPool =  VB_INVALID_POOLID;
            hHandle = -1;
            if(HI_NULL != stMem.pVirAddr)
            {
                HI_MPI_SYS_Munmap((HI_VOID*)stMem.pVirAddr, u32BlkSize );
                stMem.u32PhyAddr = HI_NULL;
            }
            if (hPool != VB_INVALID_POOLID)
            {
                HI_MPI_VB_DestroyPool( hPool );
                hPool = VB_INVALID_POOLID;
            }
            
        }
        else
        {
            sample_yuv_dump(&(astFrame[j].stVFrame), pfd);
        }

        printf("Get VpssGrp %d frame %d, time_ref: %d!!, u32PhyAddr: 0x%x\n", Grp, j, 
                astFrame[j].stVFrame.u32TimeRef, astFrame[j].stVFrame.u32PhyAddr[0]);
        /* release frame after using */
        HI_MPI_VPSS_ReleaseChnFrame(Grp, Chn, &astFrame[j]);
        astFrame[j].u32PoolId = VB_INVALID_POOLID;
    }
    VPSS_Restore(Grp, Chn);
    return (HI_VOID*)0;
}

static void usage(void)
{
    printf(
        "\n"
        "*************************************************\n"
        "Usage: ./vpss_chn_dump [VpssGrp] [VpssChn] [FrmCnt]\n"
        "1)VpssGrp: \n"
        "   Vpss group id\n"
        "2)VpssChn: \n"
        "   vpss chn id\n"
        "3)FrmCnt: \n"
        "   the count of frame to be dump\n"
        "*)Example:\n"
        "   e.g : ./vpss_chn_dump 0 0 1\n"
        "   e.g : ./vpss_chn_dump 1 4 2\n"
        "*************************************************\n"
        "\n");
}

HI_S32 main(int argc, char* argv[])
{
    HI_U32 u32FrmCnt = 1;
    
    printf("\nNOTICE: This tool only can be used for TESTING !!!\n");
    printf("\tTo see more usage, please enter: ./vpss_chn_dump -h\n\n");

    if (argc > 1)
    {
        if (!strncmp(argv[1], "-h", 2))
        {
            usage();
            exit(HI_SUCCESS);
        }
    }

    if (argc < 4)
    {
        usage();
        exit(HI_SUCCESS);
    }

    
    VpssGrp = atoi(argv[1]);    /* VpssGrp */
    VpssChn = atoi(argv[2]);    /* VpssChn */
    u32FrmCnt = atoi(argv[3]);  /* FrmCnt */

    u32VpssDepthFlag = 0;
    u32SignalFlag = 0;
    pUserPageAddr[0] = HI_NULL;
    stFrame.u32PoolId = VB_INVALID_POOLID;
    u32OrigDepth = 0;
    hPool  = VB_INVALID_POOLID;
    hHandle = -1;
    u32BlkSize = 0;
    u32Size = 0;
    pfd = HI_NULL;

    signal(SIGINT, VPSS_Chn_Dump_HandleSig);
    signal(SIGTERM, VPSS_Chn_Dump_HandleSig);

    SAMPLE_MISC_VpssDump(VpssGrp, VpssChn, u32FrmCnt);

    return HI_SUCCESS;
}
