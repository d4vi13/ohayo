#ifndef INIT_H
#define INIT_H

#include "ohayo.h"
#include "pci_handlers.h"

struct ohayo_ctrl*
get_ohayo_ctrl (void);

void
free_ohayo_ctrl (struct ohayo_ctrl* ctrl);

#endif

