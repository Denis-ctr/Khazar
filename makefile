CC      = gcc
NASM    = nasm
CFLAGS  = -m64 -ffreestanding -mcmodel=kernel -mno-red-zone -fno-pic -fno-PIC -fno-pie -fno-stack-protector -mgeneral-regs-only

# Fayl yolları
KERNEL_BIN = src/build/kernel.bin
ISO_DIR    = src/iso
ISO_KERNEL = $(ISO_DIR)/boot/kernel.elf

# Mənbə faylları
SRCS = src/boot/loader.s \
       src/kernel/kernel.c \
       src/lib/idt.c \
       src/lib/gdt.s \
       src/lib/gdt.c \
       src/lib/io.c \
       src/lib/vgatext.c \
       src/lib/isr.c

all: iso

$(KERNEL_BIN): $(SRCS) src/boot/link.ld
	mkdir -p src/build
	$(NASM) -f elf64 src/boot/loader.s -o src/build/loader.o
	$(CC) $(CFLAGS) -c src/kernel/kernel.c -o src/build/kernel.o
	$(CC) $(CFLAGS) -c src/lib/idt.c -o src/build/idt.o
	$(NASM) -f elf64 src/lib/gdt.s -o src/build/gdt_s.o
	$(CC) $(CFLAGS) -c src/lib/gdt.c -o src/build/gdt.o
	$(CC) $(CFLAGS) -c src/lib/io.c -o src/build/io.o
	$(CC) $(CFLAGS) -c src/lib/vgatext.c -o src/build/vgatext.o
	$(CC) $(CFLAGS) -c src/lib/isr.c -o src/build/isr.o
	ld -n -o $(KERNEL_BIN) -T src/boot/link.ld \
		src/build/loader.o \
		src/build/kernel.o \
		src/build/vgatext.o \
		src/build/idt.o \
		src/build/gdt_s.o \
		src/build/gdt.o \
		src/build/io.o \
		src/build/isr.o

iso: $(KERNEL_BIN)
	cp $(KERNEL_BIN) $(ISO_KERNEL)
	grub-mkrescue -o khazar.iso $(ISO_DIR)

run: iso
	qemu-system-x86_64 -cdrom khazar.iso -display gtk

clean:
	rm -rf src/build
	rm -f khazar.iso
