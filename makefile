all:
	nasm -f elf32 src/boot/loader.s -o src/build/loader.o
	gcc -m32 -ffreestanding -c src/kernel/kernel.c -o src/build/kernel.o
	gcc -m32 -ffreestanding -c src/lib/vga.c -o src/build/vga.o
	ld -m elf_i386 -T src/boot/link.ld -o src/iso/boot/kernel.elf src/build/loader.o src/build/kernel.o src/build/vga.o
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o os.iso src/iso/

clean:
	rm -f src/build/*.o src/iso/boot/kernel.elf os.iso