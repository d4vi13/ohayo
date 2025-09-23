obj-m += ohayod.o 
ohayod-objs += ohayo.o init.o irq.o pci_handlers.o chrdev.o 

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
