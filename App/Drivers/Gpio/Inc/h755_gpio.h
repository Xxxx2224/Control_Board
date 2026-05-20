#ifndef EMC_H755_GPIO_H
#define EMC_H755_GPIO_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
  PORT_A = 0,
  PORT_B,
  PORT_C,
  PORT_D,
  PORT_E,
  PORT_F,
  PORT_G,
  PORT_H,
  PORT_I,
  PORT_J,
  PORT_K
} gpio_port_t;

typedef struct {

  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFRL;
  volatile uint32_t AFRH;

} h7_gpio_reg;

#ifdef TEST_ENVIRONMENT

extern h7_gpio_reg Virtual_GPIOA;
extern h7_gpio_reg Virtual_GPIOB;
extern h7_gpio_reg Virtual_GPIOC;

#define GPIOA (&Virtual_GPIOA)
#define GPIOB (&Virtual_GPIOB)
#define GPIOC (&Virtual_GPIOC)

#else

#define GPIOA ((h7_gpio_reg *)(uintptr_t)0x58020000)
#define GPIOB ((h7_gpio_reg *)(uintptr_t)0x58020400)
#define GPIOC ((h7_gpio_reg *)(uintptr_t)0x58020800)
#define GPIOD ((h7_gpio_reg *)(uintptr_t)0x58020C00)
#define GPIOE ((h7_gpio_reg *)(uintptr_t)0x58021000)
#define GPIOF ((h7_gpio_reg *)(uintptr_t)0x58021400)
#define GPIOG ((h7_gpio_reg *)(uintptr_t)0x58021800)
#define GPIOH ((h7_gpio_reg *)(uintptr_t)0x58021C00)
#define GPIOI ((h7_gpio_reg *)(uintptr_t)0x58022000)
#define GPIOJ ((h7_gpio_reg *)(uintptr_t)0x58022400)
#define GPIOK ((h7_gpio_reg *)(uintptr_t)0x58022800)
#endif

#endif
