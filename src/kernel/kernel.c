#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/keybrd/keybrd.h"
#include "../include/memory/multiboot.h"
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

  const char* logo = "Kernel of KhazarOS";
  int32_t offset = get_offset(28, 11);
  for (int i =0; logo[i] != '\0'; i++) {
      set_char_w_color(logo[i], COLOR_LIGHT_GREEN, offset);
      offset +=2;
  }

// qardas bu memorydir PMM ucun lazm olcaq
  multiboot_info_t *mb = (multiboot_info_t *)multiboot_addr;
  if (mb->flags & MULTIBOOT_FLAG_MAP) {
    putstr("\n[ memory ]\n");
    sleep(300);
    multiboot_entry_t *entry = (multiboot_entry_t *)((uint64_t)mb->mmap_addr);
    uint64_t end = (uint64_t)mb->mmap_addr + mb->mmap_length;
   // print
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
