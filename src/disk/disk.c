#include "disk.h"
#include "io/io.h"
#include "memory/memory.h"
#include "config.h"
#include "status.h"

struct disk disk;

int
disk_read_sector(int lba, int total, void *buf)
{
    outb(0x1F6, (lba >> 24) | 0xE0);
    outb(0x1F2, total);
    outb(0x1F3, (unsigned char)(lba & 0xff));
    outb(0x1F4, (unsigned char)(lba >> 8));
    outb(0x1F5, (unsigned char)(lba >> 16));
    outb(0x1F7, 0x20);

    unsigned short *ptr = (unsigned short *) buf;

    for (int i = 0; i < total; i++) {
        char c = insb(0x1F7);

        while (!(c & 0x08)) { // wait for buffer to be ready
            c = insb(0x1F7);
        }

        // copy from hard disk to memory
        for (int j = 0; j < 256; j++) {
            *ptr = insw(0x1F0);
            ptr++;
        }
    }

    return 0;
}

void
disk_search_and_init()
{
    memset(&disk, 0, sizeof(disk));

    disk.id = 0; // only one disk at the moment
    disk.type = DISK_TYPE_REAL;
    disk.sector_size = SECTOR_SIZE;
    disk.filesystem = fs_resolve(&disk);
}

struct disk*
disk_get(int index)
{
    if (index != 0)
        return 0;

    return &disk;
}

int
disk_read_block(struct disk *idisk, unsigned int lba, int total, void *buf)
{
    if (idisk != &disk)
        return -EIO;

    return disk_read_sector(lba, total, buf);
}
