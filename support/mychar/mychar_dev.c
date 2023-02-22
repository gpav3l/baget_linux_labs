#include <uapi/asm-generic/errno-base.h>
#include <linux/kfifo.h>

#include "mychar_dev.h"
#include "mychar_desc.h"

#define FIFO_SIZE 256

static struct kfifo data_fifo;

/**
 *  Descibe which function call, when recive SCI command
 */
static struct file_operations srisa_pdrv_fops = {
    .owner          = THIS_MODULE,
    .open           = srisa_pdrv_open,
    .read           = srisa_pdrv_read,
    .write          = srisa_pdrv_write,
    .fasync         = srisa_pdrv_fasync,
    .release        = srisa_pdrv_release,
    .unlocked_ioctl = srisa_pdrv_ioctl, 
};


/**
 * @brief Init character driver
 * 
 */
int srisa_pdrv_chinit(struct platform_device *pdev)
{
    int ret;

    my_dev->minor = 0;
    my_dev->cdev_is_open = false;
    
    // register new device
    my_dev->major = register_chrdev(0, DRIVER_NAME, &srisa_pdrv_fops);
    if (my_dev->major < 0) {
        dev_err(&pdev->dev, "registering char device failed\n");
        return my_dev->major;
    }
    
    // create character class devcie
    my_dev->cls = class_create(THIS_MODULE, DRIVER_NAME);
    if (IS_ERR(my_dev->cls)) {
        dev_err(&pdev->dev, "creating class failed\n");
        return PTR_ERR(my_dev->cls);
    }

    // creation node in /dev/ folder
    my_dev->ch_dev = device_create(my_dev->cls, NULL, MKDEV(my_dev->major, my_dev->minor), NULL, DRIVER_NAME);
    if (IS_ERR(my_dev->ch_dev)) {
        class_destroy(my_dev->cls);
        dev_err(&pdev->dev, "creating device failed\n");
        return -1;
    }
    
    
    ret = kfifo_alloc(&data_fifo, FIFO_SIZE, GFP_KERNEL);
    if (ret) {
        printk(KERN_ERR "error kfifo_alloc\n");
        return ret;
    }

    return 0;
}


/**
 * @brief Deinit character driver
 * 
 */
void srisa_pdrv_chdeinit(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;
	my_dev = dev_get_drvdata(dev);
    
    kfifo_free(&data_fifo);

    device_destroy(my_dev->cls, MKDEV(my_dev->major, my_dev->minor));
    class_destroy(my_dev->cls);
    unregister_chrdev(my_dev->major, DRIVER_NAME);
}


/**
 * @brief Open file handler
 * 
 * @param inode 
 * @param file 
 * @return int 
 */
int srisa_pdrv_open(struct inode *inode, struct file *file)
{
    printk("%s: %s\n", DRIVER_NAME, __func__);

    if(my_dev->cdev_is_open)
        return -EBUSY;

    my_dev->cdev_is_open = true;

    return 0;
}


/**
 * @brief Release file handler
 * 
 * @param inode 
 * @param file 
 * @return int 
 */
int srisa_pdrv_release(struct inode *inode, struct file *file)
{
    my_dev->cdev_is_open = false;
    printk("%s: %s\n", DRIVER_NAME, __func__);
    return 0;
}


/**
 * @brief Read file handler
 * 
 * @param filp 
 * @param buffer
 * @param length
 * @param offset
 * @return ssize_t 
 */
ssize_t srisa_pdrv_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    char *kbuf = kmalloc(length, GFP_KERNEL); // Request memory region to internal buffer
	int i = 0;
    int rc = length;

    // Fill buffer with ASCII characters from 0x41 to 0x5A
    for(i=0; i<length; i++) {
        kbuf[i] = i%26 + 0x41;
    }
    
    // Try send data to user space
    if(copy_to_user(buffer, kbuf, length)) {
        rc = -EFAULT;
        printk("%s: %s: Failed send data to user space\n", DRIVER_NAME, __func__);
    } else {
        printk("%s: %s: Send %ld bytes\n", DRIVER_NAME, __func__, length);
    }
    
    kfree(kbuf); // Make free memory region, in other case memory leaks!
	return rc;
}


/**
 * @brief Write file handler, 
 * 
 * @param filp 
 * @param buffer
 * @param length 
 * @param offset
 * @return ssize_t 
 */
ssize_t srisa_pdrv_write(struct file *filp, const char *buffer, size_t length, loff_t *offset)
{
    char *kbuf = kmalloc(length, GFP_KERNEL); // Request memory region to internal buffer
    int rc = length;

    // Try get data from user space
    if(copy_from_user(kbuf, buffer, length)) {
        rc = -EFAULT;
        printk("%s: %s: Failed get data from user space\n", DRIVER_NAME, __func__);
    } else {
        printk("%s: %s: Get %ld bytes\n", DRIVER_NAME, __func__, length);
    }
    
    kfree(kbuf); // Make free memory region, in other case memory leaks!
	return rc;
}


/**
 * @brief FASYNC handler
 * 
 * @param fd 
 * @param filp 
 * @param on 
 * @return int 
 */
int srisa_pdrv_fasync(int fd, struct file *filp, int on)
{
    struct fasync_struct *irq_async;
    printk("%s: %s\n", DRIVER_NAME, __func__);
    return fasync_helper(fd, filp, on, &irq_async);
}


/**
 * @brief IO control handler
 * 
 * @param file 
 * @param ioct_num 
 * @param ioct_param 
 * @return long 
 */
long srisa_pdrv_ioctl(struct file *file, unsigned int ioct_num, unsigned long ioct_param)
{
    printk("%s: %s\n", DRIVER_NAME, __func__);
    return 0;
}
