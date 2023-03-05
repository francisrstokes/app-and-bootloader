#ifndef INC_API_UART_H
#define INC_API_UART_H

#include "common-defines.h"

void uart_setup(void);
void uart_send_string(const char* str_data, uint32_t size);

#endif // INC_API_UART_H
