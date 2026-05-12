#pragma once

#include "../../include/typint.h"
#include "../../include/vga.h"

#define MULTIBOOT_FLAG_MEM (1 << 0)
#define MULTIBOOT_FLAG_MAP (1 << 6)

typedef struct {
  uint32_t size;
  uint64_t addr;
  uint64_t len;
  uint32_t type;
} __attribute__((packed)) multiboot_entry_t;

typedef struct {
  uint32_t flags;     // hansı sahələrin dolu olduğunu göstərir
  uint32_t mem_lower; // 640KB-dan aşağı RAM (KB ilə)
  uint32_t mem_upper; // 1MB-dan yuxarı RAM (KB ilə)
  uint32_t boot_device;
  uint32_t cmdline;
  uint32_t mods_count;
  uint32_t mods_addr;
  uint32_t syms[4];
  uint32_t mmap_length; // memory map-in ümumi ölçüsü (byte)
  uint32_t mmap_addr;
} __attribute__((packed)) multiboot_info_t;
