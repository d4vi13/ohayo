#ifndef PCI_HANDLERS
#define PCI_HANDLERS

#include "ohayo.h"
#include "chrdev.h"

int 
ohayo_probe(struct pci_dev *dev, const struct pci_device_id *id);

void 
ohayo_remove(struct pci_dev *dev);

#endif
