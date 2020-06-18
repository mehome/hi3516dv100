/*
 * extdrv/ak7756en.h for Linux .
 *
 * History:
 *      22-September-2014 create this file
 */

#ifndef _INC_AK7756EN
#define  _INC_AK7756EN

#define     AK7756EN_I2C_SLAVE_ADDR     0x30

#define     SET_AK7756_SAMPLE_RATE 		0x1
#define     SET_AK7756_DATA_BITWIDTH 	0x2
#define     SET_AK7756_CTRL_MODE 		0x3
#define     SET_AK7756_TRANSFER_MODE 	0x4
#define     SET_AK7756_DAC_VOL_CTRL 	0x5
#define     SET_AK7756_ADC_POWER_SETUP 	0x6
#define     SET_AK7756_DAC_POWER_SETUP 	0x7
#define     AK7756_REG_DUMP 			0x8
#define     AK7756_SOFT_RESET 			0x9

#define     AK7756_SET_8K_SAMPLERATE	    8000
#define     AK7756_SET_16K_SAMPLERATE		16000

#define     AK7756_SET_SLAVE_MODE         0
#define     AK7756_SET_MASTER_MODE        1

#define     AK7756_SET_16BIT_WIDTH        0
#define     AK7756_SET_20BIT_WIDTH        1
#define     AK7756_SET_24BIT_WIDTH        2
#define     AK7756_SET_32BIT_WIDTH        3

#define     AK7756_READ_REG_BASEADDR      0x40
#define     AK7756_WRITE_REG_BASEADDR     0xC0


typedef struct
{
    unsigned int CtrlMode		: 1;
    unsigned int TransMode		: 2;
    unsigned int BitFs			: 2;
    unsigned int SampleRate 	: 1;
    unsigned int BitWidth		: 3;
    unsigned int MicGain		: 3;
    unsigned int PowerUp		: 1;
} Ak7756_Ctrl;

#endif
