#include "../include/typint.h"
#include "../include/vga.h"

//prot byte input output

uint8_t byte_i(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("in %%dx, %%al" : "=a" (result) : "d" (port)); // qaqas men burda gotururem port deyisenini DX registrine yukleyirem DXdeki unvani ALye yerlesdirirem ALdaki neticeni result deyisenine yaziram
    return result;
}

void byte_o(uint16_t port, uint8_t data) {
    __asm__ volatile ("out %%al, %%dx" : : "a" (data), "d" (port)); // qaqas men burda ise data deyisenini AL registrine yukleyrem port deyisenini DX registrine yukleyrem sonra da ALdaki bayti DX unvanina gonderrem
}

#define VGA_CTRL_REGISTER 0x3d4 //vganin control registri
#define VGA_DATA_REGISTER 0x3d5 //vganin data registri
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

void cursor_set(int offset)
{
    offset /= 2;
    byte_o(VGA_CTRL_REGISTER,VGA_OFFSET_HIGH);
    byte_o(VGA_DATA_REGISTER, (uint8_t) (offset >> 8));
    byte_o(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    byte_o(VGA_DATA_REGISTER, (uint8_t) (offset & 0xff));
}

int cursor_get()
{
    byte_o(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset =byte_i(VGA_DATA_REGISTER) << 8;
    byte_o(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += byte_i(VGA_DATA_REGISTER);
    return offset * 2; //burda da qaqas her sey 2 bit yer aldigi ucun ijiye vururuq yeni bele bisey
}


#define ADRESS 0xb8000
#define MAX_ROW 25
#define MAX_COL 80
#define WHITE_BLACK 0x0f

void set_char_in_memory(char character, int32_t offset)
{
    uint8_t *vidmem = (uint8_t*) ADRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = WHITE_BLACK;
}           //bunla da sen goturub ekranin hansisa memory adressine erisim edib bit yazdira bilersen

