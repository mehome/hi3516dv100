cmd_drivers/scsi/built-in.o :=  arm-hisiv300-linux-ld -EL    -r -o drivers/scsi/built-in.o drivers/scsi/scsi_mod.o drivers/scsi/scsi_transport_fc.o drivers/scsi/arm/built-in.o drivers/scsi/sd_mod.o 
