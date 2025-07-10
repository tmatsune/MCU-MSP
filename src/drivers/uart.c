#include "uart.h"
#include "common/defines.h"
#include <msp430.h>
#include <assert.h> 
#include <stdint.h> 
#include <stddef.h>

#define UART_BUFFER_SIZE (16u)
// Configuring the UART hardware registers
#define BRCLK (SMCLK) // system clock 16MHz
#define UART_BAUD_RATE (115200u) // Baud rate 
static_assert(UART_BAUD_RATE < (BRCLK / 3.0f), "Baudrate must be smaller than 1/3 of input clock in Low-Frequency Mode");
// MSP430 need clock divisor how much to divide SMCLK to get right baud rate
#define UART_DIVISOR ((float)BRCLK / UART_BAUD_RATE) //  (e.g. 16MHz / 115200) ~138.888
static_assert(UART_DIVISOR < 0xFFFFu, "Sanity check divisor fits in 16-bit");
#define UART_DIVISOR_INT_16BIT ((uint16_t)UART_DIVISOR)
#define UART_DIVISOR_INT_LOW_BYTE (UART_DIVISOR_INT_16BIT & 0xFF)
#define UART_DIVISOR_INT_HIGH_BYTE (UART_DIVISOR_INT_16BIT >> 8)
#define UART_DIVISOR_FRACTIONAL (UART_DIVISOR - UART_DIVISOR_INT_16BIT)
#define UART_UCBRS ((uint8_t)(8 * UART_DIVISOR_FRACTIONAL))
#define UART_UCBRF (0)
#define UART_UC0S16 (0)
static_assert(UART_UCBRS < 8, "Sanity check second modulation stage value fits in 3-bit");

void uart_init(void)
{
  /* Reset module. It stays in reset until cleared. The module should be in reset
  * condition while configured according to the user guide (SLAU144K). */
  UCA0CTL1 |= UCSWRST;

  /* Use default (data word length 8 bits, 1 stop bit, no parity bit)
  * [ Start (1 bit) | Data (8 bits) | Stop (1 bit) ] */
  UCA0CTL0 = 0;

  // Set SMCLK as clock source.
  UCA0CTL1 |= UCSSEL_2;

  // Set clock prescaler to the integer part of divisor N.
  UCA0BR0 = UART_DIVISOR_INT_LOW_BYTE;
  UCA0BR1 = UART_DIVISOR_INT_HIGH_BYTE;

  /* Set modulation to account for the fractional part of divisor N.
  * UCA0MCTL = [UCBRF (4 bits) | UCBRS (3 bits) | UC0S16 (1 bit) ] */
  UCA0MCTL = (UART_UCBRF << 4) + (UART_UCBRS << 1) + UART_UC0S16;

  // Clear reset to release the module for operation.
  UCA0CTL1 &= ~UCSWRST;
};

void uart_putchar_pulling(char c)
{
  while(!(IFG2 & UCA0TXIFG));
  UCA0TXBUF = c;

  if (c == '\n'){
    uart_putchar_pulling('\r');
  } 
}



