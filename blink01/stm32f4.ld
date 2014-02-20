MEMORY
{
  flash(rx) : ORIGIN = 0x08000000, LENGTH = 1M
  ram(rwx)  : ORIGIN = 0x20000000, LENGTH = 128K
  ccm (rwx) : ORIGIN = 0x10000000, LENGTH = 64K
}

__stack_begin__ = ALIGN (ORIGIN(ccm) + LENGTH(ccm), 8);

SECTIONS
{
  .text : {
    /* vector table should go to the flash first */
    *(.startup);
    *(.text*);
    *(.rodata*);
   } > flash

  . = ALIGN(4);
  __romdata_begin__ = .;

  .data : AT(__romdata_begin__) {
    . = ALIGN(4);
    __data_begin__ = .;
    *(.data)
    __data_end__ = .;
  } > ram

  .bss (NOLOAD) : {
    . = ALIGN(4);
    __bss_begin__ = .;
    *(.bss)
    __bss_end__ = .;
  } > ram
}
