#include "../include/vgat.h"
#include "../include/typint.h"
#include "../include/idt.h"

void kernel_main() {
    clear();
    idt_init();
    putstr("Kernel of Khazar");
}
