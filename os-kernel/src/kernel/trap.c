#include "../../include/uart.h"

#define CAUSE_INTERRUPT (1U << 31)
#define CAUSE_CODE_MASK 0x7FFFFFFF

#define IRQ_M_TIMER 7

void trap_handler(unsigned int cause) {
    // uart_puts("Starting trap  handler...\n");

    if (cause & CAUSE_INTERRUPT) {
	// trap is caused by an interrupt.
	unsigned int irq = cause & CAUSE_CODE_MASK;

	if (irq == IRQ_M_TIMER) {
	    // handle timer interrupts
	    uart_puts("Timer interrupt occured...\n");
	}
    }
    else {
	uart_puts("[KERNEL] Exception: mcause = ");
	uart_puthex(cause);
	uart_puts("\n");
	
	while(1);
    }
}
