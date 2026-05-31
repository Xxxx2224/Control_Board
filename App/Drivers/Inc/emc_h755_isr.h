#ifndef EMC_H755_ISR_H
#define EMC_H755_ISR_H

#include <stdint.h>
#include <sys/types.h>

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

typedef enum {
  EMC_EXTI_RISING_OFF = 0,
  EMC_EXTI_RISING_ON
} EMC_ExtiRisingEdge_t;

typedef enum {
  EMC_EXTI_FALLING_OFF = 0,
  EMC_EXTI_FALLING_ON
} EMC_ExtiFallingEdge_t;

typedef enum { EMC_EXTI_SWTRIG_ACTIVE = 1 } EMC_ExtiSoftwareTrigger_t;

typedef enum {
  EMC_EXTI_D3PEND_MASKED = 0,
  EMC_EXTI_D3PEND_UNMASKED
} EMC_ExtiD3PendingMask_t;

typedef enum {
  EMC_EXTI_PCLR_DMA_CH6 = 0,
  EMC_EXTI_PCLR_DMA_CH7,
  EMC_EXTI_PCLR_LPTIM4,
  EMC_EXTI_PCLR_LPTIM5
} EMC_ExtiPendingClear_t;

typedef enum {
  EMC_EXTI_INT_MASKED = 0,
  EMC_EXTI_INT_UNMASKED
} EMC_ExtiInterruptMask_t;

typedef enum {
  EMC_EXTI_EVT_MASKED = 0,
  EMC_EXTI_EVT_UNMASKED
} EMC_ExtiEventMask_t;

typedef enum {
  EMC_EXTI_FLAG_RESET = 0,
  EMC_EXTI_FLAG_SET
} EMC_ExtiPendingFlag_t;

typedef struct {
  uint16_t channel;
  EMC_ExtiRisingEdge_t rising;
  EMC_ExtiFallingEdge_t falling;
  EMC_ExtiD3PendingMask_t d3_pending_mask;
  EMC_ExtiPendingClear_t d3_pending_clear;
  EMC_ExtiInterruptMask_t int_mask;
  EMC_ExtiEventMask_t event_mask;
} EMC_ExtiConfig_t;

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
