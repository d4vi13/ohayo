#include "hw/misc/ohayo/mmio.h"

static uint64_t
ohayo_mmio_read(void *opaque, hwaddr addr, unsigned size)
{
    struct ohayo_state *dev = opaque;
    uint64_t ret = ~0ULL; // pq todo mundo faz isso?
    switch (addr % 4) 
      {
        case R0:
          ret = dev->r[R0];
          break;
        case R1:
          ret = dev->r[R1];
          break;
        case R2:
          ret = dev->r[R2];
          break;
        case R3:
          ret = dev->r[R3];
          break;
        case IRQ_STATUS:
          ret = dev->r[IRQ_STATUS];
          break;
        default:
          break;
      }

    return ret;
}

static void
ohayo_mmio_write(void *opaque, hwaddr addr, uint64_t val64, unsigned size)
{
    struct ohayo_state *dev = opaque;
    uint32_t val = (uint32_t) val64;
    switch (addr % 4) 
      {
        case R0:
          dev->r[R0] = val;
          break;
        case R1:
          dev->r[R1] = val;
          break;
        case R2:
          dev->r[R2] = val;
          break;
        case R3:
          dev->r[R3] = val;
          break;
        case IRQ_RAISE:
          ohayo_raise (dev, val);
          break;
        case IRQ_LOWER:
          if (ohayo_check_irq_status (dev, val))
            ohayo_lower (dev, val);
          break;
        default:
          break;
      }
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
