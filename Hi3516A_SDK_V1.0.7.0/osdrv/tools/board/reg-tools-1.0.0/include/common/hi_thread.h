/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_thread.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/6/30
  Last Modified :
  Description   : hi_thread.h header file
  Function List :
  History       :
  1.Date        : 2005/6/30
    Author      : T41030
    Modification: Created file

******************************************************************************/

#ifndef __HI_THREAD_H__
#define __HI_THREAD_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include <pthread.h>
#include <semaphore.h>
#include <hi_defs.h>
typedef pthread_mutex_t     HI_THREAD_MUTEX ;
typedef pthread_mutexattr_t HI_THREAD_MUTEXATTR;

typedef pthread_cond_t      HI_THREAD_COND;
typedef pthread_condattr_t  HI_THREAD_CONDATTR;


typedef struct HI_SYNC_STRU
{
    #if defined(SYNC_USE_COND)
    HI_THREAD_MUTEX _mutex;
    HI_THREAD_COND  _cond;
    #else
    sem_t           _sem;
    #endif
}HI_SYNC_T;

    
#define MAX_THREAD_NAME_LEN 16

typedef int HI_PRIORITY_T;

typedef char THREAD_NAME[MAX_THREAD_NAME_LEN];

typedef VOID* (*THREAD_RUN)(VOID* );

typedef struct HI_THREAD_STRU
{
    /*线程名称*/
    THREAD_NAME     szThreadName;
    /**/
    pthread_t       threadid;
    
    /*linuxthread中， 每个线程都有一个唯一的pid, 用ps可以查看*/
    pid_t           pid; 
    
    /*优先级*/
    HI_PRIORITY_T   priority;

    /*线程运行的主函数*/
    THREAD_RUN      pf_run;

    /*<TODO>是否create后马上运行*/
    BOOL            bStart; 

    /*<TODO>用于控制线程创建时是否马上开始运行*/
    HI_THREAD_COND cond_start;
    HI_THREAD_MUTEX mutex_cond_start;

    VOID*          args;
}HI_THREAD_T;

EXTERNFUNC HI_RET hi_thread_init(HI_THREAD_T *pThread, char* szName, 
                        THREAD_RUN pf, INT32 priority, BOOL bStart);

VOID* hi_thread_run_handle(VOID* arg);

EXTERNFUNC void hi_delay(U32 ulUsDelay);

/*__wait is TRUE, not run when create , wait cond_start to run*/
EXTERNFUNC INT32 hi_thread_create(HI_THREAD_T *pThread,const pthread_attr_t*__attr,
                      void*__arg);

EXTERNFUNC INT32 hi_thread_join(HI_THREAD_T *pThread, void **thread_return);

EXTERNFUNC INT32 HI_THREAD_Start(HI_THREAD_T *pThread);

EXTERNFUNC INT32 hi_thread_pause(HI_THREAD_T *pThread);

EXTERNFUNC INT32 hi_thread_cancel(HI_THREAD_T *pThread);
EXTERNFUNC VOID hi_thread_setid(HI_THREAD_T *pThread);

EXTERNFUNC VOID hi_thread_setpriority(HI_THREAD_T *pThread, HI_PRIORITY_T prio);

/*** ------------------------------------ ***/
EXTERNFUNC INT32 hi_thread_mutex_init(HI_THREAD_MUTEX* pMutex, HI_THREAD_MUTEXATTR* pMutexattr);

EXTERNFUNC INT32 hi_thread_mutex_lock(HI_THREAD_MUTEX* pMutex);

EXTERNFUNC INT32 hi_thread_mutex_trylock(HI_THREAD_MUTEX* pMutex);

EXTERNFUNC INT32 hi_thread_mutex_unlock(HI_THREAD_MUTEX* pMutex);

EXTERNFUNC INT32 hi_thread_mutex_destroy(HI_THREAD_MUTEX* pMutex);
    
/*** ------------------------------------ ***/
EXTERNFUNC INT32 hi_thread_cond_init(HI_THREAD_COND* pCond, HI_THREAD_CONDATTR* pCondattr);
EXTERNFUNC INT32 hi_thread_cond_signal(HI_THREAD_COND* pCond);
EXTERNFUNC INT32 hi_thread_cond_broadcast(HI_THREAD_COND* pCond);
EXTERNFUNC INT32 hi_thread_cond_wait(HI_THREAD_COND* pCond, HI_THREAD_MUTEX *pMutex, U32 msecs);
EXTERNFUNC INT32 hi_thread_cond_destroy(HI_THREAD_COND* pCond);


#define DEFAULT_PRIORITY       0
#define THREAD_PRIORITY_AUDIO 0
#define THREAD_PRIORITY_AZ    10

#define THREAD_SLEEP(msec) usleep(msec * 1000)
/*#define THREAD_SLEEP(msec) */

/*** -------------------------------------***/
EXTERNFUNC HI_RET hi_sync_create(IO HI_SYNC_T *pWait);
EXTERNFUNC HI_RET hi_sync_wait(IO HI_SYNC_T *pWait, IN U32 msec);
EXTERNFUNC HI_RET hi_sync_notify(IO HI_SYNC_T *pWait);
EXTERNFUNC HI_RET hi_sync_destroy(IO HI_SYNC_T *pWait);

#if defined(DEBUG)
#define SYNC_WAIT(pSync, msec, pStr) \
    if (pStr)                        \
        WRITE_LOG_DEBUG(pStr);       \
    hi_sync_wait(pSync, msec)        

#define SYNC_NOTIFY(pSync, msec, pStr) \
    if (pStr)                        \
        WRITE_LOG_DEBUG(pStr);       \
    hi_sync_notify(pSync)        
#else
#define SYNC_WAIT(pSync, msec, pStr) \
    hi_sync_wait(pSync, msec)        

#define SYNC_NOTIFY(pSync, msec, pStr) \
    hi_sync_notify(pSync)        
#endif



/*__wait is TRUE, not run when create , wait cond_start to run*/
#define HI_THREAD_CREATE (pThread, __attr, __arg)\
                hi_thread_create(pThread, __attr, __arg)

#define HI_THREAD_JOIN(pThread, ppthread_return) \
                hi_thread_join(pThread, ppthread_return)

#define HI_THREAD_START(pThread) \
                HI_THREAD_Start(pThread) 

#define HI_THREAD_PAUSE(pThread) \
                hi_thread_pause(pThread)

#define HI_THREAD_SETID(pThread) \
                hi_thread_setid(pThread)

#define HI_THREAD_SETPRIORITY(pThread ,prio) \
                hi_thread_setpriority(pThread ,prio)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_THREAD_H__ */

