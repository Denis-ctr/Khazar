global loader
extern kernel_main

; Multiboot 1 Başlığı
MAGIC_NUMBER      equ 0x1BADB002
FLAGS             equ 0x0
CHECKSUM          equ -(MAGIC_NUMBER + FLAGS)
KERNEL_STACK_SIZE equ 4096

section .bss
align 4096
p4_table:
    resb 4096
p3_table:
    resb 4096
p2_table:
    resb 4096
kernel_stack:
    resb KERNEL_STACK_SIZE


section .rodata
gdt64:
    dq 0 ; null descriptor
.code: equ $ - gdt64
    dq (1<<43) | (1<<44) | (1<<47) | (1<<53) ; code descriptor
.pointer:
    dw $ - gdt64 - 1
    dq gdt64

section .text
bits 32
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM
    
loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE

    ; 64-bit destek
    call check_cpuid ; prossesorun model ve keyfiyyeti cpuid
    call check_long_mode

    ; Sayfalama (Paging) hazırlığı
    call setup_page_tables
    call enable_paging

    ; 64-bit GDT loader
    lgdt [gdt64.pointer]

    ; 64-bit moda keçid (Long Jump)
    jmp gdt64.code:long_mode_start

check_cpuid:
    ; CPUID dəstəyini yoxlayır (EFLAGS 21-ci bitini dəyişməyə çalışaraq)
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    cmp eax, ecx
    je .no_cpuid
    ret
.no_cpuid:
    mov al, "1"
    jmp error

check_long_mode:
    ; Long Mode desteyi
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .no_long_mode

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .no_long_mode
    ret
.no_long_mode:
    mov al, "2"
    jmp error

setup_page_tables:
    mov eax, p3_table
    or eax, 0b11 ; present + writable
    mov [p4_table], eax

    mov eax, p2_table
    or eax, 0b11 ; present + writable
    mov [p3_table], eax

    mov eax, 0 | 0b10000011 ; present + writable + huge
    mov [p2_table], eax

    ret

enable_paging:

    mov eax, p4_table
    mov cr3, eax


    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax


    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr


    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret

error:
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov byte  [0xb8008], al
    hlt

bits 64
long_mode_start:
    ; 1. Seqment registrlərini null (0) ilə təmizləyirik
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; 2. 64-bitlik steki (rsp) təyin edirik
    mov rsp, kernel_stack + KERNEL_STACK_SIZE 

    ; 3. Multiboot məlumatını (ebx-də idi) RDI-yə köçürürük
    ; Beləliklə kernel_main(unsigned int multiboot_info) şəklində arqument alacaq
    mov edi, ebx 

    ; 4. C nüvəsini çağırırıq
    extern kernel_main
    call kernel_main

    ; Əgər kernel geri dönsə, sistemi dayandırırıq
    hlt