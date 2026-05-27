#include "emc_h755_gpio.h"
#include <stdint.h>

static EMC_GPIO_TypeDef *const gpio_ports[] = {
    GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOI, GPIOJ, GPIOK};
