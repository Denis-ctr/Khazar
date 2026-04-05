void vga_write() {
    char* vga = (char*) 0xb8000;
    vga[0] = 'S'; vga[1] = 0x02;
    vga[2] = 'A'; vga[3] = 0x02;
    vga[4] = 'L'; vga[5] = 0x02;
    vga[6] = 'A'; vga[7] = 0x02;
    vga[8] = 'M'; vga[9] = 0x02;
    vga[10] = ' ';
}