#include "api-system.h"

#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/cm3/scb.h>

static const uint32_t cpu_freq = 84000000;
static volatile uint64_t ticks = 0;

// Extremely simple systick implementation
void sys_tick_handler(void) {
  ticks++;
}

void system_setup(void) {
  // Configure instruction and data caching
  flash_icache_enable();
  flash_dcache_enable();
  flash_prefetch_enable();

  // Set the vector table offset register
  SCB_VTOR = 0x8000;

  // Setup the systick timer
  systick_set_frequency(1000, cpu_freq);
  systick_counter_enable();
  systick_interrupt_enable();
}

void system_delay(uint32_t ms) {
  const volatile uint64_t target_ticks = ticks + (uint64_t)ms;
  while (target_ticks > ticks) { /* Spin */ }
}
