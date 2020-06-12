cmd_net/unix/unix.o := arm-hisiv300-linux-ld -EL    -r -o net/unix/unix.o net/unix/af_unix.o net/unix/garbage.o net/unix/sysctl_net_unix.o 
