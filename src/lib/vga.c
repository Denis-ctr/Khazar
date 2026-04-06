#include "../include/typint.h"

void vga_write()
{
  char *buffer = (char*) 0xb8000;
  char *mesaj = "Salam";
  uint8_t reng = 0x02;

  for (int i = 0; mesaj[i] != '\n'; i++)
  {
    buffer[i * 2] = mesaj[i];
    buffer[i * 2 + 1] = reng;
  }
}
