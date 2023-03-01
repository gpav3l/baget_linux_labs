obj-m := spi_temp.o

KERNEL_SRC=/home/student/baget/support/linux-sources-4.15

SRC := $(shell pwd)

BRD_USER := netuser
BRD_IP := 192.168.100.200
BRD_DIR := /home/netuser

all:
	rm -f *.ko
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC)/

install: all
	scp ./spi_temp.ko $(BRD_USER)@$(BRD_IP):$(BRD_DIR)
	
clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c
	rm -f Module.markers Module.symvers modules.order .cache.mk
	rm -rf .tmp_versions Modules.symvers
