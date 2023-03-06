#ifndef INC_API_UART_H
#define INC_API_UART_H

#include "common-defines.h"

void uart_setup(void);
void uart_send_string(const char* str_data, uint32_t size);
void uart_send_char(char c);
bool uart_bytes_available(void);
bool uart_read(uint8_t* byte_out);

#endif // INC_API_UART_H
