#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>

#define DRIVER_NAME "als-spi-driver"

static struct spi_device *als_spi_device;

//Register information about your slave device
struct spi_board_info als_spi_device_info =
{
  .modalias     = DRIVER_NAME,
  .max_speed_hz = 4000000,       // speed your device (slave) can handle
  .bus_num      = 1,             // SPI bus 1
  .chip_select  = 0,             // Use Chip select 0
  .mode         = SPI_MODE_3     // SPI mode 3
};


/**
 * Read data from
 *
 * @param data for send thru SPI
 *
 * @return light level
*/
uint16_t als_spi_read(void)
{
  int     ret = -1;
  uint16_t rx  = 0x00;
  uint16_t tx = 0x00;
  printk("%s: %s\n", DRIVER_NAME, __func__);
  if(als_spi_device)
  {
    struct spi_transfer  tr =
    {
      .tx_buf  = &tx,
      .rx_buf = &rx,
      .len    = 2,
    };
    ret = spi_sync_transfer(als_spi_device, &tr, 1);
  }

  //Only 12 bit is meaning
  return (rx >> 4);
}


/**
 * Driver initialization (call when modprobe or insmod call)
*/
static int __init als_spi_init(void)
{
  int     ret;
  struct  spi_master *master;

  master = spi_busnum_to_master(als_spi_device_info.bus_num);
  if( master == NULL )
  {
    printk("%s: spi%d not found \n", DRIVER_NAME, als_spi_device_info.bus_num);
    return -ENODEV;
  }

  // create a new slave device, given the master and device info
  als_spi_device = spi_new_device( master, &als_spi_device_info );
  if(als_spi_device == NULL)
  {
    printk("%s: can't create slave device\n", DRIVER_NAME);
    return -ENODEV;
  }

  // 16-bits in a word
  als_spi_device->bits_per_word = 8;
  // setup the SPI slave device
  ret = spi_setup(als_spi_device);
  if( ret )
  {
    printk("%s: failed to setup slave device\n", DRIVER_NAME);
    spi_unregister_device(als_spi_device);
    return -ENODEV;
  }

  printk("%s: registered \n", DRIVER_NAME);

  for(ret = 0; ret < 10; ret++) {
    printk("%s: light level %d \n", DRIVER_NAME, als_spi_read());
  }
  return 0;
}


/**
 * Driver deinitialization (call when rmmod call)
*/
static void __exit als_spi_exit(void)
{
  if(als_spi_device)
  {
    spi_unregister_device(als_spi_device);    // Unregister the SPI slave
    printk("%s: unregistered \n", DRIVER_NAME);
  }
}

module_init(als_spi_init);
module_exit(als_spi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gorbokoneko Pavel <gorbokonenko@mirea.ru>");
MODULE_DESCRIPTION("A simple device driver for PmodALS module");
MODULE_VERSION("0.1");
