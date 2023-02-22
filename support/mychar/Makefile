obj-m := chardev.o

chardev-y := mychar_init.o mychar_dev.o 

KERNEL_SRC=/home/student/baget/support/linux-sources-4.15

SRC := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC)/

clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c
	rm -f Module.markers Module.symvers modules.order
	rm -rf .tmp_versions Modules.symvers
