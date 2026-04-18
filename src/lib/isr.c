#include "../include/isr.h"
#include "../include/typint.h"
#include "../include/vgat.h"

typedef struct {
  uint64_t ds;
  uint64_t rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;
  uint64_t int_no, err_code;
  uint64_t rip, cs, rflags, userrsp, ss;
} registers_t;

void isr_handler(registers_t regs) { (void)regs; }
