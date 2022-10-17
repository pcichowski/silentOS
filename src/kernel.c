#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/pmap/pmap.h"

uint16_t *video_mem = 0;

uint16_t console_row = 0;
uint16_t console_col = 0;

static struct pmap_chunk* kernel_chunk = 0;

const char *kernel_logo1 =
"     _ _            _    ____ ____\n";
const char *kernel_logo2 =
"    (_) |          | |  / _  /  ___\\\n";
const char *kernel_logo3 =
" ___ _| | ___ _ __ | |_| | | \\ `--.\n";
const char *kernel_logo4 =
"/ __| | |/ _ \\ '_ \\| __| | | |`--. \\\n";
const char *kernel_logo5 =
"\\__ \\ | |  __/ | | | |_\\ \\_/ /\\__/ /\n";
const char *kernel_logo6 =
"|___/_|_|\\___|_| |_|\\__|\\___/\\____/\n\n";

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

    print(kernel_logo1);
    print(kernel_logo2);
    print(kernel_logo3);
    print(kernel_logo4);
    print(kernel_logo5);
    print(kernel_logo6);

    print("\nWelcome to silentOS v1.0\n");

    kheap_init();

    idt_init();

    kernel_chunk = pmap_new_chunk(PMAP_IS_WRITEABLE | PMAP_IS_PRESENT | PMAP_ACCESS_FROM_ALL);

    pmap_switch(pmap_chunk_get_directory(kernel_chunk));

    char *ptr = kzalloc(4096);

    pmap_set(pmap_chunk_get_directory(kernel_chunk), (void *)0x1000, (uint32_t)ptr | PMAP_ACCESS_FROM_ALL | PMAP_IS_PRESENT | PMAP_IS_WRITEABLE);

    pmap_enable();

    char* ptr2 = (char*) 0x1000;
    ptr2[0] = 'A';
    ptr2[1] = 'B';
    print(ptr2);

    print(ptr);

    enable_interrupts();

}
