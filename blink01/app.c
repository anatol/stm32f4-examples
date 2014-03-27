#include <stdint.h>
#include <stdbool.h>

// base address for
// see reference manual section 2.3
#define RCCBASE   0x40023800
// base address for GPIO D
// see reference manual section 2.3
#define GPIODBASE 0x40020C00

#define MEM(address) (*(volatile uint32_t *)(address))

void wait(int period) {
  for (int i = 0; i < 50000 * period; i++) {
    __asm("nop");
  }
}

void application() {
  uint32_t ra;

  // enable GPIO port D
  // see refernce manual section 7.3.10
  MEM(RCCBASE + 0x30) |= (1 << 3);

  // configure pins D12-D15 to be general purpose
  // see reference manual 8.4.1
  ra = MEM(GPIODBASE + 0x00);
  ra &= 0x00FFFFFF;
  ra |= 0x55000000;
  MEM(GPIODBASE + 0x00) = ra;

  // configure pins D12-D15 to be push-pull
  // see reference manual 8.4.2
  ra = MEM(GPIODBASE + 0x04);
  ra &= 0xFFFF0FFF;
  MEM(GPIODBASE + 0x04) = ra;

  while(true) {
    // disable D13-15 and enable D15
    // see reference manual 8.4.7
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
