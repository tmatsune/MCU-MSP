#include "assert_handler.h"

#define ASSERT(expression)                                                     \
  do {                                                                         \
    if (!(expression)) {                                                       \
      assert_handler();                                                        \
    }                                                                          \
  } while (0)

void assert_handler(void){};
