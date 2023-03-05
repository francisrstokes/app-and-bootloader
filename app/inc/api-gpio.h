#ifndef INC_API_GPIO_H
#define INC_API_GPIO_H

#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/gpio.h>

#define GPIO_AF_TIM2_CH1 (GPIO_AF1)
#define GPIO_AF_UART     (GPIO_AF7)

void gpio_setup(void);
bool gpio_btn_pressed(void);
uint8_t gpio_set_led_duty(uint8_t Percent);

#endif // INC_API_IO_H
