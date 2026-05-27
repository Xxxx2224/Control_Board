#ifndef EMC_H755_ISR_H
#define EMC_H755_ISR_H

#include <stdint.h>

typedef struct {
  volatile uint32_t RTSR1;
  volatile uint32_t FTSR1;
  volatile uint32_t SWIER1;
  volatile uint32_t D3PMR1;
  volatile uint32_t D3PCR1L;
  volatile uint32_t D3PCR1H;
  uint32_t RESERVED1[2];
  volatile uint32_t RTSR2;
  volatile uint32_t FTSR2;
  volatile uint32_t SWIER2;
  volatile uint32_t D3PMR2;
  volatile uint32_t D3PCR2L;
  volatile uint32_t D3PCR2H;
  uint32_t RESERVED2[2];
  volatile uint32_t RTSR3;
  volatile uint32_t FTSR3;
  volatile uint32_t SWIER3;
  volatile uint32_t D3PMR3;
  volatile uint32_t D3PCR3L;
  volatile uint32_t D3PCR3H;
  uint32_t RESERVED3[10];
  volatile uint32_t IMR1;
  volatile uint32_t EMR1;
  volatile uint32_t PR1;
  uint32_t RESERVED4;
  volatile uint32_t IMR2;
  volatile uint32_t EMR2;
  volatile uint32_t PR2;
  uint32_t RESERVED5;
  volatile uint32_t IMR3;
  volatile uint32_t EMR3;
  volatile uint32_t PR3;
  uint32_t RESERVED6[5];
  volatile uint32_t C2IMR1;
  volatile uint32_t C2EMR1;
  volatile uint32_t C2PR1;
  uint32_t RESERVED7;
  volatile uint32_t C2IMR2;
  volatile uint32_t C2EMR2;
  volatile uint32_t C2PR2;
  uint32_t RESERVED8;
  volatile uint32_t C2IMR3;
  volatile uint32_t C2EMR3;
  volatile uint32_t C2PR3;

} EMC_EXTI_TypeDef;

typedef struct {
  volatile uint32_t IMR1;
  volatile uint32_t EMR1;
  volatile uint32_t PR1;
  uint32_t RESERVED1;
  volatile uint32_t IMR2;
  volatile uint32_t EMR2;
  volatile uint32_t PR2;
  uint32_t RESERVED2;
  volatile uint32_t IMR3;
  volatile uint32_t EMR3;
  volatile uint32_t PR3;
} EMC_EXTI_Core_TypeDef;

#ifndef TEST_ENVIRONMENT

#define EXTI_BASE (0x58000000UL)
#define EXTI ((EMC_EXTI_TypeDef *)(uintptr_t)EXTI_BASE)
#define CPU1_EXTI ((EMC_EXTI_Core_TypeDef *)(uintptr_t)(EXTI_BASE + 0x80UL))
#define CPU2_EXTI ((EMC_EXTI_Core_TypeDef *)(uintptr_t)(EXTI_BASE + 0xC0UL))

#else

#define EXTI_BASE (0x58000000UL)
#define EXTI ((EMC_EXTI_TypeDef *)(uintptr_t)EXTI_BASE)
#define CPU1_EXTI ((EMC_EXTI_Core_TypeDef *)(uintptr_t)(EXTI_BASE + 0x80UL))
#define CPU2_EXTI ((EMC_EXTI_Core_TypeDef *)(uintptr_t)(EXTI_BASE + 0xC0UL))

#endif

#endif
