# silentOS

OS created from scratch

## Prerequisites

- `nasm`
- `qemu-system-x86_64`

## Build the image

```
./build.sh
```

This sets the default target and invokes `make all`

## Running the OS

```
qemu-system-x86_64 -hda ./os.bin
```
