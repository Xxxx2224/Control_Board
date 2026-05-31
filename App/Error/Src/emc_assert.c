#include "emc_assert.h"
#include "cmsis_gcc.h"
#include <stdint.h>
#include <stdio.h>

typedef struct {
  const char *file;
  const uint32_t line;
  const char *func;
  const char *parametr;
} EMC_FaultHandler_t;

void emc_fault_handler(const char *file, const uint32_t line, const char *func,
                       const char *parametr) {
  __disable_irq();

  printf("EMC_ASSERT");
  printf("Parametr: %s/n", parametr);
  printf("Function: %s()/n", func);
  printf("File: %s/n", file);
  printf("Line: %d/n", line);

  while (1) {
  };
}
