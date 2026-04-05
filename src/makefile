all:
	nasm -f elf32 boot/loader.s -o build/loader.o
	gcc -m32 -ffreestanding -c kernel/kernel.c -o build/kernel.o
	gcc -m32 -ffreestanding -c drivers/vga.c -o build/vga.o
	ld -m elf_i386 -T boot/link.ld -o iso/boot/kernel.elf build/loader.o build/kernel.o build/vga.o
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o os.iso iso/

clean:
	rm -f build/*.o iso/boot/kernel.elf os.iso