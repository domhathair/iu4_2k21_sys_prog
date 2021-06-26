#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>

int32_t value = 0;
char array[80] = "When you finaly saw it coming...\n";
static int len = 1;

dev_t dev = 0;
static struct proc_dir_entry *parent;

static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

static ssize_t read_proc(struct file *filp, char __user *buffer, size_t length, loff_t *offset);
static ssize_t write_proc(struct file *filp, const char *buff, size_t len, loff_t *off);

static struct file_operations proc_fops = {
    .read = read_proc,
    .write = write_proc};

static ssize_t read_proc(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
        if (len)
                len = 0;
        else
        {
                len = 1;
                return 0;
        }

        if (copy_to_user(buffer, array, 80))
                pr_err("Data send error!\n");

        return length;
}

static ssize_t write_proc(struct file *filp, const char *buff, size_t len, loff_t *off)
{
        if (copy_from_user(array, buff, len))
                pr_err("Data write error!\n");

        return len;
}

static int __init etx_driver_init(void)
{
        /*Мажорный номер*/
        if ((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) < 0)
        {
                pr_info("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d, minor = %d.\n", MAJOR(dev), MINOR(dev));

        parent = proc_mkdir("procfs", NULL);
        proc_create("procfs", 0666, parent, &proc_fops);

        pr_info("Device driver insert done!\n");
        return 0;
}

static void __exit etx_driver_exit(void)
{
        proc_remove(parent);

        unregister_chrdev_region(dev, 1);
        pr_info("Device driver remove done!\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
