#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/typint.h"
#include "../include/vgat.h"

void kernel_main() {
  clear();
  init_gdt();
  idt_init();

  // Test interrupts
  asm volatile("int $0x3");
  asm volatile("int $0x4");
  putstr("Kernel of Khazar\n");
}
