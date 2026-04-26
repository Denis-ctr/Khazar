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
void set_char_in_memory(uint8_t character, int32_t offset);

// printf funksiyasi
void putstr(string_const string);
void puthex(uint64_t n);

// komekci functionlar
int32_t get_row(int32_t offset);
int32_t get_offset(int32_t col, int32_t row);
int32_t move_newl(int32_t offset);

void memorycpy(uint8_t *source, uint8_t *dest,
               int32_t nbyte); // newline ucun memorye copy edir bu function

int32_t scrolln(int32_t offset); // bu ise ekrani scroll edib yuxari kocurur

// ekrani clear edir
void clear();

#endif
