#include "stm32_hal_legacy.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_rcc.h"

#include "emc_error.h"
#include "emc_h755_gpio.h"

#include <stdint.h>
#include <sys/types.h>

static EMC_GpioTypeDef_t *const gpio_ports[] = {
    EMC_GPIOA, EMC_GPIOB, EMC_GPIOC, EMC_GPIOD, EMC_GPIOE, EMC_GPIOF,
    EMC_GPIOG, EMC_GPIOG, EMC_GPIOI, EMC_GPIOJ, EMC_GPIOK};

void gpioledpe1(void) {
  EMC_GPIOE->MODER |= 1U << 2;
  EMC_GPIOE->MODER &= ~(1U << 3);
  EMC_GPIOE->OTYPER &= ~(1U << 1);
  EMC_GPIOE->OSPEEDR &= ~(3U << 2);
  EMC_GPIOE->PUPDR &= ~(3U << 2);
}

emc_error_t emc_gpio_init(EMC_GpioConfig_t *const config) {

  // < 0  gerek varmi daha sonra test edilecek muhtemelen derleyici U ile
  // karsilastirma yaptigimiz  icin unsigned olarak karsilastirma yapicak
  if (config->pin > 15U || config->pin < 0U) {
    return BAD_PARAMETER;
  }

  if (config->mode > 3U || config->mode < 0U) {
    return BAD_PARAMETER;
  }

  if (config->port > 11U || config->port < 0U) {
    return BAD_PARAMETER;
  }

  if (config->init_state == 1U) {
    return UNINITIALIZED;
  }

  if (config->init_state != 0U) {
    return BAD_PARAMETER;
  }

  if (config->resistor > 3U || config->resistor < 0U) {
    return BAD_PARAMETER;
  }

  if (config->speed > 3U || config->speed < 0U) {
    return BAD_PARAMETER;
  }

  if (config->output_type > 1U || config->output_type < 0U) {
    return BAD_PARAMETER;
  }

  if (config->alt_func > 15U || config->alt_func < 0U) {
  }

  switch (config->port) {

  case EMC_PORT_A:
    __HAL_RCC_GPIOA_CLK_ENABLE();
    break;

  case EMC_PORT_B:
    __HAL_RCC_GPIOB_CLK_ENABLE();
    break;

  case EMC_PORT_C:
    __HAL_RCC_GPIOC_CLK_ENABLE();
    break;

  case EMC_PORT_D:
    __HAL_RCC_GPIOD_CLK_ENABLE();
    break;

  case EMC_PORT_E:
    __HAL_RCC_GPIOE_CLK_ENABLE();
    break;

  case EMC_PORT_F:
    __HAL_RCC_GPIOF_CLK_ENABLE();
    break;

  case EMC_PORT_G:
    __HAL_RCC_GPIOG_CLK_ENABLE();
    break;

  case EMC_PORT_H:
    __HAL_RCC_GPIOH_CLK_ENABLE();
    break;

  case EMC_PORT_I:
    __HAL_RCC_GPIOI_CLK_ENABLE();
    break;

  case EMC_PORT_J:
    __HAL_RCC_GPIOJ_CLK_ENABLE();
    break;

  case EMC_PORT_K:
    __HAL_RCC_GPIOK_CLK_ENABLE();
    break;

  default:
    return UNKNOWN_ERROR;
    break;
  }

  uint32_t pin = config->pin;
  EMC_GpioTypeDef_t *GPIOx = gpio_ports[config->port];

  __disable_irq();

  GPIOx->MODER = (GPIOx->MODER & ~(3U << (2U * pin))) |
                 (((uint32_t)config->mode << (2U * pin)) & (3U << (2U * pin)));

  if (config->mode == 1U || config->mode == 2U) {

    GPIOx->OTYPER = (GPIOx->OTYPER & ~(1 << pin)) |
                    (((uint32_t)config->output_type << pin) & (1 << pin));
  }

  GPIOx->OSPEEDR =
      (GPIOx->OSPEEDR & ~(3U << (2U * pin))) |
      (((uint32_t)config->speed << (2U * pin)) & (3U << (2U * pin)));

  GPIOx->PUPDR =
      (GPIOx->PUPDR & ~(3U << (2U * pin))) |
      (((uint32_t)config->resistor << (2U * pin)) & (3U << (2U * pin)));

  if (config->mode == 2) {

    if (pin < 8) {

      GPIOx->AFRL =
          (GPIOx->AFRL & ~(15U << (4U * pin))) |
          (((uint32_t)config->alt_func << (4U * pin)) & (15U << (4U * pin)));
    } else if (pin < 16) {

      GPIOx->AFRH = (GPIOx->AFRH & ~(15U << (4U * (pin - 8)))) |
                    (((uint32_t)config->alt_func << (4U * (pin - 8))) &
                     (15U << (4U * (pin - 8))));
    }
  }

  config->init_state = 1;
  return NO_ERROR;
}

emc_error_t emc_write_gpio(const EMC_GpioPort_t port, const EMC_GpioPin_t pin,
                           const EMC_GpioState_t state) {

  if (state == 1U) {
    gpio_ports[port]->BSRRSET = 1U << pin;
  } else {
    gpio_ports[port]->BSRRRESET = 1U << pin;
  }

  return NO_ERROR;
}

emc_error_t emc_read_gpio(const EMC_GpioPort_t port, EMC_GpioPin_t pin,
                          EMC_GpioState_t *state) {
  __disable_irq();

  if ((gpio_ports[port]->IDR & (1U << (uint16_t)pin)) == 1U) {

    *state = EMC_GPIO_HIGH;

  } else {

    *state = EMC_GPIO_LOW;
  }
  __enable_irq();

  return NO_ERROR;
}

emc_error_t emc_toggle_gpio(const EMC_GpioPort_t port,
                            const EMC_GpioPin_t pin) {
  __disable_irq();
  gpio_ports[port]->ODR ^= 1U << pin;
  __enable_irq();

  return NO_ERROR;
};

emc_error_t emc_W_register_write_gpio_ioctl(uint32_t adress, uint32_t value) {

  __disable_irq();
  *(volatile uint32_t *)(uintptr_t)adress = value;
  __enable_irq();

  return NO_ERROR;
}

emc_error_t emc_RW_register_write_gpio_ioctl(uint32_t adress, uint32_t value,
                                             uint8_t bit_start,
                                             uint8_t bit_width) {
  __disable_irq();

  uint32_t mask = (1U << bit_width) - 1;
  uint32_t clean_value = value & mask;

  *(volatile uint32_t *)(uintptr_t)adress &= ~(mask << bit_start);
  *(volatile uint32_t *)(uintptr_t)adress |= clean_value << bit_start;
  __enable_irq();

  return NO_ERROR;
}

emc_error_t emc_register_read_gpio_ioctl(uint32_t adress, uint32_t *data,
                                         uint32_t bit_start,
                                         uint32_t bit_width) {
  uint32_t mask = (1U << bit_width) - 1;
  *data = *(volatile uint32_t *)(uintptr_t)adress & (~(mask << bit_start));

  return NO_ERROR;
}
