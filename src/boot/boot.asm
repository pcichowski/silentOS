ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

_start:
    jmp short start ; initialize BPB according to the specification
    nop

times 33  db 0 ; zero out the rest of the BPB

start:
    jmp 0:step2 ; set code segment to 0x7c0

step2:
    cli     ; clear (diable) interrupts
    mov ax, 0x00
    mov ds, ax
    mov es, ax ; set data segments to be universal for all bioses
    mov ss, ax
    mov sp, 0x7c00
    sti     ; enable interrupts


.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    ;jmp CODE_SEG:load32
    jmp $

; -- GDT --
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0
; offset 0x8
gdt_code:
    dw 0xffff   ; first 0-15 bits
    dw 0        ; base 0-15 bits
    db 0        ; base 16-23 bits
    db 0x9a     ; access byte
    db 11001111b    ; high and low 4 bit flahs
    db 0 ; base 24-31 bits
; offset 0x10
gdt_data: ; DS, SS, ES, FS, GS
    dw 0xffff   ; first 0-15 bits
    dw 0        ; base 0-15 bits
    db 0        ; base 16-23 bits
    db 0x92     ; access byte of data segment
    db 11001111b    ; high and low 4 bit flahs
    db 0 ; base 24-31 bits
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start-1
    dd gdt_start

times 510- ($ - $$) db 0 ; zero out 510 bytes of data
dw 0xAA55                ; add boot signature
