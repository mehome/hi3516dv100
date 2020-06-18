#if !defined( HI_MESSAGE_H__ )
#define HI_MESSAGE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdarg.h>

#if defined(MULTI_TASK_LOGQUEUE)
#ifdef OS_LINUX
#include <pthread.h>
#endif
#endif

#define MAX_MESSAG_STRLEN 512
typedef struct LOG_QUEUE_STRU
{
    /** Message queue lock */
    #if defined(MULTI_TASK_LOGQUEUE)
    pthread_mutex_t     mutex_lock;
    #endif
    U8                  ucMinLevel;
    
    LENGTH_T            lenMsg;
    CHAR                *pMsg;
}LOG_QUEUE;

HI_RET Log_Create (IO LOG_QUEUE *pLogQueue, IN U8 minLevel, IN LENGTH_T lenMsg);

VOID Log_Destroy(IO LOG_QUEUE *pLogQueue );


VOID Log_Msg     (IO LOG_QUEUE *pLogQueue, 
                  IN U32 ucLogLevel, 
                  IN char *psz_format, ... );

VOID Log_MsgVa( IO LOG_QUEUE*  pLogQueue, 
                 IN U32 ucLogLevel, 
                 IN char *psz_format,IN va_list args );




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
