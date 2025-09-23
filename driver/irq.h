#ifndef IRQ_H
#define IRQ_H

#include "ohayo.h"

#define MSI_VECTOR_NUMS 1

int
init_irq (struct pci_dev *pdev);

#endif
