#include "typint.h"
#include "vgat.h"

struct gdt_entries {
  uint16_t limit_low;  // The lower 16 bits of the limit.
  uint16_t base_low;   // The lower 16 bits of the base.
  uint8_t base_middle; // The next 8 bits of the base.
  uint8_t
      access; // Access flags, determine what ring this segment can be used in.
  uint8_t granularity; // Granularity flags, determine the size of the segment.
  uint8_t base_high;   // The higher 8 bits of the base.
} __attribute__((packed));

typedef struct gdt_entries gdtent_t;

struct gdt_ptr {
  uint16_t limit;
  uint64_t base;
} __attribute__((packed));

typedef struct gdt_ptr gdtptr_t;

void init_gdt();