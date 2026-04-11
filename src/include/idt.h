#pragma once

#include "typint.h"
#include "vgat.h"

#define KERNEL_CS 0x08  //Kernel seqment terefi

typedef struct {
    uint16_t low_offset;   // handler[0:15]
    uint16_t sel;          // KERNEL_CS = 0x08
    uint8_t  ist;          // Interrupt Stack Table (0 ol)
    uint8_t  flags;        // 
    uint16_t mid_offset;   // handler[16:31]
    uint32_t high_offset;  // handler[32:63]
    uint32_t reserved;     // mütleq 0 olmalıdi
} __attribute__((packed)) idt_gate_t;  // = 16 bayt

//bu (yuxardaki kod) artiq low levelda isitafde olunan bi kod strukturudur hansi ki gelen kesmeni yeni zengin ne is goreceyini basa dusmek ucun


typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idt_register_t;


//kesinti aninda prosessorun veziyyetini tanimasi ucun interrupt frame
struct interrupt_frame 
{
    uint64_t ip;
    uint64_t cs;
    uint64_t flags;
    uint64_t sp;
    uint64_t ss;
};

#define IDT_ENTRIES 256 //256 giris oldugu ucun IDT girislerini 256 edirik

//c kodunun bunu extern olaraq tanimasi ucundur
extern void load_idt(uint64_t idtr_ptr);
void idt_init();
