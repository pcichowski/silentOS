#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stddef.h>

void kheap_init();
void *kmalloc(size_t size);
void kfree(void *ptr);

#endif //  HEAP_H
