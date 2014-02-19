#include <stdint.h>
#include <stdbool.h>

extern uint32_t __stack_begin__;
extern uint32_t __romdata_begin__;
extern uint32_t __data_begin__;
extern uint32_t __data_end__;
extern uint32_t __bss_begin__;
extern uint32_t __bss_end__;

void application(void);
void crt0(void);

__attribute__ ((section(".startup")))
const void *vector_table[] = {
    &__stack_begin__, // Stack Pointer
    &crt0   // Reset Vector
};

void crt0(void) {
  // initialize data section
  uint32_t *src = &__romdata_begin__;
  uint32_t *dest = &__data_begin__;

  while(dest < &__data_end__) {
    *dest = *src;

    src++;
    dest++;
  }

  // initialize bss with zero
  dest = &__bss_begin__;
  while (dest < &__bss_end__) {
    *dest = 0;
    dest++;
  }

  application();

  while(true) {};
}


#define RCCBASE   0x40023800
#define GPIODBASE 0x40020C00

#define MEM(address) (*(volatile uint32_t *)(address))

void inline wait(int period) {
  for (int i = 0; i < 50000 * period; i++) {
    __asm("nop");
  }
}

void application() {
  uint32_t ra;

  ra = MEM(RCCBASE + 0x30);
  ra |= 1 << 3; //enable port D
  MEM(RCCBASE + 0x30) = ra;

  //d12 = d15 output
  ra = MEM(GPIODBASE + 0x00);
  ra &= 0x00FFFFFF;
  ra |= 0x55000000;
  MEM(GPIODBASE + 0x00) = ra;
  //push pull
  ra = MEM(GPIODBASE + 0x04);
  ra &= 0xFFFF0FFF;
  MEM(GPIODBASE + 0x04) = ra;

  while(true) {
    MEM(GPIODBASE + 0x18) = 0xE0001000;
    wait(10);
//  MEM(GPIODBASE + 0x18) = 0xD0002000;
//  wait(4);
    MEM(GPIODBASE + 0x18) = 0xB0004000;
    wait(8);
//  MEM(GPIODBASE+0x18) = 0x70008000;
//  wait(4);
  }
}
