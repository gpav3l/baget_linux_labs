#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#include <linux/platform_device.h>

#include "mychar_desc.h"
#include "mychar_dev.h"

srisa_pdrv_t* my_dev;

// Some infos
MODULE_DESCRIPTION("SRISA Platform driver example");
MODULE_AUTHOR("Student <studnet@mirea.ru>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:srisa-pdrv");


static int pdrv_probe(struct platform_device *pdev);
static int pdrv_remove(struct platform_device *pdev);


/**
 * Lst of compatible devices
*/
static const struct of_device_id pdrv_of_match[] = {
        { .compatible = "srisa,platform-device", },
        { },
};
MODULE_DEVICE_TABLE(of, pdrv_of_match);


/**
 * Structure declared handlers for Kernel commands
 *   
*/
static struct platform_driver srisa_platform_driver = {
        .probe  = pdrv_probe,
        .remove = pdrv_remove,
        .driver = {
                .name           = DRIVER_NAME,
                .owner          = THIS_MODULE,
                .of_match_table = pdrv_of_match,
        },
};


/**
 * Call when module is loaded
*/
static int pdrv_probe(struct platform_device *pdev)
{
    int rc = 0; 
    struct device *dev = &pdev->dev;
    my_dev = NULL;
    
    printk("%s: %s\n", DRIVER_NAME, __func__);
    //dev_info(dev, "%pOF\n", dev_of_node(dev));
    
    // Make pointer to currrent device
    my_dev = (srisa_pdrv_t *) kmalloc(sizeof(srisa_pdrv_t), GFP_KERNEL);
	if (!my_dev) {
		dev_err(dev, "Cound not allocate srisa-pdrv device\n");
		return -ENOMEM;
	}
	dev_set_drvdata(dev, my_dev);
    
    // init character class device
    if(srisa_pdrv_chinit(pdev) != 0) {
       rc = -EIO;
       goto error1;
    }
    
    return 0;
    
error1:
	kfree(my_dev);
	dev_set_drvdata(dev, NULL);
	return rc;
}


/**
 * Call when module is unload
*/
static int pdrv_remove(struct platform_device *pdev)
{    
    srisa_pdrv_chdeinit(pdev);
    
    printk("%s: %s\n", DRIVER_NAME, __func__);   
    return 0;
}


/**
 * Register module
 * 
 */
static int __init srisa_pdrv_init(void)
{
    printk("%s: %s\n", DRIVER_NAME, __func__);
    return platform_driver_register(&srisa_platform_driver);
}
module_init(srisa_pdrv_init);


/**
 * Deinitialization
 */
static void __exit srisa_pdrv_exit(void)
{
    printk("%s: %s\n", DRIVER_NAME, __func__);
	platform_driver_unregister(&srisa_platform_driver);
}
module_exit(srisa_pdrv_exit);

