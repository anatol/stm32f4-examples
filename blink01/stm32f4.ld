MEMORY
{
  flash(rx) : ORIGIN = 0x08000000, LENGTH = 1M
  ram(rwx)  : ORIGIN = 0x20000000, LENGTH = 128K
}

_stack_start = ALIGN (ORIGIN(ram) + LENGTH(ram), 8);

SECTIONS
{
  .text : {
    /* vector table should go to the flash first */
    *(.vector_table);
    *(.text*);
    *(.rodata*);
   } > flash
}
