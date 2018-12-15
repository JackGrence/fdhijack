CROSS_COMPILE =
CC = $(CROSS_COMPILE)gcc

LINUX_DEBUG = false

KDIR := $(KERNELROOT)
KOUT := $(KERNELOUT)
PWD := $(shell pwd)

export CC

obj-m := fdhj.o
MODULE = fdhj.ko

CFLAGS_fdhj.o += -I$(PWD)/../../inc
export CFLAGS_fdhj.o

default:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	rm -rf *.ko *.o *.mod.* *.symvers *.c~ .mod* .fdhj* .test* .tmp* modules.order
cleantmp:
	rm -rf *.o *.mod.* *.symvers *.c~ .mod* .fdhj* .test* .tmp* modules.order

