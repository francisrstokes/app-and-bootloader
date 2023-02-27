#include "api-io.h"

bool io_btn_pressed(void) {
	return (gpio_port_read(BtnInPort) & BtnInPin) == 0;
}

uint8_t io_set_led_duty(uint8_t Percent) {
	const uint32_t MaxDutyValue = 83999;
	if (Percent > 100) {
		Percent = 0;
	}
	uint32_t NewDuty = (MaxDutyValue / 100) * Percent;
	timer_set_oc_value(TIM2, TIM_OC1, NewDuty);
	return Percent;
}
