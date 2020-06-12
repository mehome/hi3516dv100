Nand_product is provided to translate the origin image to burner(flash burn device) image, 
the same format as the data stored in nand flash. More information about the format
difference between the origin data and burner data, please refer to the datasheet Nand Flash
Data Storage Structure capther. The origin image include uboot_xx.bin/uImage_xx/rootfs_xx.yaffs2. 

Usage:
./nand_product
Usage: ./nand_ecc_test inputfile outputfile pagetype ecctype oobsize yaffs randomizer pagenum save_pin:
For example:
./nand_product in_2k4b.yaffs out_2k4b.yaffs 0 0 64 1 0 64 0
Page type Page size:
Input file:
Output file:
Pagetype:
0        2KB
1        4KB
2        8KB
3        16KB
ECC type ECC size:
0        4bit/512B
2        24bit/1K
3        40bit/1K
4        64bit/1K
Chip OOB size:
yaffs2 image format:
0        NO
1        YES
Randomizer:
0        randomizer_disabled
1        randomizer_enabled
Pages_per_block:
64       64pages/block
128      128pages/block
256      256pages/block
512      512pages/block
Save Pin Mode:
0        disable
1        enable

Notice:
1 When the nand pagesize less than 8K, the Randomizer select 0, others select 1;
2 When make the uboot image, the Save Pin Mode select 1, others select 0;
