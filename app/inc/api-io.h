#ifndef INC_API_IO_H
#define INC_API_IO_H

#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/gpio.h>

#define LEDPort (GPIOA)
#define LEDPin  (GPIO5)

#define BtnInPort (GPIOC)
#define BtnInPin  (GPIO13)

bool io_btn_pressed(void);
uint8_t io_set_led_duty(uint8_t Percent);

#endif // INC_API_IO_H
