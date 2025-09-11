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

  /* Cria cookie da regiao mapeada.
   * Essencialmente eh uma estrutura opaca
   * que representa nosso bar mapeado em uma
   * regiao de memoria virtual
   */
  ctrl->mmio = pci_iomap (dev, 0, 0x1000);
  if (!ctrl->mmio)
    {
      dev_err (&dev->dev,"unable to memory map pci bar\n");
      return -ENOMEM;
    }

  writel (0x0b0b, ctrl->mmio);
  printk (KERN_INFO "valor lido %x\n", readl(ctrl->mmio));

  return 0;
}

void 
ohayo_remove(struct pci_dev *dev)
{
  return;
}

