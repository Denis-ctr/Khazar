#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/typint.h"
#include "../include/vgat.h"

void kernel_main() {
  clear();
  init_gdt();
  idt_init();
  putstr("Kernel of Khazar\n");
}
