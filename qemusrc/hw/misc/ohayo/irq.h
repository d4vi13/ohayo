#ifndef IRQ_H
#define IRQ_H

#include "ohayo.h"

int 
enable_msi (PCIDevice *pdev, Error **errp);

void 
ohayo_raise (struct ohayo_state *ohayo_state, uint32_t vector);

void 
ohayo_lower (struct ohayo_state *ohayo_state, uint32_t vector);

bool
ohayo_check_irq_status (struct ohayo_state *ohayo_state, uint32_t vector);

#endif
