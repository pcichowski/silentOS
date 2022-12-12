#ifndef DISK_H
#define DISK_H

#include "filesystem/file.h"

typedef unsigned int DISK_TYPE;

#define DISK_TYPE_REAL 0

struct disk {
    DISK_TYPE type;
    int sector_size;

    struct filesystem *filesystem;
};

void disk_search_and_init();
struct disk* disk_get(int index);
int disk_read_block(struct disk *idisk, unsigned int lba, int total, void *buf);

#endif // DISK_H
