#include "api-uart.h"
#include "api-gpio.h"

#include <libopencm3/stm32/usart.h>

void uart_setup(void) {
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
  usart_set_baudrate(USART2, 115200);
  usart_set_databits(USART2, 8);
  usart_set_mode(USART2, USART_MODE_TX_RX);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_stopbits(USART2, 1);

  usart_enable_rx_interrupt(USART2);

  usart_enable(USART2);
}

void uart_send_string(const char* str_data, uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    usart_send_blocking(USART2, (uint16_t)str_data[i]);
  }
}
