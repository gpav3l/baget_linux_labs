#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/errno.h>
#include <linux/gpio.h>

#define DRIVER_NAME "dummy_driver"
#define GPIO_GRN_LED 464

struct gpio_desc *yellow;

/**
 * GPIO initialization
 *
 * @return 0 if success, negative value in other case
*/
int myled_init(int gpio_id)
{
  //Checking the GPIO is valid or not
  if(gpio_is_valid(gpio_id) == false)
  {
    printk("%s: GPIO %d is not valid\n", DRIVER_NAME, gpio_id);

    return -1;
  }

  //Requesting the GPIO
  if(gpio_request(gpio_id, "GRN_LED") < 0)
  {
    printk("%s: GPIO %d request\n", DRIVER_NAME, gpio_id);

    return -1;
  }

  //configure the GPIO as input
  gpio_direction_output(gpio_id, GPIOD_OUT_HIGH);
  return 0;
}


/**
 * Probe function, called when found device compatible with this driver
 *
 * @param pdev is pointer of device-tree nodes of compatible devices
 *
 * @return 0 if success, negative value in other case
*/
static int gpio_init_probe(struct platform_device *pdev)
{
  int i = 0;
  int dt_init = 0;  // Flag of success initialization from device-tree
  int def_init = -1; // Flag of sucess initialzation from define

  printk("%s: %s\n", DRIVER_NAME, __func__);

  def_init = myled_init(GPIO_GRN_LED);

  /* "yellowled" label is matching the device tree declaration. OUT_LOW is the value at init */
  yellow = devm_gpiod_get(&pdev->dev, "yellowled", GPIOD_OUT_LOW);

  if(IS_ERR(yellow)) {
    printk("%s: get gpio error with code %d\n", DRIVER_NAME, IS_ERR(yellow));
    dt_init = -ENODEV;
  }

  if((dt_init != 0) && (def_init != 0)) {
    printk("%s: no any gpio\n", DRIVER_NAME);
    return -1;
  }

  /* blink of the led */
  while (i < 10)
  {
    ssleep(1);
    if(dt_init == 0)  gpiod_set_value(yellow, 1);
    if(def_init == 0) gpio_set_value(GPIO_GRN_LED, 0);

    ssleep(1);
    if(dt_init == 0) gpiod_set_value(yellow, 0);
    if(def_init == 0) gpio_set_value(GPIO_GRN_LED, 1);

    i++;
  }

  return(0);
}


/**
 * Driver deinitialization, called by rmmod
 *
 * @return 0 if success, negative value in other case
*/
static int gpio_exit_remove(struct platform_device *pdev)
{
  printk("%s: %s\n", DRIVER_NAME, __func__);

  gpio_free(GPIO_GRN_LED);

  return(0);
}


/** this structure does the matching with the device tree
* if it does not match the compatible field of DT, nothing happens
*/
static struct of_device_id dummy_match[] = {
    {.compatible = "gpio,dummy"},
    {/* end node */}
};


/**
 *
*/
static struct platform_driver dummy_driver = {
    .probe = gpio_init_probe,
    .remove = gpio_exit_remove,
    .driver = {
        .name = DRIVER_NAME,
                .owner = THIS_MODULE,
                .of_match_table = dummy_match,
    }
};

module_platform_driver(dummy_driver);

MODULE_AUTHOR("Gorbokoneko Pavel <gorbokonenko@mirea.ru>");
MODULE_DESCRIPTION("Gpio example");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:dummy_driver");
