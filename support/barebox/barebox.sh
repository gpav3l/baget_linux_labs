#!/bin/sh

bootargs="console=ttyS0,115200 root=/dev/mmcblk0p1 rw rootwait"

DTB=k5500vk018_rbm.dtb


## Dump board info
srisa_set_cpu_freq -n -o /ovl

#bootm -v -o $DTB -l /ovl vmlinux-el
bootm -v -o $DTB -l /ovl vmlinux-gb11c3c88c97e
