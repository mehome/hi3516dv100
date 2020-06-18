/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : btools.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/11/24
  Last Modified :
  Description   : btools.h header file
  Function List :
  History       :
  1.Date        : 2005/11/24
    Author      : T41030
    Modification: Created file

******************************************************************************/


#ifndef __BTOOLS_H__
#define __BTOOLS_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


HI_RET himc(int argc , char* argv[]);

HI_RET himd_l(int argc , char* argv[]);

HI_RET himd(int argc , char* argv[]);

HI_RET himm(int argc , char* argv[]);

HI_RET hivd(int argc , char* argv[]);


HI_RET himdb(int argc , char* argv[]);

HI_RET hiddrs(int argc , char* argv[]);
HI_RET hil2s(int argc , char* argv[]);

HI_RET hier(int argc , char* argv[]);

HI_RET hiew(int argc , char* argv[]);

HI_RET i2c_read(int argc , char* argv[]);

HI_RET i2c_write(int argc , char* argv[]);

HI_RET ssp_read(int argc , char* argv[]);

HI_RET ssp_write(int argc , char* argv[]);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __BTOOLS_H__ */

