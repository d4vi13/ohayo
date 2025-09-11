#include "ohayo.h"
#include "init.h"

struct ohayo_ctrl *ctrl; 

struct pci_device_id ohayo_ids[] = {
  {PCI_DEVICE(VENDOR_ID, OHAYO_DEV_ID), },
  {}
};

/* Usado em tempo de build para criar arquivos de dependencias
 * que serao usados para permitir que o modulo seja carregado
 * quando um dispositivo compativel for inserido
 */
MODULE_DEVICE_TABLE(pci, ohayo_ids);

static int __init
ohayo_init(void)
{
  int err;
  ctrl = get_ohayo_ctrl ();
  if (!ctrl)
  {
    pr_err ("unable to get ohayo ctrl structure\n");
    return -ENOMEM;
  }

  err = pci_register_driver (&ctrl->pci_driver); 
  if (err < 0) 
    pr_err ("couldnt register ohayo driver\n");

  return err;
}

static void __exit
ohayo_exit (void)
{
  pci_unregister_driver (&ctrl->pci_driver);
  free_ohayo_ctrl (ctrl);
  printk (KERN_INFO "sayonara.\n");
}

module_init(ohayo_init);
module_exit(ohayo_exit);
