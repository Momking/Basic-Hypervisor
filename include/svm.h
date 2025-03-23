#ifndef SVM_H
#define SVM_H

#include <linux/types.h>
#include "vmcb.h"

// Function prototypes
bool svm_detect(void);
void svm_enable(void);
void svm_enter(struct vmcb *vmcb);
void svm_exit(void);

#endif