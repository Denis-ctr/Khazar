#ifndef IO_H
#define IO_H
#include "typint.h"
#include "vgat.h"

//io funcs

//prot byte input output

uint8_t byte_i(uint16_t port);

void byte_o(uint16_t port, uint8_t data);

#endif
