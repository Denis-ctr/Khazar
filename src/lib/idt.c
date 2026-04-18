#include "../include/idt.h"
#include "../include/typint.h"

idtent_t idt[IDT_ENTRIES]; // 256liq bir massiv

idtptr_t idtr; // idt deyisenini ve registrini saxliyir

void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags) {
  idt[num].low_offset = (uint16_t)(base & 0xFFFF); // adressin 0-15 bitleri
  idt[num].mid_offset =
      (uint16_t)((base >> 16) & 0xFFFF); // adressin 16-31 bitleri
  idt[num].high_offset =
      (uint32_t)((base >> 32) & 0xFFFFFFFF); // adressin 32-63 bitleri

  idt[num].sel = sel;
  idt[num].ist = 0;
  idt[num].flags = flags;
  idt[num].reserved = 0;
}

extern void *isr_stub_table[]; // Assembly-dən gələn cədvəl
void idt_init() {
  idtr.limit = (sizeof(idtent_t) * IDT_ENTRIES) - 1;
  idtr.base = (uint64_t)&idt;
  // İlk 32 istisnanı avtomatik qeydiyyata alırıq
  for (int i = 0; i < 32; i++) {
    idt_set_gate(i, (uint64_t)isr_stub_table[i], 0x08, 0x8E);
  }
  load_idt((uint64_t)&idtr);
}

extern void load_idt(uint64_t idtr_ptr);