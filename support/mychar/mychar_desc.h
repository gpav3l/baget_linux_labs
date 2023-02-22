#ifndef _MYCHAR_DESC_H_
#define _MYCHAR_DESC_H_

#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/kfifo.h>
#include <stdbool.h>

#define DRIVER_NAME "srisa_pdrv"
#define DRIVER_VERS "0.1"

typedef struct {
    struct cdev cdev;
    bool cdev_is_open;
    int major;
    int minor;
    struct class *cls;
    struct device *ch_dev;
} srisa_pdrv_t;

extern srisa_pdrv_t* my_dev;

#endif
