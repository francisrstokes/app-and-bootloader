#include "api-gpio.h"
#include "pins.h"

void gpio_setup(void)
{
  // Setup the LED
  gpio_mode_setup(LEDPort, GPIO_MODE_AF, GPIO_PUPD_NONE, LEDPin);
  gpio_set_af(LEDPort, GPIO_AF_TIM2_CH1, LEDPin);
  gpio_set_output_options(LEDPort, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LEDPin);

  // Setup the button
  gpio_mode_setup(BtnInPort, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BtnInPin);

  // Setup UART Tx and Rx
  gpio_mode_setup(UartPort, GPIO_MODE_AF, GPIO_PUPD_PULLUP, UartTxPin | UartRxPin);
  gpio_set_output_options(UartPort, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, UartTxPin | UartRxPin);
  gpio_set_af(UartPort, GPIO_AF_UART, UartTxPin | UartRxPin);
}

bool gpio_btn_pressed(void) {
  return (gpio_port_read(BtnInPort) & BtnInPin) == 0;
}

uint8_t gpio_set_led_duty(uint8_t Percent) {
  const uint32_t MaxDutyValue = 83999;
  if (Percent > 100) {
    Percent = 0;
  }
  uint32_t NewDuty = (MaxDutyValue / 100) * Percent;
  timer_set_oc_value(TIM2, TIM_OC1, NewDuty);
  return Percent;
}
