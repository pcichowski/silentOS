<h1 align="center">
    <img src="./.github/images/silentOS_logo.png" width="30%" height="30%">
    </br>
    silentOS
    </br>
</h1>

<p align="center">
    <a href="https://github.com/Silentsky0/silentOS/blob/main/LICENSE">
        <img src="https://img.shields.io/github/license/Silentsky0/silentOS">
    </a>
    <img src="https://img.shields.io/badge/arch-i386-informational">
    <img src="https://img.shields.io/badge/arch-i686-informational">
</p>

<h3 align="center">
    An operating system made from scratch
</h3>

# Overview

This project's aim was to create an operating system from scratch. The main 
goals were a simple console, segmentation, paging, and a FAT16 filesystem 
capable of opening and reading files from disk.

It was created using guides on [OSDev wiki](https://wiki.osdev.org/Main_Page) 
and [an online course on Udemy](https://www.udemy.com/course/developing-a-multithreaded-kernel-from-scratch/) 
by Daniel McCarthy. This was the main project for System Software 
(Oprogramowanie Systemowe) course on the 5th semester of computer science on 
GUT.

This project uses QEMU to run the OS on a virtual machine, nonetheless it is 
able to run on any computer using a bootable USB (I actually tried it for fun 
:) )

## Table of contents
- [Overview](#overview)
  - [Table of contents](#table-of-contents)
- [About this system](#about-this-system)
- [Setup](#setup)
  - [Prerequisites](#prerequisites)
  - [Building system image](#building-system-image)
- [Usage](#usage)
  - [Running the OS](#running-the-os)
  - [Cleaning build artifacts](#cleaning-build-artifacts)
- [Credits](#credits)
  - [License](#license)
  - [Acknowledgements](#acknowledgements)

# About this system

The default behaviour of the operating system is explained in the following 
steps:
1. start at the bootloader
1. intialize segmentation 
   - (in a way that it doesn't affect the OS, so all 
segments point to the entire memory)
1. boot to the operating system
1. initialize console, show system logo
1. initialize kernel heap for memory allocation
1. initialize Virtual File System and FAT16 filesystem
1. search for disk and attach it to FAT16
1. intialize the interrupt descriptor table
1. allocate some memory for the kernel
1.  enable paging and map the kernel memory
1.  enable interrupts

These steps leave the kernel in a fully working state, we are free to do 
anything now

As an example for the main goal of this project, that is reading a file from 
disk and displaying it to screen, the system will load two files to some 
allocated memory and print their contents to the console.

# Setup

## Prerequisites

- `make`
- `gcc` and `ld` built locally for crosscompilation
  - follow the guide on [OSDev wiki](https://wiki.osdev.org/GCC_Cross-Compiler)
- `qemu`

## Building system image

```
./build.sh
```

This sets the default target and invokes `make all`

> Note: you need to set correct paths to `gcc` and `ld` in `build.sh`, the 
default values are those shown on the wiki article

# Usage

## Running the OS

```
qemu-system-i386 -hda ./bin/os.bin
```

## Cleaning build artifacts

```
make all
```

# Credits

## License

This project is a free and open-source software licensed under the 
[GPL-3.0 license](./LICENSE)

## Acknowledgements

- [Developing a Multithreaded Kernel From Scratch!](https://www.udemy.com/course/developing-a-multithreaded-kernel-from-scratch/) by Daniel McCarthy on 
Udemy
- Many excellent guides on [OSDev Wiki](https://wiki.osdev.org/Main_Page)
