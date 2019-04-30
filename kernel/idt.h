#ifndef __IDT_H
#define __IDT_H

// Interrupt gate
typedef struct idt_entry_struct
{
	u16int base_lo;			// The lower 16 bits of the address to jump to when this interrupt fires
	u16int sel;				// Kernel segment selector
	u8int  always0;			// Will always be zero
	u8int  flags;			// Optional flags
	u16int base_hi;			// Upper 16 bits of the address to jump to
} __attribute__((packed)) idt_entry_t;

// describes a pointer to array of interrupt handlers
// formatted for 'lidt'
typedef struct idt_ptr_struct
{
	u16int limit;
	u32int base; // The address of the first element in our idt_entry_t array
} __attribute__((packed)) idt_ptr_t;

void init_idt();

#endif