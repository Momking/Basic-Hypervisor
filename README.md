# Basic-Hypervisor

A basic type-2 hypervisor supporting AMD-V hardware virtualization for educational purposes. This project demonstrates how to enable AMD-V (hardware virtualization) using a Linux kernel module.

## Features
- Enables AMD-V on supported AMD processors.
- Simple and lightweight kernel module implementation.
- Easy to build, load, and test.

## Requirements
To use this project, ensure your system meets the following requirements:
1. **AMD Processor**: The system must have an AMD processor.
2. **AMD-V Support**: The processor must support AMD-V hardware virtualization.
3. **Linux Kernel**: A Linux-based operating system with kernel headers installed.

## Installation

### 1. Install Dependencies
Install the necessary build tools and Linux kernel headers:
```bash
sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)
```
### 2. Clone the Repository
Clone the repository to your local machine:
```bash
git clone https://github.com/Momking/Basic-Hypervisor.git
cd Basic-Hypervisor
```

## Usage

### 1. Build the kernel Module
Compile the kernel module using the provided Makefile:
```bash
make
```
This will generate the Init.ko kernel module.
### 2. Load the Module
Load the kernel module into the Linux kernel:
```bash
make load
```
### 3. Check Kernel Logs
Verify that the module loaded successfully by checking the kernel logs:
```bash
make load
```
### 4. Unload the Module
When you're done testing, unload the module:
```bash
make unload
```
### 5. Clean Up
To clean up the generated files, run: 
```bash
make clean
```