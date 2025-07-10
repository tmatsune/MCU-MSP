#include "common/defines.h"
#include "drivers/mcu_init.h"
#include "drivers/isr.h"
#include "drivers/uart.h"
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
  P1SEL |= BIT1 + BIT2;
  P1SEL2 |= BIT1 + BIT2;
}

int main(void) {

  mcu_init();
  pin_setup();
  uart_init();

  while(1) {
    uart_putchar_pulling('h');
    uart_putchar_pulling('e');
    uart_putchar_pulling('l');
    uart_putchar_pulling('l');
    uart_putchar_pulling('o');
    uart_putchar_pulling('\n');
    __delay_cycles(1000000);
  }

  return 0;
}
