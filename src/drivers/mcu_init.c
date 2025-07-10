#include "mcu_init.h"
#include "drivers/uart.h"
#include <msp430.h>

static inline void init_clocks(void)
{
  BCSCTL1 = CALBC1_16MHZ; // config main clock to run at 16 MHz
  DCOCTL = CALDCO_16MHZ;  // sets clock rate of the DCO 
  BCSCTL3 = LFXT1S_2;
}

void mcu_init(void) {
  WDTCTL = WDTPW + WDTHOLD;
  init_clocks();
  __enable_interrupt();
}
