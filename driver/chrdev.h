#ifndef CHRDEV_H
#define CHRDEV_H

#include "ohayo.h"

ssize_t
ohayo_write (struct file *f, const char __user *buf, size_t len, loff_t *offset);

ssize_t
ohayo_read (struct file *f, char __user *buf, size_t len, loff_t *offset);

long int 
ohayo_ioctl (struct file *f, unsigned int ioctl_num, unsigned long ioctl_param);

#endif 
