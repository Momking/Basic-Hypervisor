#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

void enable_amd_v(void);

void enable_amd_v(void) {
    unsigned long long efer;
    __asm__ volatile("rdmsr" : "=A"(efer) : "c"(0xC0000080));
    efer |= (1 << 12);
    __asm__ volatile("wrmsr" : : "c"(0xC0000080), "A"(efer));
}

static int __init amd_v_init(void) {
    unsigned int eax, ebx, ecx, edx;
    eax = 0x80000001;
    __asm__ volatile("cpuid"
                     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                     : "a"(eax));
    if (ecx & (1 << 2)) {
        printk(KERN_INFO "AMD-V is supported.\n");
        enable_amd_v();
        printk(KERN_INFO "AMD-V enabled.\n");
    } else {
        printk(KERN_INFO "AMD-V is not supported.\n");
    }
    return 0;
}

static void __exit amd_v_exit(void) {
    printk(KERN_INFO "AMD-V module unloaded.\n");
}

module_init(amd_v_init);
module_exit(amd_v_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nishant Thakur");
MODULE_DESCRIPTION("AMD-V Hypervisor Module");