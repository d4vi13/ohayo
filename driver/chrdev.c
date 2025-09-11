#include "chrdev.h"

ssize_t
ohayo_write (struct file *f, const char __user *buf, size_t len, loff_t *offset)
{
  size_t i = 0;

  u32 *buffer = (u32 *)buf;
  while (len - i > 4) 
    {
      if ((*offset + i) > 0x1000)
        break;

      writel (buffer[i/4], ctrl->mmio + *offset + i);
      i += 4;
    }

  return i;
}

ssize_t
ohayo_read (struct file *f, char __user *buf, size_t len, loff_t *offset)
{
  size_t i = 0;
  u32 *buffer = (u32 *)buf;

  while (len - i > 4) 
    {
      if ((*offset + i) > 0x1000)
        break;

      buffer[i/4] = readl ( ctrl->mmio + *offset + i);
      i += 4;
    }

  return i;
}

long int 
ohayo_ioctl (struct file *f, unsigned int ioctl_num, unsigned long ioctl_param)
{
  return 0;
}

