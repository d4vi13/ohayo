#include "chrdev.h"

ssize_t
ohayo_write (struct file *f, const char __user *buf, size_t len, loff_t *offset)
{
  size_t i = 0;
  u32 *buffer = (u32 *)buf;

  for (; i < len/4; i++)
    {
      if ((*offset + i) > 0x1000)
        break;

      writel (buffer[i], ctrl->mmio + *offset + i);
    }

  return i;
}

ssize_t
ohayo_read (struct file *f, char __user *buf, size_t len, loff_t *offset)
{
  size_t i = 0;
  u32 *buffer = (u32 *)buf;

  for (; i < len/4; i++)
    {
      if ((*offset + i) > 0x1000)
        break;

      buffer[i] = readl ( ctrl->mmio + *offset + i);
    }


  return i;
}

long int 
ohayo_ioctl (struct file *f, unsigned int ioctl_num, unsigned long ioctl_param)
{
  return 0;
}


int 
init_chrdev (struct device *dev)
{
  ctrl->major = register_chrdev (0, "ohayo", &ctrl->fops);
  if (ctrl->major < 0)
    {
      dev_err (dev, "unable to register char device \n");
      return ctrl->major;
    }

  ctrl->dev_num = MKDEV (ctrl->major, DEV_MINOR);
  
  // nome para a classe em /sys/class/
  ctrl->dev_class = class_create ("ohayo");  
  if (IS_ERR (ctrl->dev_class))
    {
      dev_err (dev, "unable to create class for char device\n");
      return PTR_ERR (ctrl->dev_class);
    }

  ctrl->dev = device_create (ctrl->dev_class, NULL, ctrl->dev_num, NULL, "ohayo"); 
  if (IS_ERR (ctrl->dev))
    {
      dev_err (dev, "unable to create device for char device\n");
      return PTR_ERR (ctrl->dev_class);
    }

  return 0;
}


