#include "string.h"

int
strlen(const char *ptr)
{
    int i = 0;
    while (*ptr != 0) {
        i += 1;
        ptr += 1;
    }

    return i;
}

int
strnlen(const char *ptr, int max_length)
{
    int i = 0;
    for (i = 0; i < max_length; i++) {
        if (ptr[i] == 0)
            break;
    }
    return i;
}

int
is_digit(char c)
{
    return c >= 48 && c <= 57;
}

int
ascii_char_to_digit(char c)
{
    return c - 48;
}

