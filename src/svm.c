#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/processor.h>
#include <asm/msr.h>
#include <asm/io.h>
#include "../include/svm.h"

// Detect AMD-V support
bool svm_detect(void) {
    unsigned int eax, ebx, ecx, edx;

    // Check for AMD Processor
    cpuid(0x80000000, &eax, &ebx, &ecx, &edx);
    if (eax < 0x80000001) {
        printk(KERN_ERR "SVM: CPUID leaf 0x80000001 not supported\n");
        return false;
    }

    // Check for SVM support (AMD-V)
    cpuid(0x80000001, &eax, &ebx, &ecx, &edx);
    if (ecx & (1 << 2)) {
        printk(KERN_INFO "AMD-V is supported\n");
        return true;
    } else {
        printk(KERN_ERR "AMD-V is not supported\n");
        return false;
    }
}

// Enable SVM mode
void svm_enable(void) {
    unsigned long efer;

    // Read the EFER MSR
    rdmsrl(MSR_EFER, efer);

    // Set the SVME bit
    efer |= EFER_SVME;

    // Write back to the EFER MSR
    wrmsrl(MSR_EFER, efer);

    printk(KERN_INFO "SVM mode enabled\n");
}

// Enter SVM mode
void svm_enter(struct vmcb *vmcb) {
    // Check if the VMCB pointer is valid
    if (!vmcb) {
        printk(KERN_ERR "SVM: Invalid VMCB pointer\n");
        return;
    }

    // Convert the virtual address to a physical address
    unsigned long vmcb_phys = virt_to_phys(vmcb);
    if (!vmcb_phys) {
        printk(KERN_ERR "SVM: Failed to convert VMCB virtual address to physical address\n");
        return;
    }

    // Set the VMCB physical address in the MSR
    wrmsrl(MSR_VM_HSAVE_PA, vmcb_phys);
    printk(KERN_INFO "SVM: VMCB physical address set to 0x%lx\n", vmcb_phys);

    // Execute VMRUN
    printk(KERN_INFO "SVM: Executing VMRUN...\n");
    __asm__ volatile (
        "vmrun\n"
        :
        : "a" (vmcb)
        : "memory"
    );

    printk(KERN_INFO "SVM: Entered SVM mode\n");
}

void svm_exit(void) {
    wrmsrl(MSR_VM_HSAVE_PA, 0);

    printk(KERN_INFO "Exited SVM mode\n");
}