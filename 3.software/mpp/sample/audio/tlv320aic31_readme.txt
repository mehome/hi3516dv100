1. Update the file: mpp/ko/pinmux_hi3516a.sh,
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

2. update the file: mpp/ko/sysctl_hi3516a.sh£¬
   It need to use the external audio codec, please modify the script as below. 
	# msic config
	#himm 0x201200E0 0xd				# internal codec-AIO MCLK out, CODEC AIO TX MCLK 
	himm 0x201200E0 0xe				# external codec: AIC31/AK7756EN AIO MCLK out, CODEC AIO TX MCLK 

3. update the file: mpp\ko\load3516a£¬
   It need to insmod tlv_320aic31's driver. 
	insmod extdrv/tlv_320aic31.ko

4. modify the makefile parameter: mpp/sample/Makefile.param£¬from ACODEC_TYPE to  ACODEC_TYPE_TLV320AIC31. 
   It means use the external codec tlv_320aic31 sample code.
	################ select audio codec type for your sample ################
	ACODEC_TYPE ?= ACODEC_TYPE_INNER
	#external acodec
	#ACODEC_TYPE ?= ACODEC_TYPE_AK7756
	#ACODEC_TYPE ?= ACODEC_TYPE_TLV320AIC31

5. Rebuild the sample and get the sample_audio.
