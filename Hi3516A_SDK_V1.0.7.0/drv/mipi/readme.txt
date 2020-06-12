combo_dev_attr_t for mipi combo configuration, must be configured according to sensor data sheet.

input_mode: MIPI/LVDS/SUBLVDS/HISPI/DC
mipi_dev_attr_t: should be configured in MIPI input mode
lvds_dev_attr_t: should be configured in LVDS/SUB_LVDS/HISPI input mode

mipi_dev_attr_t:
    raw_data_type: 10/12/14 bit data type
    lane_id: -1 means disable, should be configured according to sensor data lane


lvds_dev_attr_t:
    img_size: oringnal sensor input image size
    wdr_mode: none/2f
    sync_mode: sol/sav
    raw_data_type: 8/10/12/14 bit data type
    data_endian: little/big
    sync_code_endian: little/big
    lane_id: -1 means disable, should be configured according to sensor data lane
    sync_code: each lane and each vc may have diffent sync_code, each sync code has 4 params:
                  sync_mode is SYNC_MODE_SOL: SOL, EOL, SOF, EOF
                  sync_mode is SYNC_MODE_SAV: valid sav, valid eav, invalid sav, invalid eav


-----------------------------------------------------------------------------------
example:

1. mn34220 12bit sensor wdr output:
combo_dev_attr_t SUBLVDS_4lane_SENSOR_MN34220_12BIT_1080_2WDR1_ATTR =
{
    /* input mode */
    .input_mode = INPUT_MODE_SUBLVDS,

    {
        .lvds_attr = {
            .img_size = {SENSOR_WIDTH, SENSOR_HEIGHT},
            HI_WDR_MODE_2F,            
            LVDS_SYNC_MODE_SOL,
            RAW_DATA_12BIT,                     
            LVDS_ENDIAN_BIG,
            LVDS_ENDIAN_BIG, 
            .lane_id = {0, 2, -1, -1, 1, 3, -1, -1},
            .sync_code =  {
                {{0x002, 0x003, 0x000, 0x001}, //PHY0_lane0
                    {0x202, 0x203, 0x200, 0x201},
                    {0x102, 0x103, 0x100, 0x101},
                    {0x302, 0x303, 0x300, 0x301}},

                {{0x006, 0x007, 0x004, 0x005}, //PHY0_lane1
                    {0x206, 0x207, 0x204, 0x205},
                    {0x106, 0x107, 0x104, 0x105},
                    {0x306, 0x307, 0x304, 0x305}},

                {{0x00a, 0x00b, 0x008, 0x009}, //PHY0_lane2
                    {0x20a, 0x20b, 0x208, 0x209},
                    {0x10a, 0x10b, 0x108, 0x109},
                    {0x30a, 0x30b, 0x308, 0x309}},

                {{0x00a, 0x00b, 0x008, 0x009}, //PHY0_lane3 
                    {0x20a, 0x20b, 0x208, 0x209},
                    {0x10a, 0x10b, 0x108, 0x109},
                    {0x30a, 0x30b, 0x308, 0x309}},

                {{0x012, 0x013, 0x010, 0x011},//PHY1_lane0
                    {0x212, 0x213, 0x210, 0x211},
                    {0x112, 0x113, 0x110, 0x111},
                    {0x312, 0x313, 0x310, 0x311}},

                {{0x016, 0x017, 0x014, 0x015}, //PHY1_lane1
                    {0x216, 0x217, 0x214, 0x215},
                    {0x116, 0x117, 0x114, 0x115},
                    {0x316, 0x317, 0x314, 0x315}},

                {{0x01a, 0x01b, 0x018, 0x019}, //PHY1_lane2
                    {0x21a, 0x21b, 0x218, 0x219},
                    {0x11a, 0x11b, 0x118, 0x119},
                    {0x31a, 0x31b, 0x318, 0x319}},

                {{0x01a, 0x01b, 0x018, 0x019}, //PHY1_lane3
                    {0x21a, 0x21b, 0x218, 0x219},
                    {0x11a, 0x11b, 0x118, 0x119},
                    {0x31a, 0x31b, 0x318, 0x319}}
            } 
        }
    }
};

2. imx185 mipi input mode:
combo_dev_attr_t MIPI_4lane_SENSOR_IMX185_12BIT_ATTR = 
{
    .input_mode = INPUT_MODE_MIPI,  
    {
        .mipi_attr =    
        {
            RAW_DATA_12BIT,
            {0, 1, 2, 3, -1, -1, -1, -1}
        }
    }
};

