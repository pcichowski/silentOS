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
    jmp CODE_SEG:load32

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

[BITS 32]
load32:
    mov eax, 1          ; starting sector
    mov ecx, 100        ; load 100 sectors
    mov edi, 0x0100000  ; load into this addr
    call ata_lba_read
    jmp CODE_SEG:0x0100000

; --- simplest ATA driver ---

ata_lba_read:
    mov ebx, eax    ; backup lba
    shr eax, 24     ; highest 8 bits to the lba
    or eax, 0xE0    ; select the master drive
    mov dx, 0x1F6
    out dx, al
    ; sent highest 8 bits of lda

    mov eax, ecx
    mov dx, 0x1F2
    out dx, al
    ; sent number of sectors to read

    mov eax, ebx    ; restore backup lba
    mov dx, 0x1F3
    out dx, al
    ; sent more bits of the lda

    mov dx, 0x1F4
    mov eax, ebx    ; restore backup lba
    shr eax, 8
    out dx, al
    ; sent more bits of lba

    mov dx, 0x1F5
    mov eax, ebx    ; restore backup lba
    shr eax, 16
    out dx, al
    ; sent upper 16 bits of lba

    mov dx, 0x1F7
    mov al, 0x20
    out dx, al

    ; read sectors into memory

.next_sector:
    push ecx

; check if we need to read
.try_again:
    mov dx, 0x1F7
    in al, dx
    test al, 8
    jz .try_again

    ; read 256 words at a time
    mov ecx, 256
    mov dx, 0x1F0
    rep insw    ; read from the port 0x1F0 and store into EDI (address of the kernel)
    pop ecx     ; restore number of sectors
    loop .next_sector
    ret         ; end of reading sectors

times 510- ($ - $$) db 0 ; zero out 510 bytes of data
dw 0xAA55                ; add boot signature
