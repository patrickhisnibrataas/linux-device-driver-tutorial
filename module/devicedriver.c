#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/kern_levels.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <stdbool.h>

/*** Function prototypes ***/
static int parameter_value_with_callback_set(const char *val, const struct kernel_param *kp);
static bool allocate_major_number(void);
static void deallocate_major_number(void);
static bool create_character_device(void);

/*** Variables ***/
static int parameter_value = 0;
static int parameter_value_with_callback = 0;
const struct kernel_param_ops parameter_value_with_callback_ops = {
    .set = &parameter_value_with_callback_set,
    .get = &param_get_int,
};
static dev_t dev = 0;
static struct class *devicedriver_class;
static struct cdev devicedriver_cdev;
static struct file_operations fops =
{
    .owner          = THIS_MODULE
};

/*** Parameters ***/
module_param(parameter_value, int, S_IRUGO|S_IWUSR);
module_param_cb(parameter_value_with_callback, &parameter_value_with_callback_ops, &parameter_value_with_callback, S_IRUGO|S_IWUSR);

/*** Functions ***/
static int __init devicedriver_init(void) {
    if (!allocate_major_number()) {
        return -1;
    }

    if (!create_character_device()) {
        deallocate_major_number();
        return -2;
    }

    printk(KERN_INFO "Module loaded sucessfully\n");
    
    return 0;
}

static void __exit devicedriver_exit(void) {
    device_destroy(devicedriver_class, dev);
    class_destroy(devicedriver_class);
    cdev_del(&devicedriver_cdev);
    deallocate_major_number();
    printk(KERN_INFO "Module removed\n");
}

static int parameter_value_with_callback_set(const char *val, const struct kernel_param *kp) {
    int res = param_set_int(val, kp);
    if (res) {
        printk(KERN_INFO "Unable to set parameter_value_with_callback\n");
        return -1;
    }

    printk(KERN_INFO "parameter_value_with_callback value changed to %d\n", parameter_value_with_callback);
    return 0;
}

static bool allocate_major_number(void) {
    int ret = alloc_chrdev_region(&dev, 0, 1, "devicedriver");
    if (ret < 0) {
        printk(KERN_INFO "Was not able to allocate major number for 'devicedriver' device\n");
        return false;
    }

    printk(KERN_INFO "Major = %d Minor = %d \n", MAJOR(dev), MINOR(dev));

    return true;
}

static void deallocate_major_number(void) {
    unregister_chrdev_region(dev, 1);
}

static bool create_character_device(void) {
    cdev_init(&devicedriver_cdev, &fops);

    if ((cdev_add(&devicedriver_cdev, dev, 1)) < 0) {
        printk(KERN_INFO "Cannot add the character device to the system\n");
        return false;
    }

    if ((devicedriver_class = class_create(THIS_MODULE, "devicedriver")) == NULL) {
        printk(KERN_INFO "Can not create the struct class for device\n");
        return false;
    }

    if ((device_create(devicedriver_class, NULL, dev, NULL, "devicedriver")) == NULL) {
        printk(KERN_INFO "Cannot create the Device\n");
        class_destroy(devicedriver_class);
        return false;
    }

    return true;
}

/*** Module ***/
module_init(devicedriver_init);
module_exit(devicedriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Hisni Brataas <patrick@brataas.io>");
MODULE_DESCRIPTION("A device driver where features are added step by step");
MODULE_VERSION("1.0.0");

MODULE_PARM_DESC(parameter_value, "A module parameter");
MODULE_PARM_DESC(parameter_value_with_callback, "A module parameter with callback function");
