# Bare-Metal RISC-V Kernel

This project is a minimal bare-metal operating system kernel for the RISC-V RV32 architecture, developed to understand and demonstrate how real operating systems interact with hardware at the lowest level. It focuses on bootstrapping, trap handling, and timer interrupts without relying on any runtime, standard library, or existing OS.

## 1. Project Overview
The kernel runs directly in **machine mode** on QEMU and provides:
- A custom boot sequence starting from `_start`
- A linker-controlled memory layout
- Low-level trap handling using RISC-V CSRs
- Context saving and restoring in assembly
- A C-level trap handler
- Machine timer interrupts for periodic execution

This project emphasizes:
- RISC-V privilege architecture
- OS startup and execution environment
- Exception and interrupt handling
- Interaction between assembly and C in kernel code

---

## 2. Current Progress
- Custom linker script defining kernel memory layout
- Startup code in assembly:
    - Stack initialization
    - `mscratch` setup for trap stack
    - Transfer of control to `kernel_main`
- Trap vector installation using `mtvec`
- Trap entry in assembly:
    - Stack switching using `mscratch`
    - Register context save/restore
    - Call into C trap handler
- C-level trap handler:
    - Distinguishes exceptions and interrupts
    - Handles illegal instructions and software traps
    - Handles machine timer interrupts
- Machine timer interrupt setup using:
    - `mtime`
    - `mtimecmp`
- Periodic timer interrupt generation and re-arming

---

## 3. Boot and execution flow

### 3.1 Linker Script (`linker.lds`)
Linker script tells the linker how to organize code from the input objects.

The linker script defines:
- Entry point
- Where the kernel is loaded in memory 
- The layout of:
    - `.text` : 
    - `.rodata`
    - `.data`
    - `.bss`
- Stack regions:
    - Kernel stack
    - Trap stack

### 3.2 Startup Code (`startup.S`)
Execution starts at `_start`

Responsibilities:
1. Set the stack pointer.
    ```assembly
    la sp, __stack_top
    ```
2. Initialize trap stack
    ```assembly
    la t0, __trap_stack_top
    csrw mscratch, t0
    ```
3. Jump to kernel
    ```assembly
    call kernel_main
    ```
At this point, the system starts running C code in the kernel environment.

### 3.3 Kernel Entry (`kernel_main`)
This performs system initialization.

1. Install the trap vector
```c
csr_write(mtvec, (unsigned int)trap_vector);
```
This stores the address of the `trap_vector` function to the `mtvec` register.
```c
extern void trap_vector(void);
```
This tells the function `trap_vector` is defined externally (in `trap.S` assembly file).

2. Reset the timer and enable global and timer interrupts
```c
reset_time();
csr_set(mie, MIE_MTIE);
csr_set(mstatus, MSTATUS_MIE);
```

3. Enter idle loop and wait for interrupts
```c
while (1) {
	asm volatile("wfi");
}
```

From here-on, execution is driven by interrupts

### 3.4 Trap Handling
When an exception or an interrupt occurs:
1. `pc` is loaded with the address of the `trap_vector` function which is stored in the `mtvec` register.

### 3.5 Trap Entry (`trap.S`)
`trap_vector` function is defined here.

Responsibilities:
1. Switch from task stack to trap stack:
```assembly
csrrw sp, mscratch, sp
```
2. Save the general purpose registers on the trap stack.
3. Load `mcause` and call the `trap_handler` function to handle the trap:
```assembly
    csrr a0, mcause
    call trap_handler
```
4. When `trap_handler` returns, restore the registers from stack.
5. Switch back to task stack:
```assembly
csrrw sp, mscratch, sp
```
6. Return to interrupted context:
```assembly
mret
```

### 3.6 Trap Handler(`trap_handler.c`)
This is the kernel function that is responsible for handling the trap.

Handles:
- Exceptions:
    - Illegal instructions
- Interrupts:
    - Machine Timer Interrupts

### 3.7 Timer Interrupts
A timer interrupt is fired when the value in `mtimecmp` register is less then the value in `mtime` register.

Flow:
1. Initialize the timer:
    ```c
    *mtimecmp = *mtime + delta;
    ```
    - *This causes the interrupt to occur after **delta** clock cycles.*

2. Enable timer interrupt.
3. When `*mtime >= *mtimecmpt` an interrupt is raised.
    - *Timer should be rearmed when handling the interrupt.*
