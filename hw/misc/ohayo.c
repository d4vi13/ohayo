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

// define dispositivo novo
struct ohayo_state
{
  PCIDevice pdev; // herda da clase do pci

  uint32_t r0; // registrador
};

static void
ohayo_realize (PCIDevice *pdev, Error **errp)
{
  printf("gozaimasu\n");
  return;
}

static void
ohayo_instance_init (Object *obj)
{
  printf("ohayoo\n");
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
    .instance_init = ohayo_instance_init,
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
