#include "pmap.h"
#include "memory/heap/kheap.h"

static uint32_t *current_directory = 0;

void pmap_load_directory(uint32_t *directory);

struct pmap_chunk *
pmap_new_chunk(uint8_t flags)
{
    uint32_t *directory = kzalloc(sizeof(uint32_t) * PMAP_TOTAL_ENTRIES_PER_TABLE);

    int offset = 0;
    for (int i = 0; i < PMAP_TOTAL_ENTRIES_PER_TABLE; i++) {
        uint32_t *entry = kzalloc(sizeof(uint32_t) * PMAP_TOTAL_ENTRIES_PER_TABLE);

        for (int j = 0; j < PMAP_TOTAL_ENTRIES_PER_TABLE; j++) {
            entry[j] = (offset + (j * PMAP_PAGE_SIZE)) | flags;
        }

        offset += (PMAP_TOTAL_ENTRIES_PER_TABLE * PMAP_PAGE_SIZE);
        directory[i] = (uint32_t)entry | flags | PMAP_IS_WRITEABLE;
    }

    struct pmap_chunk *chunk = kzalloc(sizeof(struct pmap_chunk));

    chunk->directory_entry = directory;
    return chunk;
}

void
pmap_switch(uint32_t *directory)
{
    pmap_load_directory(directory);
    current_directory = directory;
}

uint32_t *
pmap_chunk_get_directory(struct pmap_chunk *chunk)
{
    return chunk->directory_entry;
}
