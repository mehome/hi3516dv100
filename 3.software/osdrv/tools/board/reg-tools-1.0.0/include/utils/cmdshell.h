/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : cmdshell.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/11/1
  Last Modified :
  Description   : command shell
  Function List :
  History       :
  1.Date        : 2005/11/1
    Author      : T41030
    Modification: Created file

******************************************************************************/

#ifndef CMDSHELL_H__
#define CMDSHELL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*///////////////////////////////////////*/
/*main function style*/

#define ERR_CMD_SHELL_NULL_CMD 2
#define ERR_CMD_SHELL_NULL_FP  3

#define MAX_CMDSHELL_STRING_LEN 16
typedef HI_RET (*cmd_func)(int , char **);

#define CMD_ENABLE  1
#define CMD_DISABLE 0

typedef char CMDSHELL_STR[MAX_CMDSHELL_STRING_LEN] ;

typedef struct CMDSHELL_STRU
{
    char        *cmdstr;
    U32          isEnable;
    cmd_func     pFunc;
    char        *helpstr;
}CMD_SHELL_T;


#define CMD_SHELL_DEF(cmdstr,isEnable, pf, helpmsg) {cmdstr,isEnable, pf, helpmsg},






/*
cmdstrs : 完整的
*/
/*
CMD_SHELL_T *CMD_SHELL_Search(IN char* cmdstr, 
                              IN CMD_SHELL_T* pCmds, 
                              IN COUNT_T max_cmds
                              );
*/

CMD_SHELL_T *CMD_SHELL_Search(IN char* cmdstr, 
                              IN CMD_SHELL_T* pCmds
                              );

int CMD_SHELL_Run(CMD_SHELL_T* pCmd, int argc, char** argv);

/*输入的是整串命令*/
int CMD_SHELL_RUN(char* cmdstrs, const CMD_SHELL_T *pCmds);

/*输入的是命令行，直接从main传递参数*/
int CMD_SHELL_RUN_2(int argc, char* argv[], const CMD_SHELL_T *pCmds);

#define CMD_SHELL_PRINT_CMDSTRS(xargc, xargv)             \
    do                                                    \
    {                                                     \
        int i = 0;                                        \
        char x[128];                                      \
        memset(x, 0, 128);                                \
        for (i = 0; i< xargc;i++)                         \
        {                                                 \
            sprintf(x,"%s %s ",x, xargv[i]);               \
        }                                                 \
        printf(" argc: %d, argv:<%s>\n", xargc, x);          \
    }while(0)                                                     

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* CMDSHELL_H__ */

