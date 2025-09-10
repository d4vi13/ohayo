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

static uint64_t
ohayo_mmio_read(void *opaque, hwaddr addr, unsigned size)
{
    struct ohayo_state *dev = opaque;
    uint64_t ret = ~0ULL; // pq todo mundo faz isso?
    if (addr == 0x0)
        ret = dev->r0;
    return ret;
}

static void
ohayo_mmio_write(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    struct ohayo_state *dev = opaque;
    if (addr == 0x0)
        dev->r0 = val;
}


/* /include/system/memory.h 
 * valid = {0}: permite acessos de tamanhos arbitrários
 * impl.min_access_size = 4: acessos menores que 4 bytes são arredondados para 4 bytes
 * impl.max_access_size = 4: acessos maiores que 4 bytes são divididos em múltiplos de 4 bytes
 */
const MemoryRegionOps ohayo_mmio_ops = {
    .read = ohayo_mmio_read,
    .write = ohayo_mmio_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid  = {0},
    .impl = {
        .min_access_size = 4,
        .max_access_size = 4,
    }
};

/* 
 * Inicializa a região de memória MMIO e associa ao BAR do dispositivo PCI
 * memory_region_init_io: reserva uma região de 4 KB do "espaço físico" emulado
 * pci_register_bar: associa essa região de memória ao BAR 0 do dispositivo PCI
 */
    static void
memory_setup (struct ohayo_state *ohayo_state)
{
    memory_region_init_io(
            &ohayo_state->mmio,
            OBJECT(ohayo_state),
            &ohayo_mmio_ops, 
            ohayo_state,
            "ohayo-mmio",
            0x1000
            );

    pci_register_bar(
            &ohayo_state->pdev,
            0,
            PCI_BASE_ADDRESS_SPACE_MEMORY,
            &ohayo_state->mmio
            );
}


static void
ohayo_realize (PCIDevice *pdev, Error **errp)
{
    struct ohayo_state *ohayo_state = OHAYO_STATE(pdev);
    memory_setup (ohayo_state);
    return;
}

/*
 * o registo abaixo torna o tipo conhecido ao qemu
 * mas o class_init que de fato registra o que o tipo faz
 * eh aqui que será o overwrite de metodos herdados do pai
 * e outra coisas(sla)
 */
static void
ohayo_class_init (ObjectClass *class, const void *data)
{
    /* macro do alem fds */
    PCIDeviceClass *k = PCI_DEVICE_CLASS(class); 

    k->realize = ohayo_realize;
    k->device_id = 0xcafe;
}

/*
 * array para ser passado ao DEFINE_TYPES
 * e ser registrado. 
 * typeInfo descreve um tipo e seus hooks de inicializacao
 */  
static const TypeInfo ohayo_type[] = {
    {
        .name = TYPE_OHAYO_DEVICE,
        .parent = TYPE_PCI_DEVICE,
        .instance_size = sizeof(struct ohayo_state),
        .class_init = ohayo_class_init,
        // interface pode ser convencional, express ou legacy
        .interfaces    = (const InterfaceInfo[]) {
            { INTERFACE_CONVENTIONAL_PCI_DEVICE },
            { },
        },
    }
};

/*
 * eh possivel registrar um dispositivo usando 
 * o macro type_init que chamara uma funcao que
 * deve chamar type_register_static para registrar o typo,
 * o macro abaixo tem o mesmo proposito e chamara o 
 * type_register_static_array e registrara todos os dispositivos
 * do array 
 */
DEFINE_TYPES(ohayo_type); 
