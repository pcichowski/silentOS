#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_desc {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_2;
} __attribute__((packed));

struct idtr_desc {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_init();
void enable_interrupts();
void disable_interrupts();

#endif // IDT_H
