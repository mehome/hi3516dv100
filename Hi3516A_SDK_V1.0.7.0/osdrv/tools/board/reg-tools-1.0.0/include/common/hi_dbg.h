/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_dbg.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/4/20
  Last Modified :
  Description   : 本文件是用来定义关于调试信息相关的宏定义, 以及函数声明等,
                  例如打印输出, 写log, assert等的定义
  Function List :
  History       :
  1.Date        : 2005/4/20
    Author      : T41030
    Modification: Created file

******************************************************************************/

#ifndef __HI_DBG_H__
#define __HI_DBG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdio.h>

#if defined(DEBUG)
#include <assert.h>
#endif

#ifdef LOGQUEUE
#include "hi_message.h"
USE_GLOBALVAR LOG_QUEUE gLogQueue;
#endif

#if defined(DEBUG)
    /* TODO: 打印出文件名, 行号, 和expression , 并break*/
    #define  DBG_ASSERT(expression) assert(expression)
    #define  DBG_ASSERT_STR(expression, str)     \
                do                               \
                {                                \
                    if (!(expression))           \
                    {                            \
                        WRITE_LOG_DEBUG(str);    \
                        assert(expression);      \
                    }                            \
                }while(0);                               
                
                    
    /* TODO: 打印出文件名, 行号, 和出错信息 */
    #define  DBG_LOG  WRITE_LOG_DEBUG 
    #define  DBG_LOG1 WRITE_LOG_DEBUG1 
    #define  DBG_LOG2 WRITE_LOG_DEBUG2 
    
#else
    #define DBG_ASSERT(expression)   ((void)0)
    #define  DBG_ASSERT_STR(expression, str)
    
    #define DBG_LOG(args...)  
    #define  DBG_LOG1 WRITE_LOG_DEBUG1 
    #define  DBG_LOG2 WRITE_LOG_DEBUG2 
    
#endif
#define LOG_LEVEL_NORMAL    0
#define LOG_LEVEL_FATAL     1
#define LOG_LEVEL_ERROR     2
#define LOG_LEVEL_WARN      3
#define LOG_LEVEL_INFO      4

#define LOG_LEVEL_DEBUG     5
#define LOG_LEVEL_DEBUG1    6
#define LOG_LEVEL_DEBUG2    7

#define LOG_LEVEL_ALL       10
#define LOG_LEVEL_NONE      0

#define LOG_LEVEL_DEFAULT   LOG_LEVEL_INFO
#define LOG_LEVEL_MINI      LOG_LEVEL_ERROR
#define LOG_LEVEL_MAX       LOG_LEVEL_ALL


/* LOG */
/*
*调用方法
*WRITE_LOG_FATAL("Memory is too much , total: %u M, it's waste, please save people's money , 1024");
*WRITE_LOG ( LOG_LEVEL_WARN, "after VIU device analyse: you are a handsome pig." );
*/

/*gLogQueue is a Global Var, now defined at hi_message.c and 
  declare at hi_dbg.h, it you use this log functions outside, 
  you can declare your owner "gLogQueue"*/
/*Call this first , and only call it once*/

/*level = LOG_LEVEL_ERROR .....*/

#ifdef LOGQUEUE
#define LOG_CREATE(level, msglen)    Log_Create(&gLogQueue, level, msglen)

#define LOG_SETLEVEL(level)  (gLogQueue.ucMinLevel = level)

#define LOG_GETLEVEL() (gLogQueue.ucMinLevel)

#define LOG_DESTROY()   Log_Destroy(&gLogQueue)


#if 0
#define WRITE_LOG_NORMAL(psz_format, args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_NORMAL, psz_format, ##args )

#define WRITE_LOG_INFO(psz_format, args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_INFO, psz_format, ##args )
            
#define WRITE_LOG_FATAL(psz_format, args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_FATAL, psz_format, ##args )

#define WRITE_LOG_ERROR(psz_format, args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_ERROR, psz_format, ##args )

#define WRITE_LOG_WARN(psz_format, args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_WARN, psz_format, ##args )
            
#define WRITE_LOG_DEBUG(psz_format, args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_DEBUG, "{%s:%i}:"psz_format, \
            __FILE__, __LINE__ ,##args)

#define WRITE_LOG_DEBUG1(psz_format, args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_DEBUG1, "{%s:%i}:"psz_format, \
            __FILE__, __LINE__ ,##args)

#define WRITE_LOG_DEBUG2(psz_format, args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_DEBUG2, "{%s:%i}:"psz_format, \
            __FILE__, __LINE__ ,##args)

#define WRITE_LOG(iLevel, psz_format, args... ) \
            Log_Msg(&gLogQueue, iLevel, psz_format, ##args )
#endif      /* End of #if 0 */

#define MKSTR(exp) # exp
#define MKMARCOTOSTR(exp) MKSTR(exp)
#define LINENUMBER MKMARCOTOSTR(__LINE__)

#define ATTACHINFO "{"__FILE__ ":" LINENUMBER "}"


#define WRITE_LOG_NORMAL(args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_NORMAL, args )

#define WRITE_LOG_INFO(args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_INFO, args)
            
#define WRITE_LOG_FATAL(args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_FATAL, args )

#define WRITE_LOG_ERROR(args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_ERROR, args )

#define WRITE_LOG_WARN(args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_WARN, args )
            
#define WRITE_LOG_DEBUG(args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_DEBUG, ATTACHINFO args)

#define WRITE_LOG_DEBUG1(args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_DEBUG1, ATTACHINFO args)

#define WRITE_LOG_DEBUG2(args... ) \
            Log_Msg(&gLogQueue, LOG_LEVEL_DEBUG2, ATTACHINFO args)

#define WRITE_LOG(iLevel, args... ) \
            Log_Msg(&gLogQueue, iLevel, args )

#else

#define LOG_CREATE(level, msglen)

#define LOG_SETLEVEL(level)

#define LOG_GETLEVEL() (0)

#define LOG_DESTROY() 

#define WRITE_LOG_NORMAL(args...)

#define WRITE_LOG_INFO(args...)
            
            
#define WRITE_LOG_FATAL(args...)


#define WRITE_LOG_ERROR(args...)


#define WRITE_LOG_WARN(args...)

            
#define WRITE_LOG_DEBUG(args...)

#define WRITE_LOG_DEBUG1(args...)

#define WRITE_LOG_DEBUG2(args...)


#define WRITE_LOG(args...)

#endif


#if defined(OS_LINUX) && defined(USE_BTRACE) && defined(DEBUG)
    #if !defined(BTRACE_ENABLE)
    #define BTRACE_ENABLE
    #endif
#else
    #if defined(BTRACE_ENABLE)
    #undef BTRACE_ENABLE
    #endif
#endif



#if defined(BTRACE_ENABLE)
    #define BTRACE_INIT() btrace()
    #define BTRACE_PRINT btrace_print
    #define BTRACE_PRINT_FUNC() btrace_print_str(__func__)
    #define BTRACE_PRINT_STR(str) btrace_print_str(str)

#else
    #define BTRACE_INIT()
    #define BTRACE_PRINT 
    #define BTRACE_PRINT_FUNC() 
    #define BTRACE_PRINT_STR(str)
#endif

EXTERNFUNC HI_RET hi_md(IN VOID* pStart,IN  U32 ulLen,IN FD fd);
/*Memory Dump 2 file*/
EXTERNFUNC HI_RET hi_md2file(IN VOID* pStart,IN  U32 ulLen,
                            IN char* strLabel, 
                            IN char* fn);

EXTERNFUNC void hi_hexdump(OUT FILE *stream, 
                        IN const void *src, IN size_t len, 
                        IN size_t width);

EXTERNFUNC VOID hi_hexdump_log(IN const void *src, IN size_t len, 
                        IN size_t width);

EXTERNFUNC int hi_shexdump(IN const void *src, IN size_t len, 
                         IN size_t width, IN char *dlim,
                         OUT char *dst);

VOID hi_hexdump2(OUT FILE *stream, 
                        IN const void *src, IN size_t len, IN size_t width);



#if defined(DEBUG)
#define MEM_DUMP      hi_md
#define MEM_DUMP2FILE hi_md2file
#else
#define MEM_DUMP      
#define MEM_DUMP2FILE 
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_DBG_H__ */
