ORG 0x0
BITS 16

_start:
    jmp short start ; initialize BPB according to the specification
    nop

times 33  db 0 ; zero out the rest of the BPB

start:
    jmp 0x7c0:step2 ; set code segment to 0x7c0

handle_zero: ; handle int 0x00
    mov ah, 0eh
    mov al, 'A'
    mov bx, 0x00
    int 0x10
    iret

handle_one:
    mov ah, 0eh
    mov al, 'V'
    mov bx, 0x00
    int 0x10
    iret

step2:
    cli     ; clear (diable) interrupts
    mov ax, 0x7c0
    mov ds, ax
    mov es, ax ; set data segments to be universal for all bioses
    mov ax, 0x00
    mov ss, ax
    mov sp, 0x7c00
    sti     ; enable interrupts

    mov word[ss:0x00], handle_zero ; stack segment points to 0x00, set offset in interrupt table to handle_zero interrupt handler
    mov word[ss:0x02], 0x7c0 ; set segment of interrupt to code

    mov word[ss:0x04], handle_one
    mov word[ss:0x06], 0x7c0

    int 0
    int 1

    mov si, message ; load message label address
    call print

    jmp $           ; do not go to lower instructions

print:
.loop:
    lodsb ; load char pointed by si to al
    cmp al, 0
    je .done ; done printing if encountered '0' char
    call print_char
    jmp .loop

.done:
    ret

print_char:
    mov ah, 0eh
    int 0x10
    ret

message: db 'hello world', 0

times 510- ($ - $$) db 0 ; zero out 510 bytes of data
dw 0xAA55                ; add boot signature
