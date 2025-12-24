BITS 16
ORG 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax

    lgdt [gdt_descriptor]
    mov eax, cr0
    or  eax, 1
    mov cr0, eax
    jmp 0x08:pm_start

gdt_start:
    dq 0
    dw 0xFFFF, 0x0000, 0x00, 0x9A, 0xCF, 0x00
    dw 0xFFFF, 0x0000, 0x00, 0x92, 0xCF, 0x00
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

[BITS 32]
pm_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    xor ebp, ebp
    xor esp, esp
    jmp 0x00100000

times 510-($-$$) db 0
dw 0xAA55
