MEMORY
{
  rom(rx) : ORIGIN = 0x08000000, LENGTH = 1M
  ram(rwx)  : ORIGIN = 0x20000000, LENGTH = 128K
  ccm (rwx) : ORIGIN = 0x10000000, LENGTH = 64K
}

INCLUDE libopencm3_stm32f4.ld
