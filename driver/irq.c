#include "irq.h"

static irqreturn_t 
ohayo_irq_handler (int irq, void *ohayo_ctrl)
{
  pr_info("ohayo gozaimasu\n");
  writel(0x0, ctrl->mmio + 0x18);

  return IRQ_HANDLED;
}

int
init_irq (struct pci_dev *pdev)
{
  int err = 0;

  if (!pdev->msi_enabled)
    {
      dev_err (&pdev->dev, "msi isnt enabled on the device\n");
      return -ENXIO;
    }

  /* aloca espaco contiguo na IDT de no maximo 32 entradas */
  err = pci_alloc_irq_vectors (pdev, MSI_VECTOR_NUMS, MSI_VECTOR_NUMS, PCI_IRQ_MSI);
  if (err < 0)
    {
      dev_err (&pdev->dev, "unable to allocate msi vectors\n");
      return err;
    }
  
  dev_info (&pdev->dev, "allocated vector num %d\n", err);
  ctrl->allocated_vector_num = err;

  /* isso dara um irq number, ele nao eh uma correspondecia 
   * um pra um da idt, mas sim uma representacao do kernel
   *
   * o segundo parametro eh um misterio :(
   * talvez ele aponte o offset do interrupt no bloco de 
   * interrupts alocados.
   */
  err = pci_irq_vector (pdev, 0);
  if (err < 0)
    {
      dev_err (&pdev->dev, "unable to retrieve a irq number\n");
      return err;
    }

  ctrl->irq = err;
  dev_info (&pdev->dev, "irq num %d\n", ctrl->irq);

  err = request_irq (ctrl->irq, ohayo_irq_handler, 0, "ohayo dev", ctrl); 
  if (err < 0)
    {
      dev_err (&pdev->dev, "unable to bind handler to irq number\n");
      return err;
    }

  dev_info (&pdev->dev, "request irq %d\n", err);

  return 0;
}


