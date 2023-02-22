#ifndef _MYCHAR_DEV_
#define _MYCHAR_DEV_

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/types.h>
#include <linux/platform_device.h>

int srisa_pdrv_chinit(struct platform_device *pdev);
void srisa_pdrv_chdeinit(struct platform_device *pdev);

int srisa_pdrv_open(struct inode *inode, struct file *file);
int srisa_pdrv_release(struct inode *inode, struct file *file);
ssize_t srisa_pdrv_read(struct file *filp, char *buffer, size_t length, loff_t *offset);
ssize_t srisa_pdrv_write(struct file *filp, const char *buffer, size_t length, loff_t *offset);
int srisa_pdrv_fasync(int fd, struct file *filp, int on);
long srisa_pdrv_ioctl(struct file *file, unsigned int ioct_num, unsigned long ioct_param);


#endif
