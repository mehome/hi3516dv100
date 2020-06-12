#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hi_common.h"
#include "hi_comm_video.h"
#include "hi_comm_sys.h"
#include "hi_comm_vo.h"
#include "hi_comm_vi.h"
#include "hi_comm_vpss.h"
#include "hi_type.h"

#include "mpi_vb.h"
#include "mpi_sys.h"
#include "mpi_vi.h"
#include "mpi_vo.h"
#include "mpi_vpss.h"

#define USAGE_HELP(void)\
    {\
        printf("\n\tusage : %s para value group [chn] \n", argv[0]);    \
        printf("\n\t para: \n");    \
        printf("\t\tenNR   [0, disable; 1,enable]\n");    \
        printf("\t\tcon    [contrast, value:0~48,   default:8]\n");   \
        printf("\t\tglob   [the strength of NR, value:0~1408, default:128]\n");   \
        printf("\t\tie     [the strength of IE, value:-1~100,  default:-1]\n");   \
        printf("\t\tysf    [the strength of spatial noise reduction for the luminance, value:-1~9999, default:-1]\n");   \
        printf("\t\tytf    [the strength of temporal noise reduction for the luminance, value:-1~15, default:-1]\n");   \
        printf("\t\tcsf    [the strength of spatial noise reduction for the chrominance, value:-1~255, default:-1]\n");   \
        printf("\t\tctf    [the strength of temporal noise reduction for the chrominance, value:-1~32, default:-1]\n");   \
        printf("\t\tmdz    [the threshold for motion judgment, value:-1~511, default:-1]\n");   \
    }

#define CHECK_RET(express,name)\
    do{\
        if (HI_SUCCESS != express)\
        {\
            printf("%s failed at %s: LINE: %d ! errno:%#x \n", \
                   name, __FUNCTION__, __LINE__, express);\
            return HI_FAILURE;\
        }\
    }while(0)


HI_S32 main(int argc, char* argv[])
{
    HI_S32 s32Ret;
    VPSS_GRP_ATTR_S stVpssGrpAttr = {0};
    VPSS_GRP_PARAM_S stVpssGrpParam = {0};

    char paraTemp[16];
    HI_U32 value = 0;
    VPSS_GRP VpssGrp = 0;
    const char* para = paraTemp;

    if (argc < 4)
    {
        USAGE_HELP();
        return -1;
    }

    strcpy(paraTemp, argv[1]);
    value = atoi(argv[2]);
    VpssGrp = atoi(argv[3]);

    s32Ret = HI_MPI_VPSS_GetGrpAttr(VpssGrp, &stVpssGrpAttr);
    CHECK_RET(s32Ret, "HI_MPI_VPSS_GetGrpAttr");


    s32Ret = HI_MPI_VPSS_GetGrpParam(VpssGrp, &stVpssGrpParam);
    CHECK_RET(s32Ret, "HI_MPI_VPSS_GetGrpParam");

    if (0 == strcmp(para, "enNR"))
    {
        stVpssGrpAttr.bNrEn = value;
    }
    else if (0 == strcmp(para, "con"))
    {
        stVpssGrpParam.u32Contrast = value;
    }
    else if (0 == strcmp(para, "glob"))
    {
        stVpssGrpParam.s32GlobalStrength = value;
    }
    else if (0 == strcmp(para, "ie"))
    {
        stVpssGrpParam.s32IeStrength = value;
    }
    else if (0 == strcmp(para, "ysf"))
    {
        stVpssGrpParam.s32YSFStrength = value;
    }
    else if (0 == strcmp(para, "ytf"))
    {
        stVpssGrpParam.s32YTFStrength = value;
    }
    else if (0 == strcmp(para, "csf"))
    {
        stVpssGrpParam.s32CSFStrength = value;
    }
    else if (0 == strcmp(para, "ctf"))
    {
        stVpssGrpParam.s32CTFStrength = value;
    }
    else if (0 == strcmp(para, "mdz"))
    {
        stVpssGrpParam.s32MotionLimen = value;
    }
    else
    {
        printf("err para\n");
        USAGE_HELP();
    }

    s32Ret = HI_MPI_VPSS_SetGrpAttr(VpssGrp, &stVpssGrpAttr);
    CHECK_RET(s32Ret, "HI_MPI_VPSS_SetGrpAttr");


    s32Ret = HI_MPI_VPSS_SetGrpParam(VpssGrp, &stVpssGrpParam);
    CHECK_RET(s32Ret, "HI_MPI_VPSS_SetGrpParam");


    printf("\t\tenNR   %d\n", stVpssGrpAttr.bNrEn);
    printf("\t\tcon    %d\n", stVpssGrpParam.u32Contrast);
    printf("\t\tglob    %d\n", stVpssGrpParam.s32GlobalStrength);
    printf("\t\tie      %d\n", stVpssGrpParam.s32IeStrength);
    printf("\t\tysf     %d\n", stVpssGrpParam.s32YSFStrength);
    printf("\t\tytf     %d\n", stVpssGrpParam.s32YTFStrength);
    printf("\t\tcsf     %d\n", stVpssGrpParam.s32CSFStrength);
    printf("\t\tctf     %d\n", stVpssGrpParam.s32CTFStrength);
    printf("\t\tmdz     %d\n", stVpssGrpParam.s32MotionLimen);

    return 0;
}

