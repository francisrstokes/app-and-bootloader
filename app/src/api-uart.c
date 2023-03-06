#include "api-uart.h"
#include "api-gpio.h"
#include "ring-buffer.h"

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/usart.h>

#define UART_BUFFER_SIZE (128)
static uint8_t raw_buffer[UART_BUFFER_SIZE] = {0};
static RingBuffer_t uart_buffer = {0};

void usart2_isr(void) {
  bool byte_was_received = usart_get_flag(USART2, USART_FLAG_RXNE) == 1;
  bool overrun_occurred = usart_get_flag(USART2, USART_FLAG_ORE) == 1;

  // Did we receive a byte?
  if (byte_was_received || overrun_occurred) {
    uint8_t byte_received = usart_recv(USART2);

    // When we've received a byte, push it into the ring buffer
    if (!ring_buffer_write(&uart_buffer, byte_received)) {
      // The buffer was full, couldn't push the byte
    }
  }
}

void uart_setup(void) {
  nvic_enable_irq(NVIC_USART2_IRQ);

  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
  usart_set_baudrate(USART2, 115200);
  usart_set_databits(USART2, 8);
  usart_set_mode(USART2, USART_MODE_TX_RX);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_stopbits(USART2, 1);

  usart_enable(USART2);
  usart_enable_rx_interrupt(USART2);

  ring_buffer_init(&uart_buffer, raw_buffer, UART_BUFFER_SIZE);
}

void uart_send_string(const char* str_data, uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    usart_send_blocking(USART2, (uint16_t)str_data[i]);
  }
}

void uart_send_char(char c) {
  usart_send_blocking(USART2, (uint16_t)c);
}

bool uart_bytes_available(void) {
  return !ring_buffer_empty(&uart_buffer);
}

bool uart_read(uint8_t* byte_out) {
  return ring_buffer_read(&uart_buffer, byte_out);
}

