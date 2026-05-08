#include "../../include/pit/pit.h"
#include "../../include/isr.h"
#include "../../include/typint.h"
#include "../../include/vga.h"

uint32_t volatile tick = 0;
uint32_t timer_frequency = 0;

static void timer_callback(registers_t *regs) { tick++; }

void init_timer(uint32_t frequency) {
  timer_frequency = frequency;
  register_interrupt_handler(IRQ0, &timer_callback);

  uint32_t divisor = 1193180 / frequency;

  byte_o(0x43, 0x36);

  uint8_t l = (uint8_t)(divisor & 0xFF);
  uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);
  byte_o(0x40, l);
  byte_o(0x40, h);
}

void sleep(uint32_t ms) {
  uint32_t start_tick = tick;
  uint32_t ticks_to_wait = (ms * timer_frequency) / 1000;
  while (tick - start_tick < ticks_to_wait)
    ;
}
