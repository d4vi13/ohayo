#include "hw/misc/ohayo/mmio.h"

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
void
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
