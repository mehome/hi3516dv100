/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_bits.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2005/5/27
  Last Modified :
  Description   : hi_bits.h header file
  Function List :
  History       :
  1.Date        : 2005/5/27
    Author      : a
    Modification: Created file

******************************************************************************/

#ifndef __HI_BITS_H__
#define __HI_BITS_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/*** High 8 bits of 16 ***/
#define GET_0Byte_32(ul) ((U32)ul & 0x000000FF)
#define GET_1Byte_32(ul) ((U32)ul & 0x0000FF00) >> 8
#define GET_2Byte_32(ul) ((U32)ul & 0x00FF0000) >> 16
#define GET_3Byte_32(ul) ((U32)ul & 0xFF000000) >> 24

#define GET_HI8_16(us)  ((U16)us >> 8) 
#define GET_LO8_16(us)  ((U16)us & 0x00FF) 

#define SET_HI8_16(us, v) (((U16)us & 0x00FF) | (v << 8)) 
#define SET_LO8_16(us, v) (((U16)us & 0xFF00) | (v)) 

/**/
#define GET_HI16_32(dw)  ((dw) >> 16)
#define GET_LO16_32(dw)  ((dw) & 0x0000FFFF)

#define SET_HI16_32(dw, v) ((dw & 0x0000FFFF) | (v << 16)) 
#define SET_LO16_32(dw, v) ((dw & 0xFFFF0000) | (v)) 

#define GET_LO32_64(dw)  ((dw) & 0x00000000FFFFFFFF)

/*设置16位数的, 第nbit为v*/
/*15...3 2 1 0*/
#define SET_BIT0_16(us, v)   ((us & 0xFFFE) | v)
#define SET_BIT1_16(us, v)   ((us & 0xFFFD) | (v << 1))
#define SET_BIT2_16(us, v)   ((us & 0xFFFB) | (v << 2))
#define SET_BIT3_16(us, v)   ((us & 0xFFF7) | (v << 3))

#define SET_BIT4_16(us, v)   ((us & 0xFFEF) | (v << 4))
#define SET_BIT5_16(us, v)   ((us & 0xFFDF) | (v << 5))
#define SET_BIT6_16(us, v)   ((us & 0xFFBF) | (v << 6))
#define SET_BIT7_16(us, v)   ((us & 0xFF7F) | (v << 7))

#define SET_BIT8_16(us, v)   ((us & 0xFEFF) | (v << 8))
#define SET_BIT9_16(us, v)   ((us & 0xFDFF) | (v << 9))
#define SET_BIT10_16(us, v)  ((us & 0xFBFF) | (v << 10))
#define SET_BIT11_16(us, v)  ((us & 0xF7FF) | (v << 11))

#define SET_BIT12_16(us, v)  ((us & 0xEFFF) | (v << 12))
#define SET_BIT13_16(us, v)  ((us & 0xDFFF) | (v << 13))
#define SET_BIT14_16(us, v)  ((us & 0xBFFF) | (v << 14))
#define SET_BIT15_16(us, v)  ((us & 0x7FFF) | (v << 15))

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_BITS_H__ */
