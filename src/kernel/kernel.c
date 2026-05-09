#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/keybrd/keybrd.h"
#include "../include/multiboot.h"
#include "../include/pit/pit.h"
#include "../include/typint.h"
#include "../include/vga.h"

void kernel_main(uint64_t multiboot_addr) {
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
  putstr("Kernel of Khazar\n");

  multiboot_info_t *mb = (multiboot_info_t *)multiboot_addr;
  if (mb->flags & MULTIBOOT_FLAG_MAP) {
    putstr("\n[ memory ]\n");
    multiboot_entry_t *entry = (multiboot_entry_t *)((uint64_t)mb->mmap_addr);
    uint64_t end = (uint64_t)mb->mmap_addr + mb->mmap_length;
    while ((uint64_t)entry < end) {
      if (entry->type == 1) {
        putstr("[ USABLE ]   addr: ");
        puthex(entry->addr);
        putstr("  len: ");
        puthex(entry->len);
        putstr("\n");
      } else {
        putstr("[ RESERVED ] addr: ");
        puthex(entry->addr);
        putstr("  len: ");
        puthex(entry->len);
        putstr("\n");
      }
      entry = (multiboot_entry_t *)((uint64_t)entry + entry->size + 4);
    }
  }

  while (1)
    ;
}
