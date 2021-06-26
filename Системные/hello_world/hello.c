#include <linux/module.h>       /* Необходим для любого модуля ядра */
#include <linux/kernel.h>       /* Здесь находится определение KERN_ALERT */

MODULE_LICENSE("GPL");

int init_module(void)
{
        printk("<1>Hello world 1.\n");
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_ALERT "Goodbye world 1.\n");
}