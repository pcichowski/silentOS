ORG 0x7c00
BITS 16

start:
    mov ah, 0eh
    mov al, 'A'
    int 0x10        ; call BIOS routine to output A to the console

    jmp $           ; do not go to lower instructions

times 510- ($ - $$) db 0 ; zero out 510 bytes of data
dw 0xAA55                ; add boot signature
