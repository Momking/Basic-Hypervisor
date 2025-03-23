# Output directory for compiled binaries
OUTPUT_DIR := bin

# Kernel module name
MODULE_NAME := Basic-Hypervisor
obj-m += ${MODULE_NAME}.o

# Source files
${MODULE_NAME}-objs := \
    src/main.o \
    src/svm.o \
    src/vmcb.o

# Compilation flags
ccflags-y := -I$(PWD)/include

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf $(OUTPUT_DIR)

load:
	sudo insmod ${MODULE_NAME}.ko

unload:
	sudo rmmod ${MODULE_NAME}