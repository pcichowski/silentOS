#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 24
#define MAX_PATH_LENGTH 108

void kernel_main();

uint16_t console_char(char a, char color);
void console_initialize();
void console_putchar(int x, int y, char a, char colour);
void print(const char *str);

#define ERROR(value)    (void *)(value)
#define ERROR_I(value)  (int)(value)
#define ISERR(value)  ((int)(value) < 0)

#endif
