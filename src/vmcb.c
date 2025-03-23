#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include "../include/vmcb.h"

// Allocate and initialize the VMCB
struct vmcb *vmcb_alloc(void) {
    struct vmcb *vmcb = kmalloc(sizeof(struct vmcb), GFP_KERNEL);
    if (!vmcb) {
        printk(KERN_ERR "VMCB: Failed to allocate memory\n");
        return NULL;
    }

    // Initialize the VMCB (simplified for demonstration)
    memset(vmcb, 0, sizeof(struct vmcb));

    printk(KERN_INFO "VMCB: Allocated and initialized\n");
    return vmcb;
}

// Free the VMCB
void vmcb_free(struct vmcb *vmcb) {
    if (vmcb) {
        kfree(vmcb);
        printk(KERN_INFO "VMCB Freed\n");
    }
}