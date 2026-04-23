/*Interrupt Handler (və ya digər adı ilə ISR - Interrupt Service Routine),
  prosessorun (CPU) gördüyü işi müvəqqəti dayandıraraq,
 təcili baş vermiş bir hadisəyə cavab verməsini təmin edən xüsusi funksiyadır.
 */

#include "../include/io.h"
#include "../include/typint.h"
#include "../include/vga.h"

typedef struct {
  uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rbp, rdi, rsi, rdx, rcx, rbx,
      rax;
  uint64_t int_no, err_code;
  uint64_t rip, cs, rflags, rsp, ss;
} registers_t;

typedef void (*isr_t)(registers_t *);

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}

void isr_handler(registers_t *regs) {
  putstr("Exception: ");
  puthex(regs->int_no);
  putstr("\n");
}

void irq_handler(registers_t *regs) {
  // EOI signali
  if (regs->int_no >= 40) {

    byte_o(0xA0, 0x20);
  }
  // full master
  byte_o(0x20, 0x20);

  // kesme ucun isleyici varsa call edir
  if (interrupt_handlers[regs->int_no] != 0) {
    isr_t handler = interrupt_handlers[regs->int_no];
    handler(regs);
  }
}
