#include "../include/typint.h"
#include "../include/idt.h"

idt_gate_t idt[IDT_ENTRIES]; //256liq bir massiv

idt_register_t idtr; //idt deyisenini ve registrini saxliyir

void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags) {
    idt[num].low_offset = (uint16_t)(base & 0xFFFF);  //adressin 0-15 bitleri
    idt[num].mid_offset = (uint16_t)((base >> 16) & 0xFFFF); //adressin 16-31 bitleri
    idt[num].high_offset = (uint32_t)((base >> 32) & 0xFFFFFFFF);  //adressin 32-63 bitleri

    idt[num].sel = sel;
    idt[num].ist = 0;
    idt[num].flags = flags;
    idt[num].reserved = 0;
}

extern void load_idt(uint64_t idtr_ptr);

void idt_init()
{// IDTR strukturunu fullamaq
    idtr.limit = (sizeof(idt_gate_t) * IDT_ENTRIES) - 1;
    idtr.base = (uint64_t)&idt;

    load_idt((uint64_t)&idtr);
}
