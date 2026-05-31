#include "emc_h755_gpio.h"
#include <stdint.h>

static EMC_GpioTypeDef_t *const gpio_ports[] = {
    EMC_GPIOA, EMC_GPIOB, EMC_GPIOC, EMC_GPIOD, EMC_GPIOE,
    EMC_GPIOF, EMC_GPIOG, EMC_GPIOI, EMC_GPIOJ, EMC_GPIOK};
