#ifndef EMC_H755_GPIO_H
#define EMC_H755_GPIO_H

#include "emc_error.h"
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
} EMC_GpioPort_t;

typedef enum {
  GPIO_PIN0 = 0,
  GPIO_PIN1,
  GPIO_PIN2,
  GPIO_PIN3,
  GPIO_PIN4,
  GPIO_PIN5,
  GPIO_PIN6,
  GPIO_PIN7,
  GPIO_PIN8,
  GPIO_PIN9,
  GPIO_PIN10,
  GPIO_PIN11,
  GPIO_PIN12,
  GPIO_PIN13,
  GPIO_PIN14,
  GPIO_PIN15,
} EMC_GpioPinNumbers_t;

typedef enum {
  AF0 = 0,
  AF1,
  AF2,
  AF3,
  AF4,
  AF5,
  AF6,
  AF7,
  AF8,
  AF9,
  AF10,
  AF11,
  AF12,
  AF13,
  AF14,
  AF15,
} EMC_GpioAlternateFunction_t;

typedef enum {
  GPIO_MODE_INPUT = 0,
  GPIO_MODE_OUTPUT,
  GPIO_MODE_ALTERNATE,
  GPIO_MODE_ANALOG
} EMC_GpioMode_t;

typedef enum {
  GPIO_PUSH_PULL = 0,
  GPIO_OPEN_DRAIN,
} EMC_GpioOutputType_t;

typedef enum {
  GPIO_LOW_SPEED = 0,
  GPIO_MEDIUM_SPEED,
  GPIO_HIGH_SPEED,
  GPIO_VHIGH_SPEED
} EMC_GpioSpeed_t;

typedef enum {
  GPIO_NO_PULL_UP_DOWN = 0,
  GPIO_PULL_UP,
  GPIO_PULL_DOWN,
  GPIO_RESERVED
} EMC_GpioResistor_t;

typedef enum { GPIO_PIN_LOW = 0, GPIO_PIN_HIGH } EMC_GpioState;

typedef struct {
  EMC_GpioPort_t port;
  EMC_GpioPinNumbers_t pin;
  EMC_GpioMode_t mode;
  EMC_GpioState initstate;
  EMC_GpioResistor_t resistor;
  EMC_GpioOutputType_t output_type;
  EMC_GpioSpeed_t speed;
  EMC_GpioAlternateFunction_t a_f;
} EMC_GpioConfig_t;

typedef struct {

  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint16_t BSRRSET;
  volatile uint16_t BSRRRESET;
  volatile uint32_t LCKR;
  volatile uint32_t AFRL;
  volatile uint32_t AFRH;

} EMC_GPIO_TypeDef;

#ifdef TEST_ENVIRONMENT

extern h7_gpio_reg Virtual_GPIOA;
extern h7_gpio_reg Virtual_GPIOB;
extern h7_gpio_reg Virtual_GPIOC;

#define GPIOA (&Virtual_GPIOA)
#define GPIOB (&Virtual_GPIOB)
#define GPIOC (&Virtual_GPIOC)

#else

#define GPIOA ((EMC_GPIO_TypeDef *)(uintptr_t)0x58020000)
#define GPIOB ((EMC_GPIO_TypeDef *)(uintptr_t)0x58020400)
#define GPIOC ((EMC_GPIO_TypeDef *)(uintptr_t)0x58020800)
#define GPIOD ((EMC_GPIO_TypeDef *)(uintptr_t)0x58020C00)
#define GPIOE ((EMC_GPIO_TypeDef *)(uintptr_t)0x58021000)
#define GPIOF ((EMC_GPIO_TypeDef *)(uintptr_t)0x58021400)
#define GPIOG ((EMC_GPIO_TypeDef *)(uintptr_t)0x58021800)
#define GPIOH ((EMC_GPIO_TypeDef *)(uintptr_t)0x58021C00)
#define GPIOI ((EMC_GPIO_TypeDef *)(uintptr_t)0x58022000)
#define GPIOJ ((EMC_GPIO_TypeDef *)(uintptr_t)0x58022400)
#define GPIOK ((EMC_GPIO_TypeDef *)(uintptr_t)0x58022800)
#endif

emc_error_t emc_gpio_init(const EMC_GpioConfig_t *const config);

emc_error_t emc_write_gpio(const EMC_GpioPort_t, EMC_GpioPinNumbers_t,
                           EMC_GpioState);

emc_error_t emc_read_gpio(const EMC_GpioPort_t, EMC_GpioPinNumbers_t,
                          uint16_t *state);

emc_error_t emc_toggle_gpio(const EMC_GpioPort_t, const EMC_GpioPinNumbers_t);

emc_error_t emc_register_write_gpio_ioctl(uint32_t adress, uint32_t value);

emc_error_t emc_register_read_gpio_ioctl(uint32_t adress);

#endif
