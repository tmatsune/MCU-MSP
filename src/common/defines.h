#ifndef DEFINES_H
#define DEFINES_H

#define UNUSED(x) (void)(x)
#define PIN_COUNT 8

#define CYCLES_1MHZ (1000000u) // million cycles per sec
#define CYCLES_16MHZ (16u * CYCLES_1MHZ) // 16 million cycles per sec
#define CYCLES_PER_MS (CYCLES_16MHZ / 1000u) // 16 million cycles per sec / 1000 

#define ms_TO_CYCLES(ms) (CYCLES_PER_MS * ms) 
#define DELAY_ms(ms) (__delay_cycles(ms_TO_CYCLES(ms)))

#define MCLK CYCLES_16MHZ
#define SMCLK MCLK

#endif
