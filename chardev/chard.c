#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

static dev_t first;

static int __init ccd_init(void)
{
printk(KERN_INFO "Char Device Driver registered");
if (alloc_chrdev_region(&first, 0, 3, "char_dd") < 0)
{
return -1;
}
printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));
return 0;
}

static void __exit ccd_exit(void)
{
unregister_chrdev_region(first, 3);
printk(KERN_INFO "Char Device Driver unregistered");
}

module_init(ccd_init);
module_exit(ccd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nishant Kumar<nishantdawn01@gmail.com>");
MODULE_DESCRIPTION("First Character Driver Example");
