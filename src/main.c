#include "common/defines.h"
#include "drivers/mcu_init.h"
#include "drivers/isr.h"
#include <msp430.h>
#include <stdint.h>

__attribute__((interrupt(PORT1_VECTOR))) void Port_1(void) {
  volatile unsigned int pin;

  for (pin = 0; pin < PIN_COUNT; pin++) {
    uint8_t mask = (1 << pin);
    if (P1IFG & mask) {
      if (isr_functions[pin])
        isr_functions[pin]();
      P1IFG &= ~mask;
    }
  }
}

void pin_setup(void) {
  P1DIR |= BIT1;
  P1OUT &= ~BIT1;
}

int main(void) {
  mcu_init();
  pin_setup();
  isr_setup();

  while(1);
}
