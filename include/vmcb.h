#ifndef VMCB_H
#define VMCB_H

#include <linux/types.h>

// VMCB structure
struct vmcb {
    uint8_t reserved[1024]; // Placeholder for VMCB structure
};

// Function prototypes
struct vmcb *vmcb_alloc(void);
void vmcb_free(struct vmcb *vmcb);

#endif