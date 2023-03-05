#ifndef INC_PINS_H
#define INC_PINS_H

#include <libopencm3/stm32/gpio.h>

#define LEDPort    (GPIOA)
#define LEDPin     (GPIO5)

#define BtnInPort  (GPIOC)
#define BtnInPin   (GPIO13)

#define UartPort   (GPIOA)
#define UartTxPin  (GPIO2)
#define UartRxPin  (GPIO3)

#endif // INC_PINS_H
