obj-m := netlink_k.o
KERN :=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
default:
	$(MAKE) -C $(KERN) M=$(PWD) modules

clean:
	rm -f *.o *.ko *.mod.c

