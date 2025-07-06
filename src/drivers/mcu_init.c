#include "mcu_init.h"
#include <msp430.h>

void mcu_init(void) {
  WDTCTL = WDTPW + WDTHOLD;
  __enable_interrupt();
}
