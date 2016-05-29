#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>

#define class_name "chrdevClass"
#define dev_name "chrdev"
#define buffsize 256

static int majorNumber;
static char message[buffsize] = {0};
static int size_of_message = 0;
static int open_counter = 0;
static struct class *chrdevClass = NULL;
static struct device *chrdev = NULL;

static ssize_t dev_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset){
	int error_count = 0;
	error_count = copy_to_user(buffer, message, size_of_message);
	if(error_count == 0)
	{
		printk(KERN_INFO "chrdev: Received %d of characters from the kernel space\n", size_of_message);	
		return (size_of_message=0);
	}
	else
	{
		printk(KERN_ALERT "chrdev: Failed to read %d of characters from the kernel space\n", error_count);
		return -EFAULT;
	}	
}

static ssize_t dev_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset){
	sprintf(message,"%s(%s of letters)", buffer, len);
	size_of_message = strlen(message);
	printk(KERN_INFO "chrdev: received %d number of characters from user space\n", len);
	return len;
}

static int dev_open(struct inode *inodep, struct file *filep){
	open_counter++;
	printk(KERN_INFO "chrdev: %d number of time(s) opened\n", open_counter);
	return 0;
}

static int dev_close(struct inode *inodep, struct file *filep){
	printk(KERN_INFO "chrdev: chrdev successfully closed\n");
	return 0;
}

struct file_operations *fops = {
	.read = dev_read,
	.write = dev_write,
	.open = dev_open,
	.release = dev_close
};

static int __init chrdev_init(void){
	//register a major number
	majorNumber = register_chrdev(0, dev_name, &fops);
	if(majorNumber<0)
	{
		printk(KERN_ALERT "chrdev: Failed to register a major number\n");
		return majorNumber;	
	}
	printk(KERN_INFO "chrdev: Successfully register a major number of %d\n" majorNumber);
	
	//register the device class
	chrdevClass = create_class(
}



