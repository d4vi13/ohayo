#include "init.h"

// ohayo_ctrl ----------------------------------------------------------

static inline struct ohayo_ctrl*
alloc_ohayo_ctrl (void) 
{
  struct ohayo_ctrl *ctrl =  kzalloc (sizeof * ctrl, GFP_KERNEL); 
  if (!ctrl)
    {
      pr_err ("failed to allocate ohayo ctrl structure\n");
      return NULL;
    }

  return ctrl;
}

static inline void
init_ohayo_ctrl (struct ohayo_ctrl *ctrl) 
{
  /* init struct pci_driver */
  ctrl->pci_driver.name = DRIVER_NAME;
  ctrl->pci_driver.id_table = ohayo_ids;
  ctrl->pci_driver.probe = ohayo_probe;
  ctrl->pci_driver.remove = ohayo_remove;

  /* init struct file_operations */
  ctrl->fops.owner = THIS_MODULE;
  ctrl->fops.write = ohayo_write;
  ctrl->fops.read = ohayo_read;

  /* Use unlocked because the old
   * ioctl was fazed because it used
   * the BKL
   */
  ctrl->fops.unlocked_ioctl = ohayo_ioctl; 
}

struct ohayo_ctrl*
get_ohayo_ctrl (void) 
{
  struct ohayo_ctrl *ctrl  = alloc_ohayo_ctrl ();
  if (!ctrl)
    {
      pr_err ("unable to allocate ohayo ctrl structure\n");
      return NULL;
    }
  
  init_ohayo_ctrl (ctrl);

  return ctrl;
}

void
free_ohayo_ctrl (struct ohayo_ctrl *ctrl) 
{
  kfree(ctrl);
}

// ---------------------------------------------------------------------

