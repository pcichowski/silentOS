#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 24


void kernel_main();

uint16_t console_char(char a, char color);
void console_initialize();
void console_putchar(int x, int y, char a, char colour);
void print(const char *str);

#endif
