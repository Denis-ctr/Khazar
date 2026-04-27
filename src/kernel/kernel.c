#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/keybrd/keybrd.h"
#include "../include/pit/pit.h"
#include "../include/typint.h"
#include "../include/vga.h"

void kernel_main() {
  clear();
  init_gdt();
  idt_init();
  init_keyboard();
  init_timer(100);
  asm volatile("sti");
  putstr("[ INFO ] GDT Initialized\n");
  sleep(300);
  putstr("[ INFO ] IDT Initialized\n");
  sleep(300);
  putstr("[ INFO ]  Installing ISRs\n");
  sleep(300);
  putstr("[ INFO ] Initializing Keyboard (IRQ1)\n");
  sleep(500);
  clear();
  putstr("Kernel of Khazar");
  while (1)
    ;
}
