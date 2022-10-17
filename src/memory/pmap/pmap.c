#include "pmap.h"
#include "memory/heap/kheap.h"
#include "status.h"

extern void pmap_load_directory(uint32_t *directory);

static uint32_t *current_directory = 0;

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

int
pmap_is_aligned(void *addr)
{
    return ((uint32_t)addr % PMAP_PAGE_SIZE) == 0;
}

int
pmap_get_indexes(void *va, uint32_t *directory_index_out, uint32_t *table_index_out)
{
    int status = 0;

    if (!pmap_is_aligned(va)) {
        status = -EINVARG;
        goto done;
    }

    *directory_index_out = (uint32_t) va / (PMAP_TOTAL_ENTRIES_PER_TABLE * PMAP_PAGE_SIZE);
    *table_index_out = (uint32_t) va % ((PMAP_TOTAL_ENTRIES_PER_TABLE * PMAP_PAGE_SIZE) / PMAP_PAGE_SIZE);

done:
    return status;
}

int
pmap_set(uint32_t *directory, void *va, uint32_t val)
{
    int status = 0;

    if (!pmap_is_aligned(va)) {
        return -EINVARG;
    }

    uint32_t directory_index = 0;
    uint32_t table_index = 0;

    status = pmap_get_indexes(va, &directory_index, &table_index);
    if (status < 0)
        return status;

    uint32_t directory_entry = directory[directory_index];
    uint32_t *table_addr = (uint32_t *)(directory_entry & 0xfffff000);

    table_addr[table_index] = val;

    return status;
}
