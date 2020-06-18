/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_os.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/4/23
  Last Modified :
  Description   : 和操作系统相关的定义
  Function List :
  History       :
  1.Date        : 2005/4/20
    Author      : T41030
    Modification: Created file

******************************************************************************/


#ifndef __HI_OS_H__
#define __HI_OS_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*相关操作系统的定义*/

/* ------  使用和操作系统相关的实现时, 用下面的定义, 可以make文件中定义
#define OS_WINCE

#define OS_WIN32

#define OS_LINUX

#define OS_VXWORK

*/
#if defined(OS_LINUX)
    
#endif

#if defined(OS_WINCE)

#endif

#if defined(OS_WIN32)

#endif

#if defined(OS_LINUX)
#define  _UNUSED_FUNC __attribute__ ((unused))
#define  _UNUSED_VAR  __attribute__ ((unused))

/*
定义了函数，或者变量，但暂时不使用

.h中
int xxx() _NOWARN_UNUSED;

如果是局部函数， 没有在.h中声明的
int _NOWARN_UNUSED YYY()
{
    return 0;
}

*/
#define _NOWARN_UNUSED _UNUSED_FUNC
#endif

#if defined(OS_VXWORKS)

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_OS_H__ */
