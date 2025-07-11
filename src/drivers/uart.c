#include "uart.h"
#include <msp430.h>
#include <stdint.h>

void uart_init(void)
{
  // Hold USCI in reset during config
  UCA0CTL1 |= UCSWRST;

  // Use SMCLK (16 MHz)
  UCA0CTL1 |= UCSSEL_2;

  // Configure TXD/RXD pins (P1.1 = RX, P1.2 = TX)
  P1SEL |= BIT1 | BIT2;
  P1SEL2 |= BIT1 | BIT2;

  // For 16 MHz and 9600 baud:
  // BR = 1667 (0x0683), modulation = UCBRS_0 + UCBRF_0 + UCOS16 = 0
  UCA0BR0 = 0x83;     // low byte = 131
  UCA0BR1 = 0x06;     // high byte = 6
  UCA0MCTL = UCBRS_0; // No modulation

  // Enable USCI
  UCA0CTL1 &= ~UCSWRST;
}

void uart_putchar_pulling(char c)
{
  while (!(IFG2 & UCA0TXIFG));
  UCA0TXBUF = c;

  if (c == '\n') {
    while (!(IFG2 & UCA0TXIFG));
    UCA0TXBUF = '\r';
  }
}

