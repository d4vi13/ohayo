#include "pci_handlers.h"

static inline int 
memory_setup (struct pci_dev *dev)
{
  /* Marca regiao como sendo utilizada dentro do kernel*/
  err = pci_request_region (dev, 0, DRIVER_NAME);
  if (err < 0) 
    {
      dev_err (&dev->dev,"requested memory region is busy\n");
      return err;
    }

  dev_info (&dev->dev, "memory reserved\n");

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
  dev_info (&dev->dev, "valor lido %x\n", readl(ctrl->mmio));
  dev_info (&dev->dev, "valor lido %x\n", readl(ctrl->mmio+4));

  return 0;
}

int 
ohayo_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
  int err = 0;

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

  dev_info (&dev->dev, "device enabled\n");

  err = memory_setup (dev);
  if (err < 0)
    {
      dev_err (&dev->dev, "unable to setup memory");
      return err;
    }

  dev_info (&dev->dev, "memory configured\n");

  return 0;
}

void 
ohayo_remove(struct pci_dev *dev)
{
  if (!ctrl->mmio)
    pci_iounmap (dev, ctrl->mmio);

  pci_disable_device (dev);
  pci_release_region (dev, 0);

  return;
}

