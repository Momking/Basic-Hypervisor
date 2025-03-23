#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include "../include/svm.h"
#include "../include/vmcb.h"

static struct vmcb *vmcb = NULL;

static int __init hypervisor_init(void) {
    printk(KERN_INFO "Starting the Hypervisor\n");

    // Detect AMD-V support
    if (!svm_detect()) {
        printk(KERN_ERR "AMD-V is not supported\n");
        return -ENODEV;
    }

    // Enable SVM mode
    svm_enable();

    // Allocate and initialize the VMCB
    vmcb = vmcb_alloc();
    if (!vmcb) {
        printk(KERN_ERR "Failed to allocate VMCB\n");
        return -ENOMEM;
    }

    // // Enter SVM mode
    // svm_enter(vmcb);

    printk(KERN_INFO "Hypervisor started successfully\n");
    return 0;
}

static void __exit hypervisor_exit(void) {
    printk(KERN_INFO "Exiting the Hypervisor\n");

    svm_exit();

    if (vmcb) {
        vmcb_free(vmcb);
        vmcb = NULL;
    }
}

module_init(hypervisor_init);
module_exit(hypervisor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nishant Thakur");
MODULE_DESCRIPTION("AMD-V Hypervisor Module");