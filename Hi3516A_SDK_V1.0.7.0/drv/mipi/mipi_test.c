#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <string.h>

#include "hi_mipi.h"
#include "mipi_reg.h"
#include "hi_type.h"


void usage(void)
{
    
	printf(
			"\n"
			"Usage: ./test [options] [parameter1] ...\n"
			"Options: \n"
			"0--set mipi dev attr ,eg:              \n"
"ordinal init member: lane num(1--4),input_mode,0:LVDS, 1:D-PHY, 2:CMOS DC, 3:HiSPi\n"
"                     input data type,0:RAW10, 1:RAW12, 2:RAW14\n\n"
			"1--set mipi output clk edge,eg: output clk edge(0:up, 1:down)   \n\n"			
			"2--set mipi output msb,eg: input mode(0:MSB,1:REVERSE)        \n\n"
			"3--set mipi input Virtual Channel and input data type,eg: \n"
"ordinal init member:Virtual Channel(1--4), input data type 0:RAW10, 1:RAW12, 2:RAW14   \n\n"			
			"4--set mipi input clk edge, eg: input clkd edge(0:up ,1:down) \n\n"			
			"5--set mipi phy bias eg: \n"
"ordinal init member:voltage ctrl (0:Using BGR Circuit ,1:Resistance Split), current ctrl0(0:Using BGR Circuit, 1:Resistance Split)\n\n"						
            "6--set mipi phy data lane delay, eg: \n"
"ordinal init member: phy delay clk(0--7),phy delay d0(0--7),phy delay d1(0--7),phy delay d2(0--7),phy delay d3(0--7)\n\n"
            "7--set mipi phy fsm timeout, eg: \n"
"ordinal init member: clk enable(0:clock disabel ,1:clock enable),data enable(0:disabel ,1:enable),time(0--16777215,default:5046271)\n\n"
            "8--set mipi phy fsm tim param, eg: \n"
"ordinal init member: data_lp00_cyc(0--63,default:6),data_hs0_cyc(0--63,default:12),clk_lp00_cyc(0--63, default:11),clk_hs0_cyc(0--63, default:26)\n\n"
            "9--set mipi memory clock enabel, eg : 0: disabel, 1: enable\n\n" 
            "10--set mipi csi2 mask1 eg : 0x0000000--0xffffffff\n" 
            "11--set mipi csi2 mask2 eg : 0x0000000--0xffffffff\n"
            "12--set mipi intr mask  eg : 0x0000000--0xffffffff\n"
            "13--set lvds err lvds \n"
            "q or Q---quit                 \n"
           
    );
    
	exit(1);
}

combo_dev_attr_t MIPI_4lane_SENSOR_OV4688_12BIT_ATTR = 
{
    .input_mode = INPUT_MODE_MIPI,  
    {
        .mipi_attr =    
        {
            .raw_data_type = RAW_DATA_12BIT,
            .lane_id = {0, 1, 2, 3, -1, -1, -1, -1},
        }
    }    
};

combo_dev_attr_t LVDS_4lane_SENSOR_IMX136_12BIT_1080_NOWDR_ATTR =
{
    /* input mode */
    .input_mode = INPUT_MODE_LVDS,
    {
        .lvds_attr = {
            .img_size = {1920, 1080},
            HI_WDR_MODE_NONE,
            LVDS_SYNC_MODE_SAV,
            RAW_DATA_12BIT,
            LVDS_ENDIAN_BIG,
            LVDS_ENDIAN_BIG,
            .lane_id = {0, 1, 2, 3, -1, -1, -1, -1},
            .sync_code = {
                    {{0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}},

                    {{0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}},

                    {{0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}},
                    
                    {{0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}},
                    
                    {{0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}},
                        
                    {{0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}},

                    {{0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}},
                    
                    {{0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}, 
                    {0xab0, 0xb60, 0x800, 0x9d0}}
                     
               }
        }
    }
};

static int _atoul(const char *str, unsigned int *pvalue)
{
	unsigned int result=0;

	while (*str)
	{
		if (isdigit((int)*str))
		{
			if ((result<429496729) || ((result==429496729) && (*str<='9')))
			{
				result = result*10 + (*str)-'0';
			}
			else
			{
				*pvalue = result;
				return -1;
			}
		}
		else
		{
			*pvalue=result;
			return -1;
		}
		str++;
	}
    
	*pvalue=result;
	return 0;
}


#define ASC2NUM(ch) (ch - '0')
#define HEXASC2NUM(ch) (ch - 'A' + 10)

static int  _atoulx(const char *str, unsigned int *pvalue)
{
	unsigned int   result=0;
	unsigned char  ch;

	while (*str)
	{
		ch=toupper(*str);
		if (isdigit(ch) || ((ch >= 'A') && (ch <= 'F' )))
		{
			if (result < 0x10000000)
			{
				result = (result << 4) + ((ch<='9')?(ASC2NUM(ch)):(HEXASC2NUM(ch)));
			}
			else
			{
				*pvalue=result;
				return -1;
			}
		}
		else
		{
			*pvalue=result;
			return -1;
		}
		str++;
	}

	*pvalue=result;
	return 0;
}

/*used for convert hex value from string to int*/
static int str_to_num(const char *str, unsigned int *pvalue)
{
	if ( *str == '0' && (*(str+1) == 'x' || *(str+1) == 'X') )
        {
        	if (*(str+2) == '\0')
            {
        		return -1;
        	}
            else
            {
    			return _atoulx(str+2, pvalue);
        	}
        }
	else 
    {
		return _atoul(str,pvalue);
    }
}


int main(int argc, const char *argv[])
{
	int ret = -1;
	int fd = -1;
	const char *dev_name = "/dev/hi_mipi";
    combo_dev_attr_t dev_attr;
    unsigned int evalue,value;
    HI_BOOL en;
    input_mode_t phy_mode = INPUT_MODE_MIPI;
    lvds_sync_mode_e  sync_mode;
    sync_mode = LVDS_SYNC_MODE_SAV;
    /*lvds_dev_attr_t  lvds_attr   = {{1280,720},
                                    {HI_WDR_MODE_NONE},
                                    {LVDS_SYNC_MODE_SAV},
                                    {LVDS_RAW_DATA_10BIT},
                                    {HIGH_BIT_PRIORITY},
                                    {0, 1, 2, 3, -1, -1, -1, -1},
                                    {{0x2ac, 0x2d8, 0x200, 0x274}, 
                                   {0x2ac, 0x2d8, 0x200, 0x274}, 
                                   {0x2ac, 0x2d8, 0x200, 0x274}, 
                                   {0x2ac, 0x2d8, 0x200, 0x274}}
                                   };*/
    if (argc < 2)
    {
    	usage();
    	return 0;
    }
    
    fd = open(dev_name, O_RDWR);    
    if (fd < 0) 
    {
    	printf("open %s failed\n", dev_name);
    	return -1;
    }
    
    if (_atoul(argv[1], &value))
    {
        printf("input error\n");
        close(fd);
        return -1;
    }

    switch (value)
    {
        case 0:          
        {  
            if (argc < 3)
            {
                usage();
                return 0;
            }
            
            if (_atoul(argv[2], &evalue))
            {
                printf("input error\n");
                close(fd);
                return -1;
            }            
            dev_attr.input_mode = evalue; 
            //dev_attr.input_mode = phy_mode;
            printf("dev_attr.input_mode: %d\n", dev_attr.input_mode);
            
            if (INPUT_MODE_MIPI == dev_attr.input_mode)
            {
                short lane_id[LVDS_LANE_NUM]= {0, 1, 2, 3, -1, -1, -1, -1};
                dev_attr.mipi_attr.raw_data_type = RAW_DATA_10BIT;
                memcpy(dev_attr.mipi_attr.lane_id, lane_id, sizeof(lane_id));   
            }
            else if ((INPUT_MODE_LVDS == dev_attr.input_mode)||
                    (INPUT_MODE_SUBLVDS == dev_attr.input_mode))
            {    
                dev_attr.lvds_attr.raw_data_type = RAW_DATA_10BIT;    
                
                short lane_id[LVDS_LANE_NUM]= {0, 1, 2, 3, -1, -1, -1, -1};
                unsigned short sync_code[LVDS_LANE_NUM][WDR_VC_NUM][SYNC_CODE_NUM];
                
                if (INPUT_MODE_LVDS == dev_attr.input_mode)
                {
                    dev_attr.lvds_attr.sync_mode = LVDS_SYNC_MODE_SAV;
                    
                    short temp_lane_id[LVDS_LANE_NUM] = {0, 1, 2, 3, -1, -1, -1, -1}; 
                    
                    if(RAW_DATA_10BIT == dev_attr.lvds_attr.raw_data_type)
                    {
                       short temp_sync_code[LVDS_LANE_NUM][WDR_VC_NUM][SYNC_CODE_NUM] =
                        {
                            {{0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}},

                            {{0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}},

                            {{0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}},
                            
                            {{0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}},

                            {{0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}},

                            {{0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}},

                            {{0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}},
                                
                            {{0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}, 
                            {0x2ac, 0x2d8, 0x200, 0x274}}                        
                        };                      
                        memcpy(sync_code,temp_sync_code,sizeof(temp_sync_code));
                    }                
                    else if (RAW_DATA_12BIT == dev_attr.lvds_attr.raw_data_type)
                    {
                       short temp_sync_code[LVDS_LANE_NUM][WDR_VC_NUM][SYNC_CODE_NUM] =
                        {
                            {{0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}},

                            {{0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}},

                            {{0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}},
                            
                            {{0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}},
                            
                            {{0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}},
                                
                            {{0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}},

                            {{0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}},
                            
                            {{0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}, 
                            {0xab0, 0xb60, 0x800, 0x9d0}}
                             
                       };
                       
                    memcpy(sync_code,temp_sync_code,sizeof(temp_sync_code));
                    }                     
                    memcpy(lane_id,temp_lane_id,sizeof(temp_lane_id));
                    
                }
            else if (INPUT_MODE_SUBLVDS == dev_attr.input_mode)
            {
                dev_attr.lvds_attr.sync_mode = LVDS_SYNC_MODE_SOL;    
                short temp_lane_id[LVDS_LANE_NUM] = {0, 2, -1, -1, 1, 3, -1, -1};
                short temp_sync_code[LVDS_LANE_NUM][WDR_VC_NUM][SYNC_CODE_NUM] =                
                {
                          {{0x2, 0x3, 0x0, 0x1}, //PHY0_lane0
                          {0x2, 0x3, 0x0, 0x1},
                          {0x2, 0x3, 0x0, 0x1},
                          {0x2, 0x3, 0x0, 0x1}},

                          {{0x6, 0x7, 0x4, 0x5}, //PHY0_lane1
                          {0x6, 0x7, 0x4, 0x5},
                          {0x6, 0x7, 0x4, 0x5},
                          {0x6, 0x7, 0x4, 0x5}},

                          {{0xa, 0xb, 0x8, 0x9}, //PHY0_lane2
                          {0xa, 0xb, 0x8, 0x9},
                          {0xa, 0xb, 0x8, 0x9},
                          {0xa, 0xb, 0x8, 0x9}},

                          {{0xa, 0xb, 0x8, 0x9}, //PHY0_lane3
                          {0xa, 0xb, 0x8, 0x9},
                          {0xa, 0xb, 0x8, 0x9},
                          {0xa, 0xb, 0x8, 0x9}},

                          {{0x12, 0x13, 0x10, 0x11},//PHY1_lane0
                          {0x12, 0x13, 0x10, 0x11},
                          {0x12, 0x13, 0x10, 0x11},
                          {0x12, 0x13, 0x10, 0x11}},

                          {{0x16, 0x17, 0x14, 0x15}, //PHY1_lane1
                          {0x16, 0x17, 0x14, 0x15},
                          {0x16, 0x17, 0x14, 0x15},
                          {0x16, 0x17, 0x14, 0x15}},

                          {{0x1a, 0x1b, 0x18, 0x19}, //PHY1_lane2
                          {0x1a, 0x1b, 0x18, 0x19},
                          {0x1a, 0x1b, 0x18, 0x19},
                          {0x1a, 0x1b, 0x18, 0x19}},

                          {{0x1a, 0x1b, 0x18, 0x19}, //PHY1_lane3
                          {0x1a, 0x1b, 0x18, 0x19},
                          {0x1a, 0x1b, 0x18, 0x19},
                          {0x1a, 0x1b, 0x18, 0x19}}
                   }; 
                memcpy(lane_id,temp_lane_id,sizeof(temp_lane_id));
                memcpy(sync_code,temp_sync_code,sizeof(temp_sync_code));
            }
            else
            {
                printf("set hispi/cmos\n");//hispi,cmos
            }
            dev_attr.lvds_attr.img_size.width = 1920;
            dev_attr.lvds_attr.img_size.height = 1080;
            dev_attr.lvds_attr.wdr_mode = HI_WDR_MODE_NONE;
            dev_attr.lvds_attr.data_endian= LVDS_ENDIAN_BIG;
            dev_attr.lvds_attr.sync_code_endian= LVDS_ENDIAN_BIG;
            memcpy(dev_attr.lvds_attr.lane_id, lane_id, sizeof(lane_id));               
            memcpy(dev_attr.lvds_attr.sync_code, sync_code, sizeof(sync_code));   
            }   

            if (ioctl(fd, HI_MIPI_SET_DEV_ATTR, &dev_attr))
            {
                printf("set mipi dev fail\n");
                close(fd);
                return -1;
            }            
            
            break;
        }

        case 1 : 
        {
            if (_atoul(argv[2], &en))
            {
                printf("input error\n");
                close(fd);
                return -1;
            }            
            if (ioctl(fd, HI_MIPI_SET_OUTPUT_CLK_EDGE, &en))
            {
                printf("set mipi output clk edge fail\n");
                close(fd);
                return -1;
            }
            break;
        }       
        
        case 2 :   
        {                 
            if (_atoul(argv[2], &en))
            {
                printf("input error\n");
                close(fd);
                return -1;
            }       
            if (ioctl(fd, HI_MIPI_SET_OUTPUT_MSB, &en))
            {
                printf("set mipi output msb fail\n");
                close(fd);
                return -1;
            }
            break;
        } 
        case 14:
        {
            memcpy(&dev_attr, &LVDS_4lane_SENSOR_IMX136_12BIT_1080_NOWDR_ATTR, sizeof(combo_dev_attr_t));
            
            {
            /*1. {0, 2, -1, -1, -1, -1, -1, -1} */
            short temp_lane_id[LVDS_LANE_NUM] = {0, 2, -1, -1, -1, -1, -1, -1};
            memcpy(&dev_attr.lvds_attr.lane_id, temp_lane_id, sizeof(temp_lane_id));
            printf("err: 0x%x\n", ioctl(fd, HI_MIPI_SET_DEV_ATTR, &dev_attr));
            }
            {
            /*2. {0, 3, -1, -1, -1, -1, -1, -1} */
            short temp_lane_id[LVDS_LANE_NUM] = {0, 3, -1, -1, -1, -1, -1, -1};
            memcpy(&dev_attr.lvds_attr.lane_id, temp_lane_id, sizeof(temp_lane_id));
            printf("err: 0x%x\n", ioctl(fd, HI_MIPI_SET_DEV_ATTR, &dev_attr));
            }
            {
            /*3. {0, 1, -1, -1, 4, 6, -1, -1} */
            short temp_lane_id[LVDS_LANE_NUM] = {0, 1, -1, -1, 4, 6, -1, -1};
            memcpy(&dev_attr.lvds_attr.lane_id, temp_lane_id, sizeof(temp_lane_id));
            printf("err: 0x%x\n", ioctl(fd, HI_MIPI_SET_DEV_ATTR, &dev_attr));
            }
            {
            /*4. {0, 1, -1, -1, 2, 3, -1, -1} */
            short temp_lane_id[LVDS_LANE_NUM] = {0, 1, -1, -1, 2, 3, -1, -1};
            memcpy(&dev_attr.lvds_attr.lane_id, temp_lane_id, sizeof(temp_lane_id));
            printf("err: 0x%x\n", ioctl(fd, HI_MIPI_SET_DEV_ATTR, &dev_attr));
            }

            if (ioctl(fd, HI_MIPI_SET_DEV_ATTR, &dev_attr))
            {
                printf("set mipi dev fail\n");
                close(fd);
                return -1;
            }    

            break;
        }

        case 15:
        {
            memcpy(&dev_attr, &MIPI_4lane_SENSOR_OV4688_12BIT_ATTR, sizeof(combo_dev_attr_t));
            printf("ok: 0x%x\n", ioctl(fd, HI_MIPI_SET_DEV_ATTR, &dev_attr));
            {
            /*1. (0, 2, -1, -1) */
            short temp_lane_id[LVDS_LANE_NUM] = {0, 2, -1, -1, -1, -1, -1, -1};
            memcpy(&dev_attr.mipi_attr.lane_id, temp_lane_id, sizeof(temp_lane_id));
            printf("err: 0x%x\n", ioctl(fd, HI_MIPI_SET_DEV_ATTR, &dev_attr));
            }
            {
            /*1. {0, 1, -1, -1, 2, 3, -1, -1} */
            short temp_lane_id[LVDS_LANE_NUM] = {0, 1, -1, -1, 2, 3, -1, -1};
            memcpy(&dev_attr.mipi_attr.lane_id, temp_lane_id, sizeof(temp_lane_id));
            printf("err: 0x%x\n", ioctl(fd, HI_MIPI_SET_DEV_ATTR, &dev_attr));
            }

            break;
        }
        
        default :
        {
            printf("invalid himipi input\n");
            break;
        }
    }

err1 :
    close(fd);
    return 0;
    
}

