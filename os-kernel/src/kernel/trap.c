#include "../../include/uart.h"
#include "../../include/timer.h"
#include "../../include/schedule.h"

#define CAUSE_INTERRUPT (1U << 31)
#define CAUSE_CODE_MASK 0x7FFFFFFF

#define IRQ_M_TIMER 7

uint32_t *trap_handler(unsigned int cause, uint32_t *sp) {
    // uart_puts("Starting trap  handler...\n");

    if (cause & CAUSE_INTERRUPT) {
	// trap is caused by an interrupt.
	unsigned int irq = cause & CAUSE_CODE_MASK;

	if (irq == IRQ_M_TIMER) {
	    // handle timer interrupts
	    uart_puts("Timer interrupt occured...\n");
	    reset_timer();
	    return schedule(sp);
	}
    }
    else {
	uart_puts("[KERNEL] Exception: mcause = ");
	uart_puthex(cause);
	uart_puts("\n");
	
	while(1);
    }

    return sp;
}
