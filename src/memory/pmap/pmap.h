#ifndef PMAP_H
#define PMAP_H

#include <stdint.h>
#include <stddef.h>

#define PMAP_CACHE_DISABLED  0b00010000
#define PMAP_WRITE_THROUGH   0b00001000
#define PMAP_ACCESS_FROM_ALL 0b00000100
#define PMAP_IS_WRITEABLE    0b00000010
#define PMAP_IS_PRESENT      0b00000001

#define PMAP_TOTAL_ENTRIES_PER_TABLE 1024
#define PMAP_PAGE_SIZE 4096

struct pmap_chunk {
    uint32_t *directory_entry;
};

struct pmap_chunk *pmap_new_chunk(uint8_t flags);
void pmap_switch(uint32_t *directory);
extern void pmap_enable();

int pmap_set(uint32_t *directory, void *va, uint32_t val);
int pmap_is_aligned(void *addr);
uint32_t *pmap_chunk_get_directory(struct pmap_chunk *chunk);

#endif // PMAP_H
