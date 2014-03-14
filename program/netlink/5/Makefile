obj-m := nl_kern.o
KERN :=/lib/modules/`uname -r`/build
PWD :=$(shell pwd)
default:
	$(MAKE) -C $(KERN) M=$(PWD) modules

clean:
	rm -f *.o *.ko *.mod.c

