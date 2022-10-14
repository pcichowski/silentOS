# silentOS

OS created from scratch

## Prerequisites

- `nasm`
- `qemu-system-x86_64`

## Building bootloader image

```
nasm -f bin boot.asm -o boot.bin
```

## Running the bootloader

```
qemu-system-x86_64 -hda ./boot.bin
```
