#ifndef FAT16_H
#define FAT16_H

#include "file.h"

struct filesystem *fat16_init();

int fat16_read(struct disk *disk, void *descriptor, uint32_t size, uint32_t nmemb, char *out_ptr);

#endif // FAT16_H
