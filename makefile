CC      = gcc
NASM    = nasm
CFLAGS  = -m64 -ffreestanding -mcmodel=kernel -mno-red-zone -fno-pic -fno-PIC -fno-pie -fno-stack-protector

# Fayl yolları
KERNEL_BIN = src/build/kernel.bin
ISO_DIR    = src/iso
ISO_KERNEL = $(ISO_DIR)/boot/kernel.elf

all: iso

$(KERNEL_BIN):
	mkdir -p src/build
	$(NASM) -f elf64 src/boot/loader.s -o src/build/loader.o
	$(CC) $(CFLAGS) -c src/kernel/kernel.c -o src/build/kernel.o
	$(CC) $(CFLAGS) -c src/lib/vgatext.c      -o src/build/vgatext.o
	ld -n -o $(KERNEL_BIN) -T src/boot/link.ld \
		src/build/loader.o \
		src/build/kernel.o \
		src/build/vgatext.o

iso: $(KERNEL_BIN)
	cp $(KERNEL_BIN) $(ISO_KERNEL)
	grub-mkrescue -d src/iso/boot/grub/ -o os.iso $(ISO_DIR)

run: iso
	qemu-system-x86_64 -cdrom os.iso

clean:
	rm -rf src/build
	rm -f os.iso
