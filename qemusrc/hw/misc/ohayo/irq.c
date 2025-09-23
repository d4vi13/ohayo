#include "irq.h"

int 
enable_msi (PCIDevice *pdev, Error **errp)
{
  int err;

  /*
   * Cria e configura a capability no config space
   * pdev - duh
   * 0 - dica de onde por no lista de capacidades
   * MSI_VECTOR_NUMS - quantos interrupts diferente tera
   * true - usa enderecos de 64 bits
   * false - num entendi ainda
   */
  err = msi_init (pdev, 0, MSI_VECTOR_NUMS, true, false , errp);
  if (err < 0)
    return err;

  return 0;
}

void 
ohayo_raise (struct ohayo_state *ohayo_state, uint32_t vector) 
{
  ohayo_state->r[IRQ_STATUS] |= (1 << vector);
  PCIDevice *pdev = (PCIDevice*) ohayo_state;
  if (msi_enabled (pdev))
    msi_notify (pdev, vector); 

  return;
} 

void 
ohayo_lower (struct ohayo_state *ohayo_state, uint32_t vector) 
{
  ohayo_state->r[IRQ_STATUS] &= ~(1 << vector);

  return;
}

bool
ohayo_check_irq_status (struct ohayo_state *ohayo_state, uint32_t vector)
{
  return (((1 << vector) & ohayo_state->r[IRQ_STATUS]) != 0);
}


