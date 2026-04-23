#ifndef ISR_H
#define ISR_H

#include "typint.h"

typedef struct {
  uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rbp, rdi, rsi, rdx, rcx, rbx,
      rax;
  uint64_t int_no, err_code;
  uint64_t rip, cs, rflags, rsp, ss;
} registers_t;

typedef void (*isr_t)(registers_t *);

void isr_handler(registers_t *regs);
void irq_handler(registers_t *regs);

void register_interrupt_handler(uint8_t n, isr_t handler);

#endif
