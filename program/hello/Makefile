ifneq ($(KERNELRELEASE),)
	obj-m :=hello.o
    hello-objs :=hello.o
else
	PWD := $(shell pwd)
KDIR :=/usr/src/linux-headers-3.5.0-40-generic
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf .*.cmd  *.o  *.mod.c  *.ko  .tmp_versions
endif

