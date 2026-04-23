#include "../include/typint.h"
#include "../include/vga.h"
// prot byte input output

uint8_t byte_i(uint16_t port) {
  uint8_t result;
  __asm__ volatile(
      "in %%dx, %%al"
      : "=a"(result)
      : "d"(port)); // qaqas men burda gotururem port deyisenini DX registrine
                    // yukleyirem DXdeki unvani ALye yerlesdirirem ALdaki
                    // neticeni result deyisenine yaziram
  return result;
}

void byte_o(uint16_t port, uint8_t data) {
  __asm__ volatile(
      "out %%al, %%dx"
      :
      : "a"(data),
        "d"(port)); // qaqas men burda ise data deyisenini AL registrine
                    // yukleyrem port deyisenini DX registrine yukleyrem sonra
                    // da ALdaki bayti DX unvanina gonderrem
}
