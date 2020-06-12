
/* file name : memmap.h                                     */
/* linux /dev/mem mmap support head file					*/
/* 															*/
/* 															*/
/* Copyright 2005 huawei com.                               */
/* Author :zhouaidi(42136)									*/
/* Create date: 2005-04-07									*/
/* Modify history											*/
/*                                                          */

#ifndef __MEM_MAP_H__
#define __MEM_MAP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern void * memmap(unsigned int phy_addr, unsigned int size);
extern int memunmap(void * addr_mapped);
extern void * mmapfile(char* fn, unsigned int size);
extern void * mmapfile_r(char* fn, unsigned int size);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

