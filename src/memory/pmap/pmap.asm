[BITS 32]

section .asm

global pmap_load_directory
global pmap_enable

pmap_load_directory:
    push ebp
    mov ebp, esp

    mov eax, [ebp + 8]
    mov cr3, eax

    pop ebp
    ret

pmap_enable:
    push ebp
    mov ebp, esp

    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    pop ebp
    ret
