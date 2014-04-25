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
