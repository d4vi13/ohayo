#ifndef OHAYO_H
#define OHAYO_H
#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/pci.h>  

#define VENDOR_ID 0x0000
#define OHAYO_DEV_ID 0xcafe
#define DRIVER_NAME "ohayo-driver" 

struct ohayo_ctrl {
  struct pci_driver pci_driver;
  void __iomem *mmio; // __iomem marca a regiao de memoria como mmio para checagem estatica
};

extern struct ohayo_ctrl *ctrl;
extern struct pci_device_id ohayo_ids[];

MODULE_LICENSE("GPL");
MODULE_AUTHOR("davi c. ribeiro");
MODULE_DESCRIPTION("ohayo device driver");

#endif
