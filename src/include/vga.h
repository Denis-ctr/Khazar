#ifndef VGA_H
#define VGA_H

#include "typint.h"

// hardware terefden input output
uint8_t byte_i(uint16_t port);
void byte_o(uint16_t port, uint8_t data);

// kursorun hereketi
void cursor_set(int offset);
int cursor_get();

// memorye bit yazdirmaq
void set_char_in_memory(char character, int32_t offset);

void vga_write();

#endif