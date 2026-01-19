#include "../../include/uart.h"

#define MSTATUS 0x300
#define MTVEC 0x305
#define MIE 0x304

#define MIE_MTIE (1U << 7)
#define MSTATUS_MIE (1U << 3)

#define csr_write(csr, val) \
    asm volatile("csrw " #csr ", %0" :: "r"(val))

#define csr_set(csr, val) \
    asm volatile("csrs " #csr ", %0" :: "r"(val))


extern void trap_vector(void);


void kernel_main() {
    uart_puts("Kernel starting...\n");

    //uart_puthex((unsigned int)trap_vector);

    // install trap vector
    csr_write(mtvec, (unsigned int)trap_vector);

    // enable timer interrupts
    //csr_set(mie, MIE_MTIE);

    // enable global interrupts
    //csr_set(mstatus, MSTATUS_MIE);

    //uart_puts("Traps and machine timer interrupts enabled...\n");

    asm volatile(".word 0xffffffff");

}
