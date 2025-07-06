#include "isr.h"
#include <msp430.h>
#include <stdint.h>



void isr_setup(void){
  for (int pin = 2; pin <= 4; pin++) {
    uint8_t mask = (1 << pin);
    P1DIR &= ~mask;
    P1REN |= mask;
    P1OUT |= mask;
    P1IE  |= mask;
    P1IES |= mask;
    P1IFG &= ~mask;
  }
}

static inline void toggle_led(int amnt){
    for (int i = 0; i < amnt; i++) {
        P1OUT ^= BIT1;
        __delay_cycles(100000);
    }
    P1OUT &= ~BIT1;
} 

static inline void handle_p1_2(void) { toggle_led(3); }
static inline void handle_p1_3(void) { toggle_led(8); }
static inline void handle_p1_4(void) { toggle_led(16); }

isr_function isr_functions[PIN_COUNT] = {
    NULL, NULL, handle_p1_2, handle_p1_3, handle_p1_4, NULL, NULL, NULL
};
