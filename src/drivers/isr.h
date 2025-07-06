
#ifndef ISR_TABLE_H
#define ISR_TABLE_H

#include <stdint.h>
#include <stddef.h>
#include "common/defines.h"

typedef void (*isr_function)(void);
extern isr_function isr_functions[PIN_COUNT];

void isr_setup(void);

#endif
