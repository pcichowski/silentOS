#include "file.h"
#include "config.h"
#include "memory/memory.h"
#include "memory/heap/kheap.h"
#include "status.h"
#include "kernel.h"

struct filesystem *filesystems[MAX_FILESYSTEMS];

struct file_descriptor *file_descriptors[MAX_FILE_DESCRIPTORS];

static struct filesystem **
fs_get_free_filesystem()
{
    int i = 0;
    for (i = 0; i < MAX_FILESYSTEMS; i++) {
        if (filesystems[i] == 0) {
            return &filesystems[i];
        }
    }

    return 0;
}

void
fs_insert_filesystem(struct filesystem *filesystem)
{
    struct filesystem **fs;

    fs = fs_get_free_filesystem();

    if (!fs) {
        print("Problem inserting filesystem");
        while(1) {} /* TODO  system panic */
    }

    *fs = filesystem;
}

static void
fs_static_load()
{
    //fs_insert_filesystem(fat16_init());
}

void
fs_load()
{
    memset(filesystems, 0, sizeof(filesystems));
    fs_static_load();
}

void
fs_init()
{
    memset(file_descriptors, 0, sizeof(file_descriptors));
    fs_load();
}

static int
file_new_descriptor(struct file_descriptor **desc_out)
{
    int status = -ENOMEM;

    for (int i = 0; i < MAX_FILE_DESCRIPTORS; i++) {
        if (file_descriptors[i] == 0) {
            struct file_descriptor *desc = kzalloc(sizeof(struct file_descriptor));

            desc->index = i + 1;
            file_descriptors[i] = desc;
            *desc_out = desc;
            status = 0;
            break;
        }
    }

    return status;
}

static struct file_descriptor *
file_get_descriptor(int fd)
{
    if (fd <= 0 || fd >= MAX_FILE_DESCRIPTORS) {
        return 0;
    }

    int index = fd - 1; // descriptors start at 1

    return file_descriptors[index];
}

struct filesystem *
fs_resolve(struct disk *disk)
{
    struct filesystem *fs = 0;

    for (int i = 0; i < MAX_FILESYSTEMS; i++) {
        if (filesystems[i] != 0 && filesystems[i]->resolve(disk) == 0) {
            fs = filesystems[i];
            break;
        }
    }

    return fs;
}

int 
fopen(const char *filename, const char *mode)
{
    return -EIO;
}
