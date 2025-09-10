#ifndef OHAYO_H
#define OHAYO_H
#include "qemu/osdep.h"
#include "qemu/log.h"
#include "qemu/units.h"
#include "hw/pci/pci.h"
#include "hw/pci/msi.h"
#include "qemu/timer.h"
#include "qom/object.h"
#include "qemu/module.h"
#include "qapi/visitor.h"

#define TYPE_OHAYO_DEVICE "ohayo"

DECLARE_INSTANCE_CHECKER(struct ohayo_state, OHAYO_STATE, TYPE_OHAYO_DEVICE)

struct ohayo_state
{
    PCIDevice pdev;
    MemoryRegion mmio;

    uint32_t r0;
};

#endif
