#include "kernel.h"

void kernel_main()
{
    char *video_mem = (char*)(0xB8000);

    video_mem[0] = 'A';
    video_mem[1] = 3;

    video_mem[2] = 'C';
    video_mem[3] = 2;
}
