/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_limit.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/5/31
  Last Modified :
  Description   : azfifo.c header file
  Function List :
  History       :
  1.Date        : 2005/5/31
    Author      : T41030
    Modification: Created file

******************************************************************************/

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

#ifndef HI_LIMIT_H__
#define HI_LIMIT_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define INT_MAX         ((int)(~0U>>1))
#define MAXINT          INT_MAX
#define INT_MIN         (-INT_MAX - 1)
#define UINT_MAX        (~0U)
#define LONG_MAX        ((long)(~0UL>>1))
#define LONG_MIN        (-LONG_MAX - 1)
#define ULONG_MAX       (~0UL)



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* HI_LIMIT_H__ */
