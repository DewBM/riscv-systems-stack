    .text
    .global trap_vector
trap_vector:
    # swap current sp with the trap_stack_top
    csrrw sp, mscratch, sp

    # allocate trap frame (64 bytes = save 16y registers)
    addi sp, sp, -64

    # save general purpose registers before trap handling
    sw ra,  60(sp)
    sw t0,  56(sp)
    sw t1,  52(sp)
    sw t2,  48(sp)
    sw a0,  44(sp)
    sw a1,  40(sp)
    sw a2,  36(sp)
    sw a3,  32(sp)
    sw a4,  28(sp)
    sw a5,  24(sp)
    sw a6,  20(sp)
    sw a7,  16(sp)
    sw s0,  12(sp)
    sw s1,  8(sp)
    sw s2,  4(sp)
    sw s3,  0(sp)

    csrr a0, mcause # save the cause of the trap in the a0 register
    addi a1, sp, 0

    call trap_handler

    addi sp, a0, 0

    # restore saved registers
    lw ra,  60(sp)
    lw t0,  56(sp)
    lw t1,  52(sp)
    lw t2,  48(sp)
    lw a0,  44(sp)
    lw a1,  40(sp)
    lw a2,  36(sp)
    lw a3,  32(sp)
    lw a4,  28(sp)
    lw a5,  24(sp)
    lw a6,  20(sp)
    lw a7,  16(sp)
    lw s0,  12(sp)
    lw s1,  8(sp)
    lw s2,  4(sp)
    lw s3,  0(sp)

    # restore original stack
    addi sp, sp, 64
    csrrw sp, mscratch, sp

    mret
