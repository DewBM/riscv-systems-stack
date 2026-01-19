CC = riscv32-unknown-elf-gcc
CFLAGS = -march=rv32im_zicsr -mabi=ilp32 -nostdlib -ffreestanding -O0
LDFLAGS = -T linker.ld

SRCS = startup.S src/trap.S src/kernel/uart.c src/kernel/trap.c src/kernel/main.c 
OBJS = $(SRCS:.c=.o)

all: bare.elf

bare.elf:
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $@

clean:
	rm -f kernel.elf
