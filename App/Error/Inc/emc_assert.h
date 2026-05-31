#ifndef EMC_ASSERT_H
#define EMC_ASSERT_H
#include <stdint.h>

void emc_fault_handler(const char *file, const uint32_t line, const char *func,
                       const char *parametr);
#ifdef DEBUG
#define emc_assert(parametr)                                                   \
  do {                                                                         \
    if (!(parametr)) {                                                         \
      emc_fault_handler(__FILE__, __LINE__, __func__, #parametr);              \
    }                                                                          \
  } while (0)

#else

#define emc_assert(parametr)                                                   \
  do {                                                                         \
    if (!(parametr)) {                                                         \
      __builtin_unreachable();                                                 \
    }                                                                          \
  } while (0)
#endif

#endif
