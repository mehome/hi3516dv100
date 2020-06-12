/*
 *
 * Copyright (c) 2006 Hisilicon Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 *
 * History:
 *      29-Sep-2014 create this file
 */


#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/slab.h>
//#include <linux/smp_lock.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#ifndef CONFIG_HISI_SNAPSHOT_BOOT
#include <linux/miscdevice.h>
#endif
#include <linux/delay.h>

#include <linux/proc_fs.h>
#include <linux/poll.h>

#include <asm/bitops.h>
#include <asm/uaccess.h>
#include <asm/irq.h>

#include <linux/moduleparam.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/reboot.h>
#include <linux/notifier.h>
#include <linux/i2c.h>

#include "ak7756en.h"
#include "ak7756en_def.h"
#include "ak7756en_pram.h"
#include "ak7756en_cram.h"

#ifdef CONFIG_HISI_SNAPSHOT_BOOT
#include "himedia.h"
#endif

#define CHIP_NUM 1
#define DEV_NAME "ak7756en"
#define DEBUG_LEVEL 1
#define DPRINTK(level,fmt,args...) do{ if(level < DEBUG_LEVEL)\
            printk(KERN_INFO "%s [%s ,%d]: " fmt "\n",DEV_NAME,__FUNCTION__,__LINE__,##args);\
    }while(0)
#define CEILING_2_POWER(x,a)     ( ((x) + ((a) - 1) ) & ( ~((a) - 1) ) )
//#define DBG_AK7756EN

static unsigned int  open_cnt = 0;

#ifdef CONFIG_HISI_SNAPSHOT_BOOT
static struct himedia_device s_stAk7756enDevice;
#endif

static struct i2c_client* ak7756_client;

static struct i2c_board_info ak7756_i2c_info =
{
    I2C_BOARD_INFO("ak7756", AK7756EN_I2C_SLAVE_ADDR),
};
static unsigned char* pu8Ak77dspRAM = NULL;
static unsigned char* pu8PhyAk77dspCRAM = NULL;
static unsigned char* pu8PhyAk77dspPRAM = NULL;

static int ak7756en_device_init( void );

extern int hi_i2c_dma_write(const struct i2c_client* client, unsigned int data_addr, unsigned int reg_addr, unsigned int reg_addr_num, unsigned int length);

static int i2c_client_init(void)
{
    struct i2c_adapter* i2c_adap;

    i2c_adap      = i2c_get_adapter(2);
    ak7756_client = i2c_new_device(i2c_adap, &ak7756_i2c_info);

    i2c_put_adapter(i2c_adap);

    return 0;
}

static void i2c_client_exit(void)
{
    i2c_unregister_device(ak7756_client);
}

void hi_i2c_read_word(unsigned char devaddress, unsigned char address)
{
    unsigned char ret_data0 = 0xFF;
    unsigned char ret_data1 = 0xFF;
    int ret;
    struct i2c_client* client = ak7756_client;
    unsigned char buf[2];

    buf[0] = address;
    ret = i2c_master_recv(client, buf, 2);
    if (ret >= 0)
    {
        ret_data0 = buf[0];
        ret_data1 = buf[1];
    }
#ifdef DBG_AK7756EN
    printk("Func:%s, line:%d, ret_data0:0x%x, ret_data1:0x%x.\n", __FUNCTION__, __LINE__, ret_data0, ret_data1);
#endif
    //return ret_data;
}


unsigned char hi_i2c_read_byte(unsigned char devaddress, unsigned char address)
{
    unsigned char ret_data = 0xFF;
    int ret;
    struct i2c_client* client = ak7756_client;
    unsigned char buf[2];

    buf[0] = address;
    ret = i2c_master_recv(client, buf, 1);
    if (ret >= 0)
    {
        ret_data = buf[0];
    }
    return ret_data;
}

int hi_i2c_write_byte(unsigned char devaddress, unsigned char address, unsigned char data)
{
    int ret;
    unsigned char buf[2];
    struct i2c_client* client = ak7756_client;

    buf[0] = address;
    buf[1] = data;

    ret = i2c_master_send(client, buf, 2);
    return ret;
}

int ak7756en_read(unsigned char chip_addr, unsigned char reg_addr)
{
    return hi_i2c_read_byte(chip_addr, reg_addr);
}

void ak7756en_write(unsigned char chip_addr, unsigned char reg_addr, unsigned char value)
{
    hi_i2c_write_byte(chip_addr, reg_addr, value);
}

int ak7756en_download_ramdata( void )
{
    int ret = 0;
    //int crc = 0;
    struct i2c_client* client = ak7756_client;

#ifdef DBG_AK7756EN
    printk("Func:%s, line:%d, pu8PhyAk77dspCRAM :0x%p, pu8PhyAk77dspPRAM:0x%p!\n", __FUNCTION__, __LINE__, pu8PhyAk77dspCRAM, pu8PhyAk77dspPRAM);
#endif

    ret = hi_i2c_dma_write(client, (unsigned int)pu8PhyAk77dspCRAM, 0xB4, 1, sizeof(ak77dspCRAM));
    if (0 != ret)
    {
        printk("Func:%s, line:%d, ak7756 download data to cram failed!\n", __FUNCTION__, __LINE__);
        return ret;
    }
    msleep(10);

    //crc = hi_i2c_read_byte(0x30, 0x72);
    //printk("Func:%s, line:%d, cram crc:0x%x\n", __FUNCTION__, __LINE__, crc);

    ret = hi_i2c_dma_write(client, (unsigned int)pu8PhyAk77dspPRAM, 0xB8, 1, sizeof(ak77dspPRAM));
    if (0 != ret)
    {
        printk("Func:%s, line:%d, ak7756 download data to pram failed!\n", __FUNCTION__, __LINE__);
        return ret;
    }

    //crc = hi_i2c_read_byte(0x30, 0x72);
    //printk("Func:%s, line:%d, pram crc:0x%x\n", __FUNCTION__, __LINE__, crc);

    return 0;
}

void ak7756en_reg_dump(unsigned int reg_num)
{
    unsigned int i = 0;
    for (i = 0; i < reg_num; i++)
    {
        printk("reg%d =%x,", i, ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, i + AK7756_READ_REG_BASEADDR));
        if (0 == ((i + 1) % 8))
        {
            printk("\n");
        }
    }
}

void ak7756en_soft_reset( void )
{
    /* soft reset */
    /* clock reset */
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x02 + AK7756_WRITE_REG_BASEADDR, 0x00);
    /* codec reset, dsp reset */
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, 0x00);
    //msleep(100);

    /* control register 0: slave mode 4, clock source XTI=12.288MHz, fs=8KHz,  Bclk=64fs */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x00 + AK7756_WRITE_REG_BASEADDR, 0x40);

    /* control register 1: no crc check, fs=8KHz, Bclk=64fs, dsp process step=9216 */
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x01 + AK7756_WRITE_REG_BASEADDR, 0x00);


    //msleep(100);
    /* download pram  and cram data to dsp */
    //ak7756en_download_ramdata();
    //msleep(100);

    /* control register 2: I2S mode, manu power down, clock reset */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x02 + AK7756_WRITE_REG_BASEADDR, 0x42);

    /* control register 3: watchdog enable, DLRAM setting */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x03 + AK7756_WRITE_REG_BASEADDR, 0x00);

    /* control register 4: DLYRAM pointer mode, DRAM Addressing Select, WAVM mode, mem align */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x04 + AK7756_WRITE_REG_BASEADDR, 0x00);

    /* control register 5: output DOUT2, input DIN MSB 24bit */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x05 + AK7756_WRITE_REG_BASEADDR, 0x20);

    /* control register 6: output DOUT2 MSB 24bit, output DOUT1 MSB 24bit */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x06 + AK7756_WRITE_REG_BASEADDR, 0x00);

    /* control register 7: dsp jx disable, output DOUT3 enable, power down VSS */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x07 + AK7756_WRITE_REG_BASEADDR, 0x38);

    /* control register 8: input DIN2, blck disable, lrck disable, DOUT2 enable, DOUT1 disable */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x08 + AK7756_WRITE_REG_BASEADDR, 0x78);

    /* control register 9: mic gain 24db, differential input */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x09 + AK7756_WRITE_REG_BASEADDR, 0x80);

    /* control register 10: mic/ADC/DAC/lineout/ power up, codec/dsp reset */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, 0xD0);

    /* control register 11: EEPROM download failed, download completed */
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0B + AK7756_WRITE_REG_BASEADDR, 0x00);

    /* clock reset release*/
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x02 + AK7756_WRITE_REG_BASEADDR, 0x42);

    /* codec reset release */
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, 0xD8);

    /* control register 1: crc check, fs=8KHz, Bclk=64fs, dsp process step=9216 */
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x01 + AK7756_WRITE_REG_BASEADDR, 0x80);
    msleep(10);
    /* download pram  and cram data to dsp */
    ak7756en_download_ramdata();
    msleep(10);
    /* control register 1: no crc check, fs=8KHz, Bclk=64fs, dsp process step=9216 */
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x01 + AK7756_WRITE_REG_BASEADDR, 0x00);

    /* dsp reset release */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, 0xDC);
}

/* device open. set counter */
static int ak7756en_open(struct inode* inode, struct file* file)
{
    if (0 == open_cnt++)
    {
        return 0;
    }

    return -1 ;
}

/* Close device, Do nothing! */
static int ak7756en_close(struct inode* inode, struct file* file)
{
    open_cnt--;

    return 0;
}

static long ak7756en_ioctl(struct file* file, unsigned int cmd, unsigned long arg)
{
    unsigned int __user* argp = (unsigned int __user*)arg;
    Ak7756_Ctrl temp;
    Ak7756_Ctrl* Audio_Ctrl = NULL;

    Control_Register0 	Ctrl_Reg0;
    Control_Register1 	Ctrl_Reg1;
    Control_Register2 	Ctrl_Reg2;
    Control_Register5 	Ctrl_Reg5;
    Control_Register6 	Ctrl_Reg6;
    Control_Register9 	Ctrl_Reg9;
    Control_Register10 	Ctrl_Reg10;

    if (NULL != argp)
    {
        if (copy_from_user(&temp, argp, sizeof(Ak7756_Ctrl)))
        {
            return -EFAULT;
        }
    }

    Audio_Ctrl = &temp;

    /* clock reset */
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x02 + AK7756_WRITE_REG_BASEADDR, 0x40);
    /* codec reset, dsp reset */
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, 0xd0);

    switch (cmd)
    {
        case SET_AK7756_SAMPLE_RATE: //sample rate 8K/16K
            /* control register 1: DFS */
#ifdef DBG_AK7756EN
            printk("Func:%s, line:%d, ak7756en sampleRate %d\n", __FUNCTION__, __LINE__, Audio_Ctrl->SampleRate);
#endif
            Ctrl_Reg1.b8 = ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x01 + AK7756_READ_REG_BASEADDR);
            Ctrl_Reg1.bit.dfs  = Audio_Ctrl->SampleRate;
            ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x01 + AK7756_WRITE_REG_BASEADDR, Ctrl_Reg1.b8);
            break;
        case SET_AK7756_DATA_BITWIDTH: //bitwidth 24bit/16bit
            if (Audio_Ctrl->BitWidth <= 5)
            {
                Ctrl_Reg5.b8 = ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x05 + AK7756_READ_REG_BASEADDR);
                Ctrl_Reg5.bit.dif = Audio_Ctrl->BitWidth;
                ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x05 + AK7756_WRITE_REG_BASEADDR, Ctrl_Reg5.b8);

                Ctrl_Reg6.b8 = ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x06 + AK7756_READ_REG_BASEADDR);
                Ctrl_Reg6.bit.dof1 = Audio_Ctrl->BitWidth;
                Ctrl_Reg6.bit.dof2 = Audio_Ctrl->BitWidth;
                ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x06 + AK7756_WRITE_REG_BASEADDR, Ctrl_Reg6.b8);
            }
            else
            {
                printk("Func:%s, line:%d, ak7756en unsupport bitwidth %d.\n", __FUNCTION__, __LINE__, Audio_Ctrl->BitWidth);
                /* clock reset release*/
                //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x02 + AK7756_WRITE_REG_BASEADDR, 0x82);
                /* codec reset release, dsp reset release */
                //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, 0xDC);
                return -1;
            }
            break;
        case SET_AK7756_TRANSFER_MODE: //I2S/PCM choose
            Ctrl_Reg2.b8 = ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x02 + AK7756_READ_REG_BASEADDR);
            Ctrl_Reg2.bit.difpcm = Audio_Ctrl->TransMode;
            Ctrl_Reg2.bit.difi2s = ~Audio_Ctrl->TransMode;
            ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x02 + AK7756_WRITE_REG_BASEADDR, Ctrl_Reg2.b8);
            break;
        case SET_AK7756_CTRL_MODE:
            Ctrl_Reg0.b8 = ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x00 + AK7756_READ_REG_BASEADDR);
            if (1 == Audio_Ctrl->CtrlMode)
            {
                Ctrl_Reg0.bit.ckm = 6;
            }
            else
            {
                Ctrl_Reg0.bit.ckm = 4;
            }
            Ctrl_Reg0.bit.bitfs = Audio_Ctrl->BitFs;
            ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x00 + AK7756_WRITE_REG_BASEADDR, Ctrl_Reg0.b8);

            /* clock config */
            Ctrl_Reg1.b8 = ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x01 + AK7756_READ_REG_BASEADDR);
            Ctrl_Reg1.bit.dfs = Audio_Ctrl->SampleRate;
            ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x01 + AK7756_WRITE_REG_BASEADDR, Ctrl_Reg0.b8);
            break;
        case SET_AK7756_DAC_VOL_CTRL: //DAC gain
            Ctrl_Reg9.b8 = ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x09 + AK7756_READ_REG_BASEADDR);
            Ctrl_Reg9.bit.mgain = Audio_Ctrl->MicGain;
            ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x09 + AK7756_WRITE_REG_BASEADDR, Ctrl_Reg9.b8);
            break;
        case SET_AK7756_ADC_POWER_SETUP:
            Ctrl_Reg10.b8 = ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_READ_REG_BASEADDR);
            Ctrl_Reg10.bit.pmadc = Audio_Ctrl->PowerUp;
            ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, Ctrl_Reg10.b8);
            break;
        case SET_AK7756_DAC_POWER_SETUP:
            Ctrl_Reg10.b8 = ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_READ_REG_BASEADDR);
            Ctrl_Reg10.bit.pmdac = Audio_Ctrl->PowerUp;
            ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, Ctrl_Reg10.b8);
            break;
        case AK7756_SOFT_RESET:
            ak7756en_soft_reset();
            break;
        case AK7756_REG_DUMP:
            ak7756en_reg_dump(11);
            break;
        default:
            break;
    }

    /* clock reset release*/
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x02 + AK7756_WRITE_REG_BASEADDR, 0x42);
    /* codec reset release, dsp reset release */
    //ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, 0xDC);

    return 0;
}

#ifdef CONFIG_HISI_SNAPSHOT_BOOT
static int ak7756en_freeze(struct himedia_device* pdev)
{
    printk(KERN_ALERT "%s  %d\n", __FUNCTION__, __LINE__);

    return 0;
}

static int ak7756en_restore(struct himedia_device* pdev)
{
    if (ak7756en_device_init() < 0)
    {
        printk(KERN_ALERT "%s  %d, ak7756en device init fail!\n", __FUNCTION__, __LINE__);
        return -1;
    }

    printk(KERN_ALERT "%s  %d\n", __FUNCTION__, __LINE__);

    return 0;
}
#endif

/*
 *  The various file operations we support.
 */

static struct file_operations ak7756en_fops =
{
    .owner			= THIS_MODULE,
    .unlocked_ioctl	= ak7756en_ioctl,
    .open			= ak7756en_open,
    .release		= ak7756en_close
};

#ifdef CONFIG_HISI_SNAPSHOT_BOOT
struct himedia_ops stAk7756enDrvOps =
{
    .pm_freeze  = ak7756en_freeze,
    .pm_restore = ak7756en_restore
};
#else
static struct miscdevice ak7756en_dev =
{
    MISC_DYNAMIC_MINOR,
    DEV_NAME,
    &ak7756en_fops,
};
#endif

static int ak7756en_reboot(struct notifier_block* self, unsigned long data, void* pdata)
{
    /* HPLOUT is mute */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, 0x20);

    /* HPROUT is mute */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x08 + AK7756_WRITE_REG_BASEADDR, 0xE0);

    printk("Func:%s, line:%d, system reboot######\n", __FUNCTION__, __LINE__);

    return 0;
}

static struct notifier_block ak7756en_reboot_notifier =
{
    .notifier_call = ak7756en_reboot,
};

static int ak7756en_device_init( void )
{
    unsigned int uiBufferLen = 0;
    unsigned int uiCRAMbufferLen = 0;
    unsigned int uiPRAMbufferLen = 0;

    /* read codec device identification */
    if (ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x60) != 0x56)
    {
        DPRINTK(0, "init ak7756en error: 0x%x", ak7756en_read(AK7756EN_I2C_SLAVE_ADDR, 0x60));
        return -1;
    }
    /* malloc DSP RAM buffer */
    uiCRAMbufferLen = CEILING_2_POWER(sizeof(ak77dspCRAM), 4);
    uiPRAMbufferLen = CEILING_2_POWER(sizeof(ak77dspPRAM), 4);
    uiBufferLen = uiCRAMbufferLen + uiPRAMbufferLen;
    pu8Ak77dspRAM = (unsigned char*)kmalloc(uiBufferLen, GFP_KERNEL);
    //printk("pu8Ak77dspRAM: 0x%x\n", pu8Ak77dspRAM);
    if (!pu8Ak77dspRAM)
    {
        printk("kmalloc Ak77dspRAM buffer fail!\n");
        return -1;
    }
    memcpy(pu8Ak77dspRAM, ak77dspCRAM, sizeof(ak77dspCRAM));
    pu8PhyAk77dspCRAM = (unsigned char*)virt_to_phys(pu8Ak77dspRAM);
    //printk("pu8PhyAk77dspCRAM: 0x%x\n", pu8PhyAk77dspCRAM);
    memcpy(pu8Ak77dspRAM + uiCRAMbufferLen, ak77dspPRAM, sizeof(ak77dspPRAM));
    pu8PhyAk77dspPRAM = (unsigned char*)virt_to_phys(pu8Ak77dspRAM + uiCRAMbufferLen);
    //printk("pu8PhyAk77dspPRAM: 0x%x\n", pu8PhyAk77dspPRAM);

    /* Control Register Setting */
    //ak7756en_soft_reset();

    /* reboot notifier */
    register_reboot_notifier(&ak7756en_reboot_notifier);

    return 0;
}

static int ak7756en_device_exit( void )
{
    /* HPLOUT is mute */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x0A + AK7756_WRITE_REG_BASEADDR, 0x20);

    /* HPROUT is mute */
    ak7756en_write(AK7756EN_I2C_SLAVE_ADDR, 0x08 + AK7756_WRITE_REG_BASEADDR, 0xE0);

    kfree(pu8Ak77dspRAM);

    return 0;
}


static int __init ak7756en_init(void)
{
    unsigned int ret;

#ifdef CONFIG_HISI_SNAPSHOT_BOOT
    snprintf(s_stAk7756enDevice.devfs_name, sizeof(s_stAk7756enDevice.devfs_name), DEV_NAME);

    s_stAk7756enDevice.minor  = HIMEDIA_DYNAMIC_MINOR;
    s_stAk7756enDevice.fops   = &ak7756en_fops;
    s_stAk7756enDevice.drvops = &stAk7756enDrvOps;
    s_stAk7756enDevice.owner  = THIS_MODULE;

    ret = himedia_register(&s_stAk7756enDevice);
    if (ret)
    {
        DPRINTK(0, "could not register ak7756en device");
        return -1;
    }
#else
    ret = misc_register(&ak7756en_dev);
    if (ret)
    {
        DPRINTK(0, "could not register ak7756en device");
        return -1;
    }
#endif

    i2c_client_init();

    if (ak7756en_device_init() < 0)
    {
#ifdef CONFIG_HISI_SNAPSHOT_BOOT
        himedia_unregister(&s_stAk7756enDevice);
#else
        misc_deregister(&ak7756en_dev);
#endif

        DPRINTK(0, "ak7756en device init fail, deregister it!");

        return -1;
    }

    DPRINTK(1, "ak7756en driver init successful!");

    printk("load ak7756en.ko for Hi3516A ok!\n");

    return ret;
}

static void __exit ak7756en_exit(void)
{
    i2c_client_exit();

    ak7756en_device_exit();

    unregister_reboot_notifier(&ak7756en_reboot_notifier);

#ifdef CONFIG_HISI_SNAPSHOT_BOOT
    himedia_unregister(&s_stAk7756enDevice);
#else
    misc_deregister(&ak7756en_dev);
#endif

    DPRINTK(1, "deregister ak7756en");

    printk("rmmod ak7756en.ko for Hi3516A ok!\n");
}

module_init(ak7756en_init);
module_exit(ak7756en_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon");

