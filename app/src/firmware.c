#include <libopencm3/stm32/rcc.h>

#include "api-system.h"
#include "api-io.h"

#define GPIO_AF_TIM2_CH1 (GPIO_AF1)

static void rcc_setup(void) {
  rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);

  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOC);
  rcc_periph_clock_enable(RCC_TIM2);
}

static void gpio_setup(void)
{
  // Setup the LED
  gpio_mode_setup(LEDPort, GPIO_MODE_AF, GPIO_PUPD_NONE, LEDPin);
  gpio_set_af(LEDPort, GPIO_AF_TIM2_CH1, LEDPin);
  gpio_set_output_options(LEDPort, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, LEDPin);

  // Setup the button
  gpio_mode_setup(BtnInPort, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BtnInPin);
}

static void timer_setup(void) {
  // Basic initalisation
  timer_set_prescaler(TIM2, 0);
  timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
  timer_set_period(TIM2, 83999); // ~1kHz
  timer_enable_preload(TIM2);
  timer_generate_event(TIM2, TIM_EGR_UG);

  // Init PWM
  timer_set_master_mode(TIM2, 0);
  timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);
  timer_enable_oc_preload(TIM2, TIM_OC1);
  timer_set_oc_value(TIM2, TIM_OC1, 42000);
  timer_set_oc_fast_mode(TIM2, TIM_OC1);
}

int main(void)
{
  system_setup();

  rcc_setup();
  gpio_setup();
  timer_setup();

  timer_enable_counter(TIM2);
  timer_enable_oc_output(TIM2, TIM_OC1);
  timer_enable_oc_preload(TIM2, TIM_OC1);

  uint8_t Duty = 50;

  while (1) {
    if (io_btn_pressed()) {
      Duty = io_set_led_duty(Duty + 5);
      system_delay(100);
    }
  }

  return 0;
}
