#include "hw/misc/ohayo/ohayo.h"
#include "hw/misc/ohayo/mmio.h"
#include "hw/misc/ohayo/irq.h"

static void
ohayo_realize (PCIDevice *pdev, Error **errp)
{
    struct ohayo_state *ohayo_state = OHAYO_STATE(pdev);
    memory_setup (ohayo_state);
    enable_msi(pdev, errp);
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
    k->class_id = PCI_CLASS_OTHERS;
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
