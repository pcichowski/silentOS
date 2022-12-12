#ifndef STRING_H
#define STRING_H

int strlen(const char *ptr);
int strnlen(const char *ptr, int max_length);
char *strcpy(char *dest, const char *src);
int is_digit(char c);
int ascii_char_to_digit(char c);

#endif // STRING_H
