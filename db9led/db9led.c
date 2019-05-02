#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <asm/uaccess.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

#include <linux/serial_reg.h>
#define SERIAL_PORT_BASE 0x3F8
u8 data;

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;

static char c = '0';

static int my_open(struct inode *i, struct file *f)
{
	return 0;
}
static int my_close(struct inode *i, struct file *f)
{
	return 0;
}



static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	

if (*off == 0)
	{


		if (raw_copy_to_user(buf, &c, 1))
		{
			return -EFAULT;
		}
		*off += 1;
		return 1;
	}
	else

		return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{


		if(*buf == '1')
		outb(data | UART_LCR_SBC, SERIAL_PORT_BASE + UART_LCR);  // LED High
		if(*buf == '0')
		outb(data & (~UART_LCR_SBC), SERIAL_PORT_BASE + UART_LCR); // LED LOW

	if (raw_copy_from_user(&c, buf + len - 1, 1))
	{
		return -EFAULT;
	}
	return len;
}

static struct file_operations driver_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write
};

static int __init fcd_init(void)
{
	int ret;
	struct device *dev_ret;
	data = inb(SERIAL_PORT_BASE + UART_LCR);
	/* Pulling the Tx line LOW */	
        outb(data & (~UART_LCR_SBC), SERIAL_PORT_BASE + UART_LCR);

	

	if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "serial_led_driver")) < 0)
	{
		return ret;
	}

	cdev_init(&c_dev, &driver_fops);

	if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0)
	{
		unregister_chrdev_region(dev, MINOR_CNT);
		return ret;
	}
	
	if (IS_ERR(cl = class_create(THIS_MODULE, "char_serial_led")))
	{
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(cl);
	}
	if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "serial_led%d", FIRST_MINOR)))
	{
		class_destroy(cl);
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(dev_ret);
	}

	return 0;
}

static void __exit fcd_exit(void)
{
	outb(data & (~UART_LCR_SBC), SERIAL_PORT_BASE + UART_LCR); // LED LOW
	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
}

module_init(fcd_init);
module_exit(fcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nishant Kumar <Nishantdawn01@gmail.com>");
MODULE_DESCRIPTION("Serial Port Led Driver");
