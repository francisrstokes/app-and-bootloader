#include "ring-buffer.h"

// Note: size must be a power of 2
void ring_buffer_init(RingBuffer_t* rb, uint8_t* buffer, uint32_t size) {
  rb->buffer = buffer;
  rb->mask = size - 1;
  rb->read_index = 0;
  rb->write_index = 0;
}

bool ring_buffer_empty(RingBuffer_t* rb) {
  uint32_t local_read_index = rb->read_index;
  uint32_t local_write_index = rb->write_index;

  return local_read_index == local_write_index;
}

bool ring_buffer_read(RingBuffer_t* rb, uint8_t* byte_out) {
  uint32_t local_read_index = rb->read_index;
  uint32_t local_write_index = rb->write_index;

  if (local_read_index == local_write_index) {
    // No bytes available, cannot read
    return false;
  }

  *byte_out = rb->buffer[local_read_index];
  local_read_index = (local_read_index + 1) & rb->mask;

  rb->read_index = local_read_index;

  return true;
}

bool ring_buffer_write(RingBuffer_t* rb, uint8_t value) {
  uint32_t local_write_index = rb->write_index;
  uint32_t local_read_index = rb->read_index;
  uint32_t next_write_index = (local_write_index + 1) & rb->mask;

  if (next_write_index == local_read_index) {
    // Writing now would overrun the buffer. Arbitrarily choose to favour older data over new,
    // and drop the byte
    return false;
  }

  rb->buffer[local_write_index] = value;
  rb->write_index = next_write_index;

  return true;
}
