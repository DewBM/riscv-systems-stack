#!/bin/bash
qemu-system-riscv32 \
  -machine virt \
  -nographic \
  -bios none \
  -serial mon:stdio \
  -kernel kernel.elf
