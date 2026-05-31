#ifndef EMC_H755_GPIO_H
#define EMC_H755_GPIO_H

#include "emc_error.h"
#include <stddef.h>
#include <stdint.h>

typedef enum {
  EMC_PORT_A = 0,
  EMC_PORT_B,
  EMC_PORT_C,
  EMC_PORT_D,
  EMC_PORT_E,
  EMC_PORT_F,
  EMC_PORT_G,
  EMC_PORT_H,
  EMC_PORT_I,
  EMC_PORT_J,
  EMC_PORT_K
} EMC_GpioPort_t;

typedef enum {
  EMC_GPIO_PIN0 = 0,
  EMC_GPIO_PIN1,
  EMC_GPIO_PIN2,
  EMC_GPIO_PIN3,
  EMC_GPIO_PIN4,
  EMC_GPIO_PIN5,
  EMC_GPIO_PIN6,
  EMC_GPIO_PIN7,
  EMC_GPIO_PIN8,
  EMC_GPIO_PIN9,
  EMC_GPIO_PIN10,
  EMC_GPIO_PIN11,
  EMC_GPIO_PIN12,
  EMC_GPIO_PIN13,
  EMC_GPIO_PIN14,
  EMC_GPIO_PIN15,
} EMC_GpioPin_t;

typedef enum {
  EMC_AF0 = 0,
  EMC_AF1,
  EMC_AF2,
  EMC_AF3,
  EMC_AF4,
  EMC_AF5,
  EMC_AF6,
  EMC_AF7,
  EMC_AF8,
  EMC_AF9,
  EMC_AF10,
  EMC_AF11,
  EMC_AF12,
  EMC_AF13,
  EMC_AF14,
  EMC_AF15,
} EMC_GpioAltFunc_t;

typedef enum {
  EMC_GPIO_MODE_INPUT = 0,
  EMC_GPIO_MODE_OUTPUT,
  EMC_GPIO_MODE_ALTERNATE,
  EMC_GPIO_MODE_ANALOG
} EMC_GpioMode_t;

typedef enum {
  EMC_GPIO_OTYPE_PUSH_PULL = 0,
  EMC_GPIO_OTYPE_OPEN_DRAIN,
} EMC_GpioOutputType_t;

typedef enum {
  EMC_GPIO_SPEED_LOW = 0,
  EMC_GPIO_SPEED_MEDIUM,
  EMC_GPIO_SPEED_HIGH,
  EMC_GPIO_SPEED_VERY_HIGH
} EMC_GpioSpeed_t;

typedef enum {
  GPIO_NO_PULL_UP_DOWN = 0,
  GPIO_PULL_UP,
  GPIO_PULL_DOWN,
  GPIO_RESERVED
} EMC_GpioResistor_t;

typedef enum { EMC_GPIO_LOW = 0, EMC_GPIO_HIGH } EMC_GpioState_t;

typedef struct {
  EMC_GpioPort_t port;
  EMC_GpioPin_t pin;
  EMC_GpioMode_t mode;
  EMC_GpioState_t init_state;
  EMC_GpioResistor_t resistor;
  EMC_GpioOutputType_t output_type;
  EMC_GpioSpeed_t speed;
  EMC_GpioAltFunc_t alt_func;
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
} EMC_GpioTypeDef_t;

#ifdef TEST_ENVIRONMENT

extern h7_gpio_reg Virtual_GPIOA;
extern h7_gpio_reg Virtual_GPIOB;
extern h7_gpio_reg Virtual_GPIOC;

#define GPIOA (&Virtual_GPIOA)
#define GPIOB (&Virtual_GPIOB)
#define GPIOC (&Virtual_GPIOC)

#else

#define EMC_GPIOA ((EMC_GpioTypeDef_t *)(uintptr_t)0x58020000)
#define EMC_GPIOB ((EMC_GpioTypeDef_t *)(uintptr_t)0x58020400)
#define EMC_GPIOC ((EMC_GpioTypeDef_t *)(uintptr_t)0x58020800)
#define EMC_GPIOD ((EMC_GpioTypeDef_t *)(uintptr_t)0x58020C00)
#define EMC_GPIOE ((EMC_GpioTypeDef_t *)(uintptr_t)0x58021000)
#define EMC_GPIOF ((EMC_GpioTypeDef_t *)(uintptr_t)0x58021400)
#define EMC_GPIOG ((EMC_GpioTypeDef_t *)(uintptr_t)0x58021800)
#define EMC_GPIOH ((EMC_GpioTypeDef_t *)(uintptr_t)0x58021C00)
#define EMC_GPIOI ((EMC_GpioTypeDef_t *)(uintptr_t)0x58022000)
#define EMC_GPIOJ ((EMC_GpioTypeDef_t *)(uintptr_t)0x58022400)
#define EMC_GPIOK ((EMC_GpioTypeDef_t *)(uintptr_t)0x58022800)

#endif

emc_error_t emc_gpio_init(const EMC_GpioConfig_t *const config);

emc_error_t emc_write_gpio(const EMC_GpioPort_t, EMC_GpioPin_t,
                           EMC_GpioState_t);

emc_error_t emc_read_gpio(const EMC_GpioPort_t, EMC_GpioPin_t, uint16_t *state);

emc_error_t emc_toggle_gpio(const EMC_GpioPort_t, const EMC_GpioPin_t);

emc_error_t emc_register_write_gpio_ioctl(uint32_t adress, uint32_t value);

emc_error_t emc_register_read_gpio_ioctl(uint32_t adress);

#endif
