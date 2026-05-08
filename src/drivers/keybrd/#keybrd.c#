#include "../../include/keybrd/keybrd.h"
#include "../../include/idt.h"
#include "../../include/isr.h"
#include "../../include/typint.h"
#include "../../include/vga.h"

#define IRQ1 33

void print_letter(uint8_t scancode) {
  switch (scancode) {
  case 0x0:
    putstr("ERROR");
    break;
  case 0x1:
    putstr("ESC");
    break;
  case 0x2:
    putstr("1");
    break;
  case 0x3:
    putstr("2");
    break;
  case 0x4:
    putstr("3");
    break;
  case 0x5:
    putstr("4");
    break;
  case 0x6:
    putstr("5");
    break;
  case 0x7:
    putstr("6");
    break;
  case 0x8:
    putstr("7");
    break;
  case 0x9:
    putstr("8");
    break;
  case 0x0A:
    putstr("9");
    break;
  case 0x0B:
    putstr("0");
    break;
  case 0x0C:
    putstr("-");
    break;
  case 0x0D:
    putstr("=");
    break;
  case 0x0E:
    putstr("BACKSPACE");
    break;
  case 0x0F:
    putstr("TAB");
    break;
  case 0x10:
    putstr("q");
    break;
  case 0x11:
    putstr("w");
    break;
  case 0x12:
    putstr("e");
    break;
  case 0x13:
    putstr("r");
    break;
  case 0x14:
    putstr("t");
    break;
  case 0x15:
    putstr("y");
    break;
  case 0x16:
    putstr("u");
    break;
  case 0x17:
    putstr("i");
    break;
  case 0x18:
    putstr("o");
    break;
  case 0x19:
    putstr("p");
    break;
  case 0x1A:
    putstr("[");
    break;
  case 0x1B:
    putstr("]");
    break;
  case 0x1C:
    putstr("ENTER");
    break;
  case 0x1D:
    putstr("LCTRL");
    break;
  case 0x1E:
    putstr("a");
    break;
  case 0x1F:
    putstr("s");
    break;
  case 0x20:
    putstr("d");
    break;
  case 0x21:
    putstr("f");
    break;
  case 0x22:
    putstr("g");
    break;
  case 0x23:
    putstr("h");
    break;
  case 0x24:
    putstr("j");
    break;
  case 0x25:
    putstr("k");
    break;
  case 0x26:
    putstr("l");
    break;
  case 0x27:
    putstr(";");
    break;
  case 0x28:
    putstr("'");
    break;
  case 0x29:
    putstr("`");
    break;
  case 0x2A:
    putstr("LSHIFT");
    break;
  case 0x2B:
    putstr("\\");
    break;
  case 0x2C:
    putstr("z");
    break;
  case 0x2D:
    putstr("x");
    break;
  case 0x2E:
    putstr("c");
    break;
  case 0x2F:
    putstr("v");
    break;
  case 0x30:
    putstr("b");
    break;
  case 0x31:
    putstr("n");
    break;
  case 0x32:
    putstr("m");
    break;
  case 0x33:
    putstr(",");
    break;
  case 0x34:
    putstr(".");
    break;
  case 0x35:
    putstr("/");
    break;
  case 0x36:
    putstr("RSHIFT");
    break;
  case 0x37:
    putstr("*");
    break;
  case 0x38:
    putstr("LALT");
    break;
  case 0x39:
    putstr("Space");
    break;
  case 0x3A:
    putstr("CAPS");
    break;
  case 0x3B:
    putstr("F1");
    break;
  case 0x3C:
    putstr("F2");
    break;
  case 0x3D:
    putstr("F3");
    break;
  case 0x3E:
    putstr("F4");
    break;
  case 0x3F:
    putstr("F5");
    break;
  case 0x40:
    putstr("F6");
    break;
  case 0x41:
    putstr("F7");
    break;
  case 0x42:
    putstr("F8");
    break;
  case 0x43:
    putstr("F9");
    break;
  case 0x44:
    putstr("F10");
    break;
  case 0x45:
    putstr("NUMLOCK");
    break;
  case 0x46:
    putstr("SCROLLLOCK");
    break;
  case 0x47:
    putstr("HOME");
    break;
  case 0x48:
    putstr("UP");
    break;
  case 0x49:
    putstr("PAGEUP");
    break;
  case 0x4A:
    putstr("-");
    break;
  case 0x4B:
    putstr("LEFT");
    break;
  case 0x4C:
    putstr("CENTER");
    break;
  case 0x4D:
    putstr("RIGHT");
    break;
  case 0x4E:
    putstr("+");
    break;
  case 0x4F:
    putstr("END");
    break;
  case 0x50:
    putstr("DOWN");
    break;
  case 0x51:
    putstr("PAGEDOWN");
    break;
  case 0x52:
    putstr("INSERT");
    break;
  case 0x53:
    putstr("DELETE");
    break;
  default:
    if (scancode <= 0x7f) {
      putstr(" [ ERROR ] : Unknown key down");
    } else if (scancode <= 0x39 + 0x89) {
      putstr(" [ KEY UP ] ");
      print_letter(scancode - 0x80);
    } else {
      putstr("Unknown Key Up");
    }
  }
}

static void keyboard_callback(registers_t *regs) {
  uint8_t scancode = byte_i(0x60);
  print_letter(scancode);
  putstr("\n");
}

void init_keyboard() { register_interrupt_handler(IRQ1, keyboard_callback); }
