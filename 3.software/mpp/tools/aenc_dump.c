#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>

#include "hi_common.h"
#include "hi_comm_video.h"
#include "hi_comm_sys.h"
#include "mpi_sys.h"
#include "hi_comm_vb.h"
#include "mpi_vb.h"
#include "hi_comm_aio.h"
#include "mpi_aenc.h"


#define AUDIO_VALUE_BETWEEN(x,min,max) (((x)>=(min)) && ((x) < (max)))

static AUDIO_SAVE_FILE_INFO_S g_stSaveFileInfo;
static AENC_CHN AencChn;

static  FILE *fp = NULL;

static void TOOL_AUDIO_HandleSig(HI_S32 signo)
{
    if (SIGINT == signo || SIGTERM == signo)
    {
    	g_stSaveFileInfo.bCfg = HI_FALSE;
		HI_MPI_AENC_SaveFile(AencChn, &g_stSaveFileInfo);
		
		if (NULL != fp)
		{
			pclose(fp);
			fp = NULL;
		}
        printf("\033[0;31mprogram exit abnormally!\033[0;39m\n");
    }

    exit(0);
}

static HI_VOID TOOL_AUDIO_Usage(HI_VOID)
{
	printf("\n*************************************************\n"
			"Usage: ./aenc_dump <chn> [name] [size] [path]\n"
			"1)chn: aenc channel id.\n"
			"2)name: file name for saving.\n"
			"default:default\n"
			"3)size: file size(KB).\n"
			"default:1024\n"
			"4)path: path for saving(NULL means current path).\n"
			"default: \n"
			"\n*************************************************\n");
}


HI_S32 main(int argc, char *argv[])
{
    HI_U32 u32Size = 1024;
	AUDIO_FILE_STATUS_S stFileStatus;
    HI_S32 s32Ret;
    HI_CHAR aCurPath[258]; /*256 + '\n'+'\0'*/    
    HI_S32 s32CurrentPath = -1;

	printf("\nNOTICE: This tool only can be used for TESTING !!!\n");
    printf("\tTo see more usage, please enter: ./aenc_dump -h\n\n");

    if (argc < 2)
    {
		TOOL_AUDIO_Usage();
    	return -1;
    }

	if (!strncmp(argv[1], "-h", 2))
	{
		TOOL_AUDIO_Usage();
    	return 0;
	}
	else
	{
	    AencChn = atoi(argv[1]);/* chn id*/
	    if (!AUDIO_VALUE_BETWEEN(AencChn, 0, AENC_MAX_CHN_NUM))
	    {
    		printf("chn id must be [0,%d)!!!!\n\n", AENC_MAX_CHN_NUM);
	    	return -1;
	    }
	}
	
	if (argc>=3)
    {
        if (!AUDIO_VALUE_BETWEEN(strlen(argv[2]), 1, 256))
        {
        	printf("path lenth must be [1,256]!!!!\n\n");
        	return -1;
        }
        memcpy(g_stSaveFileInfo.aFileName, argv[2], strlen(argv[2]));
        g_stSaveFileInfo.aFileName[strlen(argv[2])] = '\0';
    }
    else
    {
        memcpy(g_stSaveFileInfo.aFileName, "default", strlen("default")+1);
    }
	
    if (argc>=4)
    {
        if (!AUDIO_VALUE_BETWEEN(atoi(argv[3]), 1, 10*1024+1))
        {
        	printf("file size must be [1, 10*1024]!!!!\n\n");
        	return -1;
        }
        u32Size = atoi(argv[3]);/* frame count*/
    }
	
    if (argc>=5)
    {
        if (!AUDIO_VALUE_BETWEEN(strlen(argv[4]), 1, 256))
        {
        	printf("path lenth must be [1, 256]!!!!\n\n");
        	return -1;
        }
        memcpy(g_stSaveFileInfo.aFilePath,argv[4],strlen(argv[4]));
        g_stSaveFileInfo.aFilePath[strlen(argv[4])] = '\0';

        if (g_stSaveFileInfo.aFilePath[0] == '.' && (g_stSaveFileInfo.aFilePath[1] == '\0' || g_stSaveFileInfo.aFilePath[1] == '/'))
        {
            s32CurrentPath = 0;
        }
    }
    else
    {
        s32CurrentPath = 1;
    }

	signal(SIGINT, TOOL_AUDIO_HandleSig);
    signal(SIGTERM, TOOL_AUDIO_HandleSig);

    if (s32CurrentPath != -1)
    {
        fp = popen("pwd", "r");
        fgets(aCurPath, sizeof(aCurPath), fp);
        if (!AUDIO_VALUE_BETWEEN(strlen(aCurPath), 1, 256))
        {
            printf("path lenth must be [1,256]!!!!\n\n");
            pclose(fp);
			fp = NULL;
            return -1;
        }
        aCurPath[strlen(aCurPath) - 1] = '/'; /*replace '\n' with '/'*/

        if (s32CurrentPath == 0)
        {
            HI_U32 i = 2;
            HI_U32 u32Len = strlen(aCurPath);
            if (!AUDIO_VALUE_BETWEEN(strlen(aCurPath)+strlen(g_stSaveFileInfo.aFilePath), 1, 256))
            {
                printf("path lenth must be [1,256]!!!!\n\n");
                pclose(fp);
				fp = NULL;
                return -1;
            }

            while (strlen(g_stSaveFileInfo.aFilePath) > 1 && g_stSaveFileInfo.aFilePath[i] != '\0')
            {
                
                aCurPath[u32Len+i-2] = g_stSaveFileInfo.aFilePath[i];

                i ++;
            }

            aCurPath[u32Len+i-2] = '\0';
        }
        snprintf(g_stSaveFileInfo.aFilePath, 256, "%s", aCurPath);
        
        pclose(fp);
		fp = NULL;
        //memcpy(g_stSaveFileInfo.aFilePath,"./",strlen("./")+1);
    }

	
    g_stSaveFileInfo.u32FileSize = u32Size;
    g_stSaveFileInfo.bCfg = HI_TRUE;
	
    printf("File path:%s, file name:%s, file size:%d*1024\n\n", g_stSaveFileInfo.aFilePath, g_stSaveFileInfo.aFileName, g_stSaveFileInfo.u32FileSize);
    s32Ret = HI_MPI_AENC_SaveFile(AencChn,&g_stSaveFileInfo);
    if (s32Ret != HI_SUCCESS)
    {
    	printf("HI_MPI_AENC_SaveFile() error,ret=%x!!!!\n\n",s32Ret);
    	return -1;
    }

	printf("Saving file now, please wait.\n");
	do 
	{
		s32Ret = HI_MPI_AENC_QueryFileStatus(AencChn, &stFileStatus);
		if ((HI_SUCCESS != s32Ret) || (!stFileStatus.bSaving))
		{
			break;
		}

		usleep(200000);

	}while (stFileStatus.bSaving);

	printf("File saving is finished.\n");

    return HI_SUCCESS;
}

