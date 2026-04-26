CC   = gcc
NASM = nasm

CFLAGS = -m64 -ffreestanding -mcmodel=kernel -mno-red-zone \
         -fno-pic -fno-PIC -fno-pie -fno-stack-protector \
         -mgeneral-regs-only \
         -Isrc/include

BUILD      = src/build
ISO_DIR    = src/iso
KERNEL_BIN = $(BUILD)/kernel.bin
ISO_KERNEL = $(ISO_DIR)/boot/kernel.elf

SRCS = src/boot/loader.s   \
       src/kernel/kernel.c \
       src/cpu/idt.c       \
       src/cpu/gdt.s       \
       src/cpu/gdt.c       \
       src/drivers/io.c    \
       src/drivers/vga.c   \
       src/cpu/isr.c       \
       src/drivers/keybrd/keybrd.c

all: iso

$(KERNEL_BIN): $(SRCS) src/boot/link.ld
	mkdir -p $(BUILD)
	$(NASM) -f elf64 src/boot/loader.s       -o $(BUILD)/loader.o
	$(CC)   $(CFLAGS) -c src/kernel/kernel.c  -o $(BUILD)/kernel.o
	$(CC)   $(CFLAGS) -c src/cpu/idt.c        -o $(BUILD)/idt.o
	$(NASM) -f elf64 src/cpu/gdt.s            -o $(BUILD)/gdt_s.o
	$(CC)   $(CFLAGS) -c src/cpu/gdt.c        -o $(BUILD)/gdt.o
	$(CC)   $(CFLAGS) -c src/drivers/io.c     -o $(BUILD)/io.o
	$(CC)   $(CFLAGS) -c src/drivers/vga.c    -o $(BUILD)/vga.o
	$(CC)   $(CFLAGS) -c src/cpu/isr.c        -o $(BUILD)/isr.o
	$(CC)    $(CFLAGS) -c src/drivers/keybrd/keybrd.c   -o $(BUILD)/keybrd.o

	ld -n -o $(KERNEL_BIN) -T src/boot/link.ld \
		$(BUILD)/loader.o  \
		$(BUILD)/kernel.o  \
		$(BUILD)/vga.o     \
		$(BUILD)/idt.o     \
		$(BUILD)/gdt_s.o   \
		$(BUILD)/gdt.o     \
		$(BUILD)/io.o      \
		$(BUILD)/isr.o     \
		$(BUILD)/keybrd.o

iso: $(KERNEL_BIN)
	cp $(KERNEL_BIN) $(ISO_KERNEL)
	grub-mkrescue -o khazar.iso $(ISO_DIR)

run: iso
	qemu-system-x86_64 -cdrom khazar.iso -display gtk

clean:
	rm -rf $(BUILD)
	rm -f khazar.iso
