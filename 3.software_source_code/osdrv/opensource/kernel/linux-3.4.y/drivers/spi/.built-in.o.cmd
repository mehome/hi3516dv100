cmd_drivers/spi/built-in.o :=  arm-hisiv300-linux-ld -EL    -r -o drivers/spi/built-in.o drivers/spi/spi.o drivers/spi/spidev.o drivers/spi/hi_spidev_info.o drivers/spi/hi_spi.o 
