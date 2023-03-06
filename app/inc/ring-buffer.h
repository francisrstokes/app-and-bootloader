#ifndef INC_RING_BUFFER_H
#define INC_RING_BUFFER_H

#include "common-defines.h"
#include <libopencm3/cm3/sync.h>

typedef struct RingBuffer_t {
  uint8_t* buffer;
  uint32_t mask;
  volatile uint32_t read_index;
  volatile uint32_t write_index;
} RingBuffer_t;

void ring_buffer_init(RingBuffer_t* rb, uint8_t* buffer, uint32_t size);
bool ring_buffer_empty(RingBuffer_t* rb);
bool ring_buffer_read(RingBuffer_t* rb, uint8_t* byte_out);
bool ring_buffer_write(RingBuffer_t* rb, uint8_t value);

#endif // INC_RING_BUFFER_H
