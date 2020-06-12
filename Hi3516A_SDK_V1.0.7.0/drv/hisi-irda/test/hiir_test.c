#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "hiir.h"
#include "hiir_codedef.h"

typedef unsigned short int U8;

typedef struct
{
    char *name;
    unsigned int irkey_value;
}IRKEY_ADAPT;

#define REMOTE_POWER      0xef10f708
#define REMOTE_MUTE       0xf20df708
#define REMOTE_INPUT_MOD  0xff00f708
#define REMOTE_TRACK      0xfe01f708
#define REMOTE_F1         0xb24df708
#define REMOTE_F2         0xb14ef708
#define REMOTE_F3         0xae51f708
#define REMOTE_F4         0xad52f708

static IRKEY_ADAPT g_irkey_adapt_array[] =
{
    /*irkey_name*/ /*irkey_value*/
    {"REMOTE_POWER       ", REMOTE_POWER,/*power*/                  },
    {"REMOTE_MUTE        ", REMOTE_MUTE,/*mute*/                    },
    {"REMOTE_INPUT_MOD   ", REMOTE_INPUT_MOD,/*inout method*/       },
    {"REMOTE_TRACK       ", REMOTE_TRACK,/*track*/                  },
    {"REMOTE_KEY_ONE     ", 0xe01ff708,/*1*/                        },
    {"REMOTE_KEY_TWO     ", 0xfc03f708,/*2*/                        },
    {"REMOTE_KEY_THREE   ", 0xfb04f708,/*3*/                        },
    {"REMOTE_KEY_FOUR    ", 0xfa05f708,/*4*/                        },
    {"REMOTE_KEY_FIVE    ", 0xe31cf708,/*5*/                        },
    {"REMOTE_KEY_SIX     ", 0xf906f708,/*6*/                        },
    {"REMOTE_KEY_SEVEN   ", 0xf807f708,/*7*/                        },
    {"REMOTE_KEY_EIGHT   ", 0xf708f708,/*8*/                        },
    {"REMOTE_KEY_NINE    ", 0xe21df708,/*9*/                        },
    {"REMOTE_SWITH_1_2   ", 0xf609f708,/*-/--*/                     },
    {"REMOTE_KEY_ZERO    ", 0xf50af708,/*0*/                        },
    {"REMOTE_BACKSPACE   ", 0xf40bf708,/*<-*/                       },
    {"REMOTE_INTERACTION ", 0xeb14f708,/*interaction*/              },
    {"REMOTE_SEARCH      ", 0xea15f708,/*search*/                   },
    {"REMOTE_UP_CURSOR   ", 0xe916f708,/*up*/                       },
    {"REMOTE_LEFT_CURSOR ", 0xe817f708,/*left*/                     },
    {"REMOTE_RIGHT_CURSOR", 0xf30cf708,/*right*/                    },
    {"REMOTE_DOWN_CURSOR ", 0xed12f708,/*down*/                     },
    {"REMOTE_ENTER       ", 0xe718f708,/*enter*/                    },
    {"REMOTE_MENU        ", 0xf10ef708,/*menu*/                     },
    {"REMOTE_PAGEUP      ", 0xec13f708,/*page up*/                  },
    {"REMOTE_PAGEDOWN    ", 0xee11f708,/*page down*/                },
    {"REMOTE_GO_BACK     ", 0xe619f708,/*back*/                     },
    {"REMOTE_BTV_PLAY    ", 0xe51af708,/*broadcast television */    },
    {"REMOTE_VOD_PLAY    ", 0xe41bf708,/*video on demand*/          },
    {"REMOTE_REP_PLAY    ", 0xbb44f708,/*repeat play*/              },
    {"REMOTE_RECALL      ", 0xbf40f708,/*recall*/                   },
    {"REMOTE_PLAYANDPAUSE", 0xa55af708,/*play/pause*/               },
    {"REMOTE_FAST_REWIND ", 0xbd42f708,/*fast rewind*/              },
    {"REMOTE_FAST_FORWARD", 0xba45f708,/*fast forward*/             },
    {"REMOTE_STOP        ", 0xbc43f708,/*stop*/                     },
    {"REMOTE_SEEK        ", 0xb748f708,/*seek*/                     },
    {"REMOTE_FAVORITE    ", 0xb54af708,/*favorite*/                 },
    {"REMOTE_SETTING     ", 0xb649f708,/*setting*/                  },
    {"REMOTE_INFO        ", 0xb44bf708,/*information*/              },
    {"REMOTE_CHANNEL_PLUS", 0xb34cf708,/*channel+*/                 },
    {"REMOTE_CHANNEL_MINU", 0xaf50f708,/*channel-*/                 },
    {"REMOTE_VOL_PLUS    ", 0xb04ff708,/*volume+*/                  },
    {"REMOTE_VOL_MINUS   ", 0xac53f708,/*volume-*/                  },
    {"REMOTE_F1          ", REMOTE_F1,/*F1 green key*/              },
    {"REMOTE_F2          ", REMOTE_F2,/*F2 red key*/                },
    {"REMOTE_F3          ", REMOTE_F3,/*F3 yellow key*/             },
    {"REMOTE_F4          ", REMOTE_F4,/*F4 blue key*/               },
    {"MYTEST             ", 0x31ceff00,/*F4 blue key*/              },
};

static int g_irkey_adapt_count = sizeof(g_irkey_adapt_array) / sizeof(IRKEY_ADAPT);
static int powerkey_down = 0;
static int mutekey_down = 0;
static int f1key_down = 0;
static int f2key_down = 0;
static int f3key_down = 0;
static int f4key_down = 0;

static void huawei_report_irkey(irkey_info_s rcv_irkey_info)
{
    int i = 0;
    for(i = 0; i<g_irkey_adapt_count; i++)
    {
        if( (rcv_irkey_info.irkey_datah == 0) &&
            (rcv_irkey_info.irkey_datal == g_irkey_adapt_array[i].irkey_value) )
        {
        	printf("keyvalue=H/L 0x%x/0x%x\n",rcv_irkey_info.irkey_datah,rcv_irkey_info.irkey_datal);
            break;
        }
    }
    if(i>=g_irkey_adapt_count)
    {
        printf("Error. get a invalid code. irkey_datah=0x%.8x,irkey_datal=0x%.8x.\n", 
               (int)rcv_irkey_info.irkey_datah, (int)rcv_irkey_info.irkey_datal);
    }
    else
    {
        printf("RECEIVE ---> %s\t", g_irkey_adapt_array[i].name);
        if(rcv_irkey_info.irkey_state_code == 1)
        {
            printf("KEYUP...");
        }
        printf("\n");
        
        if((rcv_irkey_info.irkey_datah == 0) && 
           (rcv_irkey_info.irkey_state_code == 0) &&
           (rcv_irkey_info.irkey_datal == REMOTE_POWER)) /*POWER*/
        {
            powerkey_down = 1;
        }
        else if((rcv_irkey_info.irkey_datah == 0) && 
                (rcv_irkey_info.irkey_state_code == 0) &&
                (rcv_irkey_info.irkey_datal == REMOTE_MUTE)) /*MUTE*/
        {
            mutekey_down = 1;
        }
        else if((rcv_irkey_info.irkey_datah == 0) && 
                (rcv_irkey_info.irkey_state_code == 0) &&
                (rcv_irkey_info.irkey_datal == REMOTE_F1)) /*F1*/
        {
            f1key_down = 1;
        }
        else if((rcv_irkey_info.irkey_datah == 0) && 
                (rcv_irkey_info.irkey_state_code == 0) &&
                (rcv_irkey_info.irkey_datal == REMOTE_F2)) /*F2*/
        {
            f2key_down = 1;
        }
        else if((rcv_irkey_info.irkey_datah == 0) && 
                (rcv_irkey_info.irkey_state_code == 0) &&
                (rcv_irkey_info.irkey_datal == REMOTE_F3)) /*F3*/
        {
            f3key_down = 1;
        }
        else if((rcv_irkey_info.irkey_datah == 0) && 
                (rcv_irkey_info.irkey_state_code == 0) &&
                (rcv_irkey_info.irkey_datal == REMOTE_F4)) /*F4*/
        {
            f4key_down = 1;
        }
    }
}

static void normal_report_irkey(irkey_info_s rcv_irkey_info)
{
    printf("RECEIVE ---> irkey_datah=0x%.8x, irkey_datal=0x%.8x\t", (int)(rcv_irkey_info.irkey_datah), (int)(rcv_irkey_info.irkey_datal));
    if(rcv_irkey_info.irkey_state_code == 1)
    {
        printf("KEYUP...");
    }
    printf("\n");
}


////////////////////////////////////////////////////////////////////////////////

static inline void ir_config_fun(int filp, hiir_dev_param dev_param)
{
    int tmp[2];

    ioctl(filp, IR_IOC_SET_CODELEN, dev_param.code_len);
    
    ioctl(filp, IR_IOC_SET_FORMAT, dev_param.codetype);

    ioctl(filp, IR_IOC_SET_FREQ, dev_param.frequence);

    tmp[0] = dev_param.leads_min;
    tmp[1] = dev_param.leads_max;
    ioctl(filp, IR_IOC_SET_LEADS, tmp);

    tmp[0] = dev_param.leade_min;
    tmp[1] = dev_param.leade_max;
    ioctl(filp, IR_IOC_SET_LEADE, tmp);

    tmp[0] = dev_param.sleade_min;
    tmp[1] = dev_param.sleade_max;
    ioctl(filp, IR_IOC_SET_SLEADE, tmp);

    tmp[0] = dev_param.cnt0_b_min;
    tmp[1] = dev_param.cnt0_b_max;
    ioctl(filp, IR_IOC_SET_CNT0_B, tmp);

    tmp[0] = dev_param.cnt1_b_min;
    tmp[1] = dev_param.cnt1_b_max;
    ioctl(filp, IR_IOC_SET_CNT1_B, tmp);
}

////////////////////////////////////////////////////////////////////////////////
/*
Default configuration.
Press down huawei's telecontroller randomly.
Check whether the report of the key is correct. 
Check whether the delay time of repeated key is correct.
Check whether the function is correct after set the delay time of repeated key again.  
*/
void Hi_IR_FUNC_TEST_001()
{
    int fp, res, i, count;
    int delay = 0;
    irkey_info_s rcv_irkey_info[4];
    
    powerkey_down = 0;
    mutekey_down = 0;
    f1key_down = 0;
    f2key_down = 0;
    f3key_down = 0;
    f4key_down = 0;

    printf("Hi_IR_FUNC_TEST_001 start...\n");
    printf("REMOTE codetype ...NEC with simple repeat code - uPD6121G\n");
    
    if( -1 == (fp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, fp);
        return;
    }

    ioctl(fp, IR_IOC_SET_ENABLE_KEYUP, 1);

    printf("REMOTE_POWER key to finish the test...\n");
    printf("REMOTE_MUTE  key to set repkey delay time...\n");
    while(1)
    {
        res = read(fp, rcv_irkey_info, sizeof(rcv_irkey_info));
        count = res / sizeof(irkey_info_s);
        if( (res > 0) && (res<=sizeof(rcv_irkey_info)) )
        {
            for(i=0;i<count;i++)
            {
                huawei_report_irkey(rcv_irkey_info[i]);
            }
        }
        else
        {
            printf("Hi_IR_FUNC_TEST_001 Error. read irkey device error. result=%d.\n", res);
        }

        if(powerkey_down)
        {
            printf("Hi_IR_FUNC_TEST_001 pass.\n\n");
            break;
        }
        if(mutekey_down)
        {
            mutekey_down = 0;
            printf("REMOTE_MUTE  key to set repkey delay time...\n");
            printf("Hi_IR_FUNC_TEST_001: input repkey delay = ");
            scanf("%d", &delay);
            ioctl(fp, IR_IOC_SET_REPKEY_TIMEOUTVAL, delay);
        }
    }

    close(fp);
}

/*
The right way to occupy the device exclusively: first time open the Hi_IR devive sucessfully ,
second time open the Hi_IR devive failure.
*/
void Hi_IR_FUNC_TEST_002()
{
    int fp, fp2;

    printf("Hi_IR_FUNC_TEST_002 start...\n");
    printf("REMOTE codetype ...NEC with simple repeat code - uPD6121G\n");
    
    if( -1 == (fp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_FUNC_TEST_002 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, fp);
        return;
    }

    if( -1 != (fp2 = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_FUNC_TEST_002 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, fp2);
        return;
    }
    close(fp2);
    close(fp2);
    close(fp2);

    close(fp);

    if( -1 == (fp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_FUNC_TEST_002 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, fp);
        return;
    }
    close(fp);

    printf("Hi_IR_FUNC_TEST_002 pass.\n\n");
}

/*
After a number of times to close the device,the device can be  successsfully opened.
*/
void Hi_IR_FUNC_TEST_003()
{
    int fp = 0;

    printf("Hi_IR_FUNC_TEST_003 start...\n");
    printf("REMOTE codetype ...NEC with simple repeat code - uPD6121G\n");
    
    if( -1 == (fp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_FUNC_TEST_003 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, fp);
        return;
    }
    close(fp);
    close(fp);
    close(fp);

    if( -1 == (fp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_FUNC_TEST_003 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, fp);
        return;
    }
    close(fp);

    printf("Hi_IR_FUNC_TEST_003 pass.\n\n");
}


/*
Test all ioctl command function
*/
void Hi_IR_FUNC_TEST_004()
{
    int filp;
    int i;
    hiir_dev_param tmp;

    printf("Hi_IR_FUNC_TEST_004 start...\n");
    printf("REMOTE codetype ...NEC with simple repeat code - uPD6121G\n");
    
    if( -1 == (filp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_FUNC_TEST_004 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, filp);
        return;
    }
    for(i = 0; i<16; i++)
    {
        ir_config_fun(filp, static_dev_param[i]);
        ioctl(filp, IR_IOC_GET_CONFIG, &tmp);
        if( 0 != memcmp(&tmp, &(static_dev_param[i]), sizeof(hiir_dev_param)) )
        {
            printf("Hi_IR_FUNC_TEST_004 ERROR. need check ioctl fun.\n");
            return;
        }
    }
    printf("Hi_IR_FUNC_TEST_004 pass.\n\n");
    close(filp);
}

/*
Press down telecontroller randomly.
Check whether the report of the key is correct. 
Check whether the delay time of repeated key is correct.
Check whether the key release message is correct.
Check whether the device's buffer is correct.  
*/
void Hi_IR_FUNC_TEST_005()
{
    /*
    Press down REMOTE_POWER key to finish the test:
    Press down REMOTE_F1 key to set support release key msg(0--no,1--yes);
    Press down REMOTE_F2 key to set support repeart key msg(0--no,1--yes);
    Press down REMOTE_F3 key to set set repeart key delay time.
    Press down REMOTE_F4 key to set device buffer length.
    */
    int filp = 0;
    int i = 0;
    int res = 0;
    irkey_info_s rcv_irkey_info;

    printf("Hi_IR_FUNC_TEST_005 start...\n");
    printf("REMOTE codetype ...NEC with simple repeat code - uPD6121G\n");

    powerkey_down = 0;
    mutekey_down = 0;
    f1key_down = 0;
    f2key_down = 0;
    f3key_down = 0;
    f4key_down = 0;

    if( -1 == (filp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_FUNC_TEST_005 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, filp);
        return;
    }
    ioctl(filp, IR_IOC_ENDBG, 1);

    printf("REMOTE_POWER key to finish the test...\n");
    printf("REMOTE_F1    key to set support release key msg(0-not support, not 0-support)...\n");
    printf("REMOTE_F2    key to set support repeart key msg(0-not support, not 0-support)...\n");
    printf("REMOTE_F3    key to set repkey delay time...\n");
    printf("REMOTE_F4    key to set device buffer length...\n");
    
    while(1)
    {
        res = read(filp, &rcv_irkey_info, sizeof(rcv_irkey_info));
        if( (res > 0) && (res<=sizeof(rcv_irkey_info)) )
        {
            huawei_report_irkey(rcv_irkey_info);
        }
        else
        {
            printf("Hi_IR_FUNC_TEST_005 Error. read irkey device error. result=%d.\n", res);
        }

        if(powerkey_down)
        {
            printf("Hi_IR_FUNC_TEST_005 pass.\n\n");
            break;
        }
        if(f1key_down)
        {
            f1key_down = 0;
            printf("REMOTE_F1    key to set support release key msg(0-not support, not 0-support)...\n");
            printf("input = ");
            scanf("%d", &i);
            ioctl(filp, IR_IOC_SET_ENABLE_KEYUP, i);
        }
        if(f2key_down)
        {
            f2key_down = 0;
            printf("REMOTE_F2    key to set support repeart key msg(0-not support, not 0-support)...\n");
            printf("input = ");
            scanf("%d", &i);
            ioctl(filp, IR_IOC_SET_ENABLE_REPKEY, i);
        }
        if(f3key_down)
        {
            f3key_down = 0;
            printf("REMOTE_F3    key to set repkey delay time...\n");
            printf("input = ");
            scanf("%d", &i);
            ioctl(filp, IR_IOC_SET_REPKEY_TIMEOUTVAL, i);
        }
        if(f4key_down)
        {
            f4key_down = 0;
            printf("REMOTE_F4    key to set device buffer length...\n");
            printf("input = ");
            scanf("%d", &i);
            ioctl(filp, IR_IOC_SET_BUF, i);
        }
    }
    
    close(filp);
}

/*
Press down TC9012 telecontroller randomly.
Check whether the report of the key is correct. 
Check whether the delay time of repeated key is correct.
Check whether the function is correct after set the delay time of repeated key again.  
*/
void Hi_IR_FUNC_TEST_006()
{
    int filp = 0;
    int i = 0;
    int res = 0;
    irkey_info_s rcv_irkey_info;

    printf("Hi_IR_FUNC_TEST_006 start...\n");
    printf("REMOTE codetype ...TC9012 - TC9012F/9243\n");
    
    if( -1 == (filp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_FUNC_TEST_006 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, filp);
        return;
    }
    
    ioctl(filp, IR_IOC_ENDBG, 1);
    
    ir_config_fun(filp, static_dev_param[4]);//TC9012F
    
    printf("random press 10 keys...\n");
    for(i = 0; i<10; i++)
    {
        res = read(filp, &rcv_irkey_info, sizeof(rcv_irkey_info));
        if( (res > 0) && (res<=sizeof(rcv_irkey_info)) )
        {
            normal_report_irkey(rcv_irkey_info);
        }
        else
        {
            printf("Hi_IR_FUNC_TEST_006 Error. read irkey device error. res=%d.\n", res);
        }
    }

    printf("Hi_IR_FUNC_TEST_006 pass.\n\n");
    close(filp);
}

/*
Press down NEC's telecontroller with full repeat code randomly.
Check whether the report of the key is correct. 
Check whether the delay time of repeated key is correct.
Check whether the function is correct after set the delay time of repeated key again.  
*/
void Hi_IR_FUNC_TEST_007()
{
    /* NEC with full repeat code */
    int filp = 0;
    int i = 0;
    int res = 0;
    irkey_info_s rcv_irkey_info;

    printf("Hi_IR_FUNC_TEST_007 start...\n");
    printf("REMOTE codetype ...NEC with full repeat code\n");
    
    if( -1 == (filp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_FUNC_TEST_007 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, filp);
        return;
    }
    ir_config_fun(filp, static_dev_param[5]);//NEC with full repeat code
    printf("random press 10 keys...\n");
    for(i = 0; i<10; i++)
    {
        res = read(filp, &rcv_irkey_info, sizeof(rcv_irkey_info));
        if( (res > 0) && (res<=sizeof(rcv_irkey_info)) )
        {
            normal_report_irkey(rcv_irkey_info);
        }
        else
        {
            printf("Hi_IR_FUNC_TEST_007 Error. read irkey device error. res=%d.\n", res);
        }
    }

    printf("Hi_IR_FUNC_TEST_007 pass.\n\n");
    close(filp);
}

/*
Press down SONY's telecontroller randomly.
Check whether the report of the key is correct. 
Check whether the delay time of repeated key is correct.
Check whether the function is correct after set the delay time of repeated key again.  
*/
void Hi_IR_FUNC_TEST_008()
{
    /* SONY */
    int filp = 0;
    int i = 0;
    int res = 0;
    irkey_info_s rcv_irkey_info;

    printf("Hi_IR_FUNC_TEST_008 start...\n");
    printf("REMOTE codetype ...SONY\n");
    
    if( -1 == (filp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_FUNC_TEST_008 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, filp);
        return;
    }
    ir_config_fun(filp, static_dev_param[12]);//NEC with full repeat code
    printf("random press 10 keys...\n");
    for(i = 0; i<10; i++)
    {
        res = read(filp, &rcv_irkey_info, sizeof(rcv_irkey_info));
        if( (res > 0) && (res<=sizeof(rcv_irkey_info)) )
        {
            normal_report_irkey(rcv_irkey_info);
        }
        else
        {
            printf("Hi_IR_FUNC_TEST_008 Error. read irkey device error. res=%d.\n", res);
        }
    }

    printf("Hi_IR_FUNC_TEST_008 pass.\n\n");
    close(filp);
}

/*
According to test program,randomly enter 13 numbers  to test input function.
*/
void Hi_IR_STRONG_TEST_001()
{
    int filp = 0;
    int i = 0;
    hiir_dev_param tmp;

    printf("Hi_IR_STRONG_TEST_001 start...\n");
    
    if( -1 == (filp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_STRONG_TEST_001 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, filp);
        return;
    }
    
    /* input and config */
    printf("input frequence = "); scanf("%d", &i); (tmp.frequence) = (U8)i;
    printf("input codetype = "); scanf("%d", &i); (tmp.codetype) = (U8)i;
    printf("input code_len = "); scanf("%d", &i); (tmp.code_len) = (U8)i;
    printf("input leads_min = "); scanf("%d", &i); (tmp.leads_min) = (U8)i;
    printf("input leads_max = "); scanf("%d", &i); (tmp.leads_max) = (U8)i;
    printf("input leade_min = "); scanf("%d", &i); (tmp.leade_min) = (U8)i;
    printf("input leade_max = "); scanf("%d", &i); (tmp.leade_max) = (U8)i;
    printf("input cnt0_b_min = "); scanf("%d", &i); (tmp.cnt0_b_min) = (U8)i;
    printf("input cnt0_b_max = "); scanf("%d", &i); (tmp.cnt0_b_max) = (U8)i;
    printf("input cnt1_b_min = "); scanf("%d", &i); (tmp.cnt1_b_min) = (U8)i;
    printf("input cnt1_b_max = "); scanf("%d", &i); (tmp.cnt1_b_max) = (U8)i;
    printf("input sleade_min = "); scanf("%d", &i); (tmp.sleade_min) = (U8)i;
    printf("input sleade_max = "); scanf("%d", &i); (tmp.sleade_max) = (U8)i;
    ir_config_fun(filp, tmp);

    printf("\n");

    /* then echo the config */
    ioctl(filp, IR_IOC_GET_CONFIG, &tmp);
    printf("output frequence = %d\n",tmp.frequence);
    printf("output codetype = %d\n",tmp.codetype);
    printf("output code_len = %d\n",tmp.code_len);
    printf("output leads_min = %d\n",tmp.leads_min);
    printf("output leads_max = %d\n",tmp.leads_max);
    printf("output leade_min = %d\n",tmp.leade_min);
    printf("output leade_max = %d\n",tmp.leade_max);
    printf("output cnt0_b_min = %d\n",tmp.cnt0_b_min);
    printf("output cnt0_b_max = %d\n",tmp.cnt0_b_max);
    printf("output cnt1_b_min = %d\n",tmp.cnt1_b_min);
    printf("output cnt1_b_max = %d\n",tmp.cnt1_b_max);
    printf("output sleade_min = %d\n",tmp.sleade_min);
    printf("output sleade_max = %d\n",tmp.sleade_max);

    printf("Hi_IR_STRONG_TEST_001 pass.\n\n");
    close(filp);
}

/*
Open device with ioctl function to check the range of legal paramers.
*/

void Hi_IR_STRONG_TEST_002()
{
    int filp = 0;
    hiir_dev_param in, out;

    printf("Hi_IR_STRONG_TEST_002 start...\n");
    
    if( -1 == (filp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_STRONG_TEST_002 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, filp);
        return;
    }

    /* Check the legal minimum of paramers */
    in = static_dev_param[0];
    in.codetype = 0;
    in.frequence = 1;
    ioctl(filp, IR_IOC_SET_FORMAT, 0);
    ioctl(filp, IR_IOC_SET_FREQ, 1);
    ioctl(filp, IR_IOC_GET_CONFIG, &out);
    if(0 != memcmp(&in, &out, sizeof(hiir_dev_param)))
    {
        printf("Hi_IR_STRONG_TEST_002 ERROR: critical input check fail.\n");
        return;
    }

    /* Check the legal maximum of paramers */
    in = static_dev_param[0];
    in.codetype = 3;
    in.frequence = 128;
    ioctl(filp, IR_IOC_SET_FORMAT, 3);
    ioctl(filp, IR_IOC_SET_FREQ, 128);
    ioctl(filp, IR_IOC_GET_CONFIG, &out);
    if(0 != memcmp(&in, &out, sizeof(hiir_dev_param)))
    {
        printf("Hi_IR_STRONG_TEST_002 ERROR: critical input check fail.\n");
        return;
    }

    /* Check the ilegal minimum of paramers */
    in = static_dev_param[0];
    in.codetype = -1;
    in.frequence = 0;
    ioctl(filp, IR_IOC_SET_FORMAT, -1);
    ioctl(filp, IR_IOC_SET_FREQ, 0);
    ioctl(filp, IR_IOC_GET_CONFIG, &out);
    if(0 == memcmp(&in, &out, sizeof(hiir_dev_param)))
    {
        printf("Hi_IR_STRONG_TEST_002 ERROR: critical input check fail.\n");
        return;
    }

    /* Check the ilegal maximum of paramers */
    in = static_dev_param[0];
    in.codetype = 4;
    in.frequence = 129;
    ioctl(filp, IR_IOC_SET_FORMAT, 4);
    ioctl(filp, IR_IOC_SET_FREQ, 129);
    ioctl(filp, IR_IOC_GET_CONFIG, &out);
    if(0 == memcmp(&in, &out, sizeof(hiir_dev_param)))
    {
        printf("Hi_IR_STRONG_TEST_002 ERROR: critical input check fail.\n");
        return;
    }

    printf("Hi_IR_STRONG_TEST_002 pass.\n\n");
    close(filp);
}

/*
Test for boundary value of repeart key delay time and device buffer length.
Open the device and sleep 1 second,then input at most 20 numbers at one time.
Should be checked by human being.
See print messages for other settings  
*/
void Hi_IR_STRONG_TEST_003()
{
    /*
    Press down REMOTE_POWER key to finish the test:
    Press down REMOTE_F1 key to set support release key msg(0--no,1--yes);
    Press down REMOTE_F2 key to set support repeart key msg(0--no,1--yes);
    Press down REMOTE_F3 key to set set repeart key delay time.
    Press down REMOTE_F4 key to set device buffer length.
    */
    int filp = 0;
    int i = 0;
    int res = 0;
    irkey_info_s rcv_irkey_info[20];

    printf("Hi_IR_FUNCHi_IR_STRONG_TEST_003_TEST_005 start...\n");
    printf("REMOTE codetype ...NEC with simple repeat code - uPD6121G\n");

    powerkey_down = 0;
    mutekey_down = 0;
    f1key_down = 0;
    f2key_down = 0;
    f3key_down = 0;
    f4key_down = 0;

    if( -1 == (filp = open("/dev/"HIIR_DEVICE_NAME, O_RDWR) ) )
    {
        printf("Hi_IR_STRONG_TEST_003 ERROR:can not open %s device. read return %d\n", HIIR_DEVICE_NAME, filp);
        return;
    }
    ioctl(filp, IR_IOC_ENDBG, 1);//open debug

    //ioctl(filp, IR_IOC_SET_ENABLE_REPKEY, 0);

    printf("REMOTE_POWER key to finish the test...\n");
    printf("REMOTE_F4    key to set device buffer length...\n");
    printf("Each loop will sleep 1s...\n");
    
    while(1)
    {
        res = read(filp, rcv_irkey_info, sizeof(rcv_irkey_info));
        if( (res > 0) && (res<=sizeof(rcv_irkey_info)) )
        {
            res = res / sizeof(irkey_info_s);
            printf("read %d unit key...\n", res);
            for(i = 0; i<res; i++)
            {
                huawei_report_irkey(rcv_irkey_info[i]);
            }
        }
        else
        {
            printf("Hi_IR_STRONG_TEST_003 Error. read irkey device error. result=%d.\n", res);
        }

        if(powerkey_down)
        {
            printf("Hi_IR_STRONG_TEST_003 pass.\n\n");
            break;
        }
        if(f4key_down)
        {
            f4key_down = 0;
            printf("REMOTE_F4    key to set device buffer length...\n");
            printf("input = ");
            scanf("%d", &i);
            ioctl(filp, IR_IOC_SET_BUF, i);
        }

        printf("sleep 1s...\n");
        sleep(1);
    }
    
    close(filp);
}


int  main(void)
{
    Hi_IR_FUNC_TEST_001();
    Hi_IR_FUNC_TEST_002();
    Hi_IR_FUNC_TEST_003();
    Hi_IR_FUNC_TEST_004();
    Hi_IR_FUNC_TEST_005();
    Hi_IR_FUNC_TEST_006();
    Hi_IR_FUNC_TEST_007();
    Hi_IR_FUNC_TEST_008();
    Hi_IR_STRONG_TEST_001();
    Hi_IR_STRONG_TEST_002();
    Hi_IR_STRONG_TEST_003();

    return 0;
}


