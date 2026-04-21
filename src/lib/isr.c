#include "../include/typint.h"
#include "../include/vgat.h"

typedef struct {
  uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rbp, rdi, rsi, rdx, rcx, rbx, rax;
  uint64_t int_no, err_code;
  uint64_t rip, cs, rflags, rsp, ss;
} registers_t;

void isr_handler(registers_t *regs) {
  putstr("Exception: ");
  puthex(regs->int_no);
  putstr("\n");
}
