/**
 * @file hello.c
 * @author James Jallorina
 * @date 11.4.2015
 * @version 0.1
 * @brief An introductory "Hello World!" loadable kernel module (LKM) that can
 * display a message in /var/log/kern.log file when the module is loaded and
 * removed.
 */
//Core header for loading LKMs into the kernel
#include <linux/module.h>

//Contains types, macros, functions for the kernel
#include <linux/kernel.h>

//Macros used to mark up functions e.g., __init __exit
#include <linux/init.h>

/*use modinfo to see details of the module */
//< The license type -- this aafects runtime behavior
MODULE_LICENSE("GPL");
//< The author -- visible when you use modinfo
MODULE_AUTHOR("James Jallorina");
//< The Description -- see modinfo
MODULE_DESCRIPTION("A simple linux driver for the beaglebone black");
//< The version of the module
MODULE_VERSION("0.1");

static char *name = "world";  //an example of LKM argument -- default is "world"
//Param desc. charp = char ptr, S_IRUGO can read/not changed
module_param(name, charp, S_IRUGO);
//parameter description
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");

/*__init function used to display a message in /var/log/kern.log when module is loaded into the kernel */

static int __init hello_beaglebone_init(void)
{
        printk(KERN_INFO "Hello %s from the beaglebone LKM!\n", name);
        return 0; // a non 0 return mean a module is failed to load
}

/*__exit function used to display a message in /var/log/kern.log when module is removed from the kernel */

static void __exit hello_beaglebone_exit(void)
{
        printk(KERN_INFO "Goodbye %s from the beagleone LKM!\n", name);
}

/* module_init & module_exit macros from linux/init.h, which is used to identify the initialization function at insertion time and the cleanup function */


module_init(hello_beaglebone_init);
module_exit(hello_beaglebone_exit);
