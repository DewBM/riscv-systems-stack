#include "../../include/uart.h"

#define UART0_BASE 0x10000000
#define UART_THR   0x00
#define UART_LSR   0x05
#define LSR_EMPTY  0x20

static volatile unsigned char *uart = (unsigned char *)UART0_BASE;

void uart_putc(char c) {
    while ((uart[UART_LSR] & LSR_EMPTY) == 0);
    uart[UART_THR] = c;
}

void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

void uart_puthex(unsigned int val) {
    char hex[] = "0123456789ABCDEF";
    uart_puts("0x");

    for (int i = 28; i >= 0; i -= 4) {
        uart_putc(hex[(val >> i) & 0xF]);
    }
}
