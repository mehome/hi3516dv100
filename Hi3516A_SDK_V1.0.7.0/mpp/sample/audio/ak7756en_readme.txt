1. Update the Kernel file: osdrv/opensource/kernel/linux-3.4.y/drivers/hidmac/hi_dmac.c,
   Since AK7756 only support I2C2 interface, it need to modify the code in struct g_peripheral[DMAC_MAX_PERIPHERALS] as below. 
	/*periphal 2: I2C2 RX*/
          { 2, 0x20250010, 0x99000000, 0xd004, 0},        /*  8bit width */
 
          /*periphal 3: I2C2 TX*/
          { 3, 0x20250010, 0x96000000, 0xc8c0, 0},        /*  8bit width */

2. Update the file: mpp/ko/pinmux_hi3516a.sh,
   It need to use I2S2 interface, so open the pinmux setting as below. 
	i2s_pin_mux()
	{
		#himm 0x200f0088 0x2;	# i2s0_bclk_rx
		#himm 0x200f008c 0x2;	# i2s0_ws_rx
		#himm 0x200f0090 0x2;	# i2s0_mclk
		#himm 0x200f0094 0x2;	# i2s0_bclk_tx
		#himm 0x200f0098 0x2;	# i2s0_ws_tx
		#himm 0x200f009c 0x2;	# i2s0_sd_rx
		#himm 0x200f00a0 0x2;	# i2s0_sd_tx

		#himm 0x200f00b0 0x2;	# i2s1_mclk
		#himm 0x200f00b4 0x2;	# i2s1_bclk_tx
		#himm 0x200f00b8 0x2;	# i2s1_ws_tx
		#himm 0x200f00bc 0x2;	# i2s1_sd_tx
		#himm 0x200f00c0 0x2;	# i2s1_bclk_rx
		#himm 0x200f00c4 0x2;	# i2s1_ws_rx
		#himm 0x200f00c8 0x2;	# i2s1_sd_rx

		himm 0x200f01ac 0x2;	# i2s2_mclk
		himm 0x200f01b0 0x2;	# i2s2_bclk_tx
		himm 0x200f01b4 0x2;	# i2s2_ws_tx
		himm 0x200f01b8 0x2;	# i2s2_sd_tx
		himm 0x200f01bc 0x2;	# i2s2_bclk_rx
		himm 0x200f01c0 0x2;	# i2s2_ws_rx
		himm 0x200f01c4 0x2;	# i2s2_sd_rx
	}

	i2c_pin_mux;
	vicap_pin_mux;
	i2s_pin_mux;

3. update the file: mpp/ko/sysctl_hi3516a.sh£¬
    It need to use the external audio codec, please modify the script as below. 
	# msic config
	#himm 0x201200E0 0xd				# internal codec-AIO MCLK out, CODEC AIO TX MCLK 
	himm 0x201200E0 0xe				# external codec: AIC31/AK7756EN AIO MCLK out, CODEC AIO TX MCLK 

4. update the file: mpp/ko/load3516a£¬
   It need to insmod AK7756's driver. 
	insmod extdrv/ak7756.ko

5. modify the makefile parameter: mpp/sample/Makefile.param£¬from ACODEC_TYPE to  ACODEC_TYPE_AK7756. 
   It means use the external codec AK7756 sample code.
	################ select audio codec type for your sample ################
	ACODEC_TYPE ?= ACODEC_TYPE_INNER
	#external acodec
	#ACODEC_TYPE ?= ACODEC_TYPE_AK7756
	#ACODEC_TYPE ?= ACODEC_TYPE_TLV320AIC31

6. Rebuild the sample and get the sample_audio.

Notes: 1. AK7756 ONLY support 8K16bit.
       2. AK7756 ONLY support MONO sound.
       3. AK7756 ONLY support I2S_MASTER for now.
       4. AI and AO must share clk.  (AI u32ClkSel must be set to 1)
