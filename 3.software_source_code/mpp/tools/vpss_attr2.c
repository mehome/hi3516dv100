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
    do{\
        printf("\n\tusage : %s para value group [chn] \n", argv[0]);    \
        printf("\n\tpara: \n");    \
        printf("\t\tenNR            [0, disable; 1,enable]\n");    \
        printf("\t\tsfc             [the strength of spatial filtering, value:0~255,   default:8]\n");   \
        printf("\t\ttfc             [the strength of temporal filtering, value:0~32, default:0]\n");   \
        printf("\t\tiepost          [if there is a delay post-processing image texture or edge, value:0~1,  default:0]\n");   \
        printf("\t\tie              [enhance the strength of texture or the strength of edge, value:0~63,  default:63]\n");   \
        printf("\t\tysfm 	        [the strength of spatial for luminance in the moving region, value:0~255, default:32]\n");   \
        printf("\t\tysfs 	        [the strength of spatial for luminance in the static region, value:0~64, default:32]\n");   \
        printf("\t\tytf  	        [the strength of temporal for luminance,value:0~31, default:31]\n");   \
        printf("\t\tymth            [the threshold for  motion detection of luminance, value:0~511, default:64]\n");\
        printf("\t\tdesand          [the removal of grain-noise, value:0~8, default:0 ]\n");\
    }while(0)

#define CHECK_RET(express,name)\
    do{\
        if (HI_SUCCESS != express)\
        {\
            printf("%s failed at %s: LINE: %d ! errno:0x%x \n", \
                   name, __FUNCTION__, __LINE__, express);\
            return HI_FAILURE;\
        }\
    }while(0)


HI_S32 main(int argc, char* argv[])
{
    HI_S32 s32Ret;
    VPSS_GRP_ATTR_S stVpssGrpAttr = {0};
    VPSS_GRP_PARAM_V2_S stVpssGrpParam = {0};

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


    s32Ret = HI_MPI_VPSS_GetGrpParamV2(VpssGrp, &stVpssGrpParam);
    CHECK_RET(s32Ret, "HI_MPI_VPSS_GetGrpParam");

    printf("================================\n");
    if (0 == strcmp(para, "enNR"))
    {
        stVpssGrpAttr.bNrEn = value;
    }
    else if (0 == strcmp(para, "sfc"))
    {
        stVpssGrpParam.Chroma_SF_Strength = value;
    }
    else if (0 == strcmp(para, "tfc"))
    {
        stVpssGrpParam.Chroma_TF_Strength = value;
    }
    else if (0 == strcmp(para, "iepost"))
    {
        stVpssGrpParam.IE_PostFlag = value;
    }
    else if (0 == strcmp(para, "ie"))
    {
        stVpssGrpParam.IE_Strength = value;
    }
    else if (0 == strcmp(para, "ysfm"))
    {
        stVpssGrpParam.Luma_SF_MoveArea = value;
    }
    else if (0 == strcmp(para, "ysfs"))
    {
        stVpssGrpParam.Luma_SF_StillArea = value;
    }
    else if (0 == strcmp(para, "ytf"))
    {
        stVpssGrpParam.Luma_TF_Strength = value;
    }
    else if (0 == strcmp(para, "ymth"))
    {
        stVpssGrpParam.Luma_MotionThresh = value;
    }
    else if (0 == strcmp(para, "desand"))
    {
        ;//stVpssGrpParam.DeSand_Strength = value;
    }
    else
    {
        printf("err para\n");
        USAGE_HELP();
    }

    s32Ret = HI_MPI_VPSS_SetGrpAttr(VpssGrp, &stVpssGrpAttr);
    CHECK_RET(s32Ret, "HI_MPI_VPSS_SetGrpAttr");


    s32Ret = HI_MPI_VPSS_SetGrpParamV2(VpssGrp, &stVpssGrpParam);
    CHECK_RET(s32Ret, "HI_MPI_VPSS_SetGrpParam");

    printf("\t\tenNR            %d\n", stVpssGrpAttr.bNrEn);
    printf("\t\tsfc             %d\n", stVpssGrpParam.Chroma_SF_Strength);
    printf("\t\ttfc             %d\n", stVpssGrpParam.Chroma_TF_Strength);
    printf("\t\tiepost          %d\n", stVpssGrpParam.IE_PostFlag);
    printf("\t\tie              %d\n", stVpssGrpParam.IE_Strength);
    printf("\t\tymth            %d\n", stVpssGrpParam.Luma_MotionThresh);
    printf("\t\tysfm            %d\n", stVpssGrpParam.Luma_SF_MoveArea);
    printf("\t\tysfs            %d\n", stVpssGrpParam.Luma_SF_StillArea);
    printf("\t\tytf             %d\n", stVpssGrpParam.Luma_TF_Strength);
    //printf("\t\tdesand          %d\n", stVpssGrpParam.DeSand_Strength);

    return 0;
}

