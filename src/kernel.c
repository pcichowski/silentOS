#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"

uint16_t *video_mem = 0;

uint16_t console_row = 0;
uint16_t console_col = 0;

/*
 * Makes a correct console character with a specified background
 */
uint16_t
console_char(char a, char colour)
{
    return (colour << 8 ) | a;
}

void
console_putchar(int x, int y, char a, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = console_char(a, colour);
}

void
console_writechar(char c, char colour)
{
    if (c == '\n') {
        console_row += 1;
        console_col = 0;
        return;
    }

    console_putchar(console_col, console_row, c, colour);

    console_col += 1;

    if (console_col >= VGA_WIDTH) {
        console_col = 0;
        console_row += 1;
    }
}

/*
 * Clears the console screen
 */
void
console_initialize()
{
    video_mem = (uint16_t*)(0xB8000);

    for (int i = 0; i < VGA_HEIGHT; i++) {
        for (int j = 0; j < VGA_WIDTH; j++) {
            console_putchar(j, i, ' ', 0);
        }
    }
}

size_t
strlen(const char *str)
{
    size_t len = 0;
    while(str[len]) {
        len += 1;
    }
    return len;
}

void
print(const char *str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++) {
        console_writechar(str[i], 15);
    }
}

extern void problem();

void
kernel_main()
{
    console_initialize();

    print("hello world, the print function is working correctly\n");
    print("it even supports newlines\n");

    kheap_init();

    idt_init();
    enable_interrupts();

}
