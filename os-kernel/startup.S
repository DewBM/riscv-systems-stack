.section .text.init
.globl _start
_start:
    la sp, __stack_top       # Set stack pointer
    call clear_bss

    # diable global interrupts
    csrrc x0, mstatus, 0x8 # clear the MIE bit in the mstatus register

    # load trap stack top to the mscratch register
    la t0, __trap_stack_top
    csrw mscratch, t0

    # Jump to kernel
    call kernel_main

1:  j 1b                     # Infinite loop

clear_bss:
    la a0, __bss_start
    la a1, __bss_end
zero_loop:
    bge a0, a1, done
    sw zero, 0(a0)
    addi a0, a0, 4
    j zero_loop
done:
    ret
