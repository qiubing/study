obj-m := netlink_exam_kern.o
KERN :=/lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERN) M=$(PWD) modules

clean:
	rm -f *.o *.ko *.mod.c
