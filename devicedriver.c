#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kern_levels.h>
#include <linux/module.h>

/*** Functions ***/
static int __init devicedriver_init(void) {
    printk(KERN_INFO "Module loaded sucessfully\n");

    return 0;
}

static void __exit devicedriver_exit(void) {
    printk(KERN_INFO "Module removed\n");
}

/*** Module ***/
module_init(devicedriver_init);
module_exit(devicedriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Hisni Brataas <patrick@brataas.io>");
MODULE_DESCRIPTION("A device driver where features are added step by step");
MODULE_VERSION("1.0.0");
