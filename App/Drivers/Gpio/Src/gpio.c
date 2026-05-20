#include "h755_gpio.h"
#include <stdint.h>

static h7_gpio_reg *const gpio_ports[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE,
                                          GPIOF, GPIOG, GPIOI, GPIOJ, GPIOK};
