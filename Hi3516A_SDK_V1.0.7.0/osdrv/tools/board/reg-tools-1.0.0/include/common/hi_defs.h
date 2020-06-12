/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_defs.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/4/23
  Last Modified :
  Description   : 常用定义
  Function List :
  History       :
  1.Date        : 2005/4/20
    Author      : T41030
    Modification: Created file

******************************************************************************/


#ifndef __HI_DEFS_H__
#define __HI_DEFS_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef __GNUC__
#define __asm__    asm
#define __inline__ inline
#endif

#define DO_NOTHING

#define INLINE inline

/*use for parameter INPUT, *DO NOT Modify the value* */
#define IN
/* use for parameter OUTPUT, the value maybe change when return from the function 
 * the init value is ingore in the function.*/
#define OUT
/*use for parameter INPUT and OUTPUT*/
#define IO

/* --------------------------------  */
#define EXTERN extern
#define STATIC static

#define LOCALVAR static
#define GLOBALVAR extern


/*申明全局变量时*/
#define DECLARE_GLOBALVAR 

/*使用全局变量时, 用此声明*/
#define USE_GLOBALVAR extern


#define LOCALFUNC    static
#define EXTERNFUNC   extern



/*低层次的LOW API*/
#define LAPI  
/*高层次API*/
#define HAPI  
/*Multimedia Frame API*/
#define MMFAPI

/* -------- Standard input/output/err *****/
#define STDIN  stdin
#define STDOUT stdout
#define STDERR stderr


#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define MAX(x,y) ((x) > (y) ? (x) : (y))


/*
 * 根据给出的值v, 和对齐位数a, 计算对齐后的起始地址
 * 如4byte对齐, 0x80001232 ALIGN_START(0x80001232,4) = 0x80001230
 */
#define ALIGN_START(v,a) (((v)) & (~((a)-1)))

/*
 * 根据给出的值v, 和对齐位数a, 计算对齐后的结束地址地址
 * 如4byte对齐, 0x80001232 ALIGN_END(0x80001232,4) = 0x80001233
 */
#define ALIGN_END(v,a) (((v) & ~((a)-1)) + ((a)-1) ) 
/*
 * 根据给出的值v, 和对齐位数a, 计算对齐后下一地址的开始地址
 * 如4byte对齐, 0x80001232 ALIGN_NEXT(0x80001232,4) = 0x80001234
 */

#define ALIGN_NEXT(v,a) ((((v) + ((a)-1)) & (~((a)-1))))

#define ALIGN_LENGTH(l, a) ALIGN_NEXT(l, a)

#define ALIGNTYPE_1BYTE  1
/*zsp*/
#define ALIGNTYPE_2BYTE  2
/*x86... default*/
#define ALIGNTYPE_4BYTE  4

#define ALIGNTYPE_8BYTE  8
/*1 Page*/
#define ALIGNTYPE_4K     4096

#define ALIGNTYPE_ZSP    ALIGNTYPE_2BYTE

#define ALIGNTYPE_VIDEO  ALIGNTYPE_8BYTE

#define PRINT_OUT(args...) printf(##args)


#define PACK_ONE_BYTE  __attribute__((__packed__))

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_DEFS_H__ */
