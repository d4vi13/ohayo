#include "pci_handlers.h"

int 
ohayo_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
  int err = 0;
  printk(KERN_INFO "dispositivo carregado\n");
  printk(KERN_INFO "vendor: %x id: %x\n", id->vendor, id->device);

  /* Nesse ponto o BAR deve ter um endereco valido 
   * alocado anteriormente pelo kernel apos ter feito
   * a enumeracao dos barramentos 
   *
   * Liga no command register do espaco de configuracao
   * a habilidade responder a acessos de memoria e io
   */
  err = pci_enable_device(dev); 
  if (err < 0)
  {
    dev_err (&dev->dev, "unable to enable ohayo device\n");
    return err;
  }

  printk(KERN_INFO "ohayo device enabled\n");

  /* Marca regiao como sendo utilizada dentro do kernel*/
  err = pci_request_region (dev, 0, DRIVER_NAME);
  if (err < 0) 
    {
      dev_err (&dev->dev,"requested memory region is busy\n");
      return err;
    }

  printk(KERN_INFO "memory reserved\n");

  return 0;
}

void 
ohayo_remove(struct pci_dev *dev)
{
  return;
}

