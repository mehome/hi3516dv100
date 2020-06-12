/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : argparser.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/7/1
  Last Modified :
  Description   : Argument parser
  Function List :
  History       :
  1.Date        : 2005/7/27
    Author      : T41030
    Modification: Created file

******************************************************************************/


#ifndef ARGPARSER_H__
#define ARGPARSER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define ERR_ARG_WRONG_FMT         2   /*格式错误*/
#define ERR_ARG_UNKOWN_ARG        3 /*没有定义的arg*/
#define ERR_ARG_NOT_DEFINE_NO_OPT 4/*没有定义类型为NO_OPT的参数*/
#define ERR_ARG_MULTI_NO_OPT      5/*没有定义类型为NO_OPT的参数*/

enum ARG_TYPE
{
    ARG_TYPE_NO_OPT   =  0, /*没有 opt, 只有一个arg*/
    ARG_TYPE_CHAR     =  1, /*字符*/
    ARG_TYPE_STRING   =  2, /*字符串*/
    ARG_TYPE_INT      =  3, /*整形*/
    ARG_TYPE_FLOAT    =  4, /*浮点型*/
    ARG_TYPE_SINGLE   =  5, /*单个, 不带参数*/
    ARG_TYPE_HELP     =  6,
    ARG_TYPE_END      
};

typedef struct ARGOpt_stru
{
    //CHAR  opt;
    CHAR* sz_opt;    
    CHAR type;
    CHAR isSet; /*1: be set, 0 not set*/
    CHAR resv;
    CHAR *pHelpMsg;
    void *pValue;
}ARGOpt_t;

EXTERNFUNC HI_RET ARGParser(int argc, char **argv, ARGOpt_t *opts);
EXTERNFUNC VOID   ARGPrintOpt(ARGOpt_t *pOpt);

EXTERNFUNC VOID   StrToArg(CHAR* pSrc, int* argc, CHAR** argv);
EXTERNFUNC VOID   ARGClearOpts(ARGOpt_t *opts);
EXTERNFUNC VOID   ARGPrintHelp(ARGOpt_t *opts);

#define ARGHelpStrHead "\t"
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* ARGPARSER_H__ */
