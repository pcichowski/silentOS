ORG 0x7c00
BITS 16

start:
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
