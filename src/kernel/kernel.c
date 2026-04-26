#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/keybrd/keybrd.h"
#include "../include/typint.h"
#include "../include/vga.h"

void kernel_main() {
  clear();
  init_gdt();
  putstr("[ INFO ] GDT Initialized\n");
  idt_init();
  putstr("[ INFO ] IDT Initialized\n");
  asm volatile("sti");
  putstr("[ INFO ]  Installing ISRs\n");
  putstr("[ INFO ] Initializing Keyboard (IRQ1)\n");
  init_keyboard();
  putstr("Kernel of Khazar");
  while (1)
    ;
}
