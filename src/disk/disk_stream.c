#include "disk_stream.h"
#include "memory/heap/kheap.h"
#include "config.h"

struct disk_stream *
diskstream_new(int disk_id)
{
    struct disk *disk = disk_get(disk_id);
    if (!disk)
        return 0;
    
    struct disk_stream *stream = kzalloc(sizeof(struct disk_stream));
    stream->pos = 0;
    stream->disk = disk;
    return stream;
}

int
diskstream_seek(struct disk_stream *stream, int pos)
{
    stream->pos = pos;
    return 0;
}

int
diskstream_read(struct disk_stream *stream, void *out, int total)
{
    int status;
    int sector = stream->pos / SECTOR_SIZE;
    int offset = stream->pos % SECTOR_SIZE;
    char buf[SECTOR_SIZE];

    status = disk_read_block(stream->disk, sector, 1, buf);
    if (status < 0)
        goto done;

    int total_to_read = total > SECTOR_SIZE ? SECTOR_SIZE : total;

    for (int i = 0; i < total_to_read; i++) {
        *(char *)out++ = buf[offset + i];
    }

    stream->pos += total_to_read;
    if (total > SECTOR_SIZE)
        status = diskstream_read(stream, out, total - SECTOR_SIZE); // TODO this could overflow the stack

done:
    return status;
}

void
diskstream_close(struct disk_stream *stream)
{
    kfree(stream);
}
