ENTRY(_start)

MEMORY
{
  RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS
{
  .text : {
    *(.text.init)
    *(.text*)
  } > RAM

  .rodata : {
    *(.rodata*)
  } > RAM

  .data : {
    *(.data*)
  } > RAM

  .bss : {
    __bss_start = .;
    *(.bss*)
    *(COMMON)
    __bss_end = .;
  } > RAM

  .stack (NOLOAD) : {
    . = . + 4K;
    __stack_top = .;
  } > RAM

    .trap_stack (NOLOAD) : {
	. = . + 4K;
	__trap_stack_top = .;
    } > RAM
}
