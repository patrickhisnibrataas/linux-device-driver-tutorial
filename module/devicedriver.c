#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kern_levels.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

/*** Function prototypes ***/
static int parameter_value_with_callback_set(const char *val, const struct kernel_param *kp);

/*** Variables ***/
static int parameter_value = 0;
static int parameter_value_with_callback = 0;
const struct kernel_param_ops parameter_value_with_callback_ops = {
    .set = &parameter_value_with_callback_set,
    .get = &param_get_int,
};

/*** Parameters ***/
module_param(parameter_value, int, S_IRUGO|S_IWUSR);
module_param_cb(parameter_value_with_callback, &parameter_value_with_callback_ops, &parameter_value_with_callback, S_IRUGO|S_IWUSR);

/*** Functions ***/
static int __init devicedriver_init(void) {
    printk(KERN_INFO "Module loaded sucessfully\n");

    return 0;
}

static void __exit devicedriver_exit(void) {
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

/*** Module ***/
module_init(devicedriver_init);
module_exit(devicedriver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Hisni Brataas <patrick@brataas.io>");
MODULE_DESCRIPTION("A device driver where features are added step by step");
MODULE_VERSION("1.0.0");

MODULE_PARM_DESC(parameter_value, "A module parameter");
MODULE_PARM_DESC(parameter_value_with_callback, "A module parameter with callback function");
