[BITS 32]
global _start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
    ; set data segments to the correct GDT
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; move the stack furthet
    mov ebp, 0x00200000
    mov esp, ebp

    ; enable the A20 line
    in al, 0x92
    test al, 2
    jnz .after
    or al, 2
    and al, 0xFE
    out 0x92, al
    .after:

    jmp $
