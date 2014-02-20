#include <stdint.h>
#include <stdbool.h>

#define RCCBASE   0x40023800
#define GPIODBASE 0x40020C00

#define MEM(address) (*(volatile uint32_t *)(address))

void wait(int period) {
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
