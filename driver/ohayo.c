#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/pci.h>	

MODULE_LICENSE("GPL");
MODULE_AUTHOR("davi c. ribeiro");
MODULE_DESCRIPTION("ohayo device driver");

#define VENDOR_ID 0x1234
#define OHAYO_DEV_ID 0xcafe

static int 
ohayo_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
  printk(KERN_INFO "dispositivo carregado\n");
  printk(KERN_INFO "vendor: %x id: %x\n", id->vendor, id->device);
  return 0;
}

static void 
ohayo_remove(struct pci_dev *dev)
{
  return;
}

static struct pci_device_id ohayo_ids[] = {
  {PCI_DEVICE(VENDOR_ID, OHAYO_DEV_ID), },
  {}
};

/* Usado em tempo de build para criar arquivos de dependencias
 * que serao usados para permitir que o modulo seja carregado
 * quando um dispositivo compativel for inserido
 */
MODULE_DEVICE_TABLE(pci, ohayo_ids);

/*
 * id_table - dispositivos compativeis
 * probe - funcao executada ao inserir dispositivo
 */
static struct pci_driver ohayo_driver = {
  .name = "ohayo-driver",
  .id_table = ohayo_ids,
  .probe = ohayo_probe,
  .remove = ohayo_remove,
};

static int __init
ohayo_init(void)
{
  int err = pci_register_driver(&ohayo_driver); 
  if (err < 0) 
    printk (KERN_NOTICE "couldnt register ohayo driver\n");

	return err;
}

static void __exit
ohayo_exit (void)
{
	printk(KERN_INFO "sayonara.\n");
}

module_init(ohayo_init);
module_exit(ohayo_exit);
