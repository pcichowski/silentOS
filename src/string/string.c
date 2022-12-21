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

char tolower(char c) {
    if (c >= 65 && c <= 90) {
        c += 32;
    }
    return c;
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

int istrncmp(const char *str1, const char *str2, int n) {
    unsigned char u1, u2;

    while (n-- > 0) {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;

        if (u1 != u2 && tolower(u1) != tolower(u2))
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }
    return 0;
}

int strncmp(const char *str1, const char *str2, int n) {
    unsigned char u1, u2;
    
    while (n--) {
        u1 = (unsigned char)*str1++;
        u2 = (unsigned char)*str2++;

        if (u1 != u2)
            return u1 - u2;
        if (u1 == '\0')
            return 0;
    }
    return 0;
}

int strnlen_terminator(const char *str, int max, char terminator) {
    int i = 0;
    for (i = 0; i < max; i++) {
        if (str[i] == '\0' || str[i] == terminator)
            break;
    }

    return i;
}

char *strcpy(char *dest, const char *src) {
    char *tmp = dest;
    while (*src != 0) {
        *dest = *src;
        src += 1;
        dest += 1;
    }

    *dest = 0x00;

    return tmp;
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

