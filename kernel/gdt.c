#include "common.h"
#include "gdt.h"

#define GDT_ENTRIES 3

extern void gdt_set(u32int); // set_dt.s

gdt_entry_t gdt_entries[GDT_ENTRIES];
gdt_ptr_t	gdt_ptr;

// Set the value of one GDT entry
static void gdt_set_gate(s32int index, u32int base, u32int limit, u8int access, u8int gran)
{
	gdt_entries[index].base_low = base & 0xFFFF;
	gdt_entries[index].base_middle = (base >> 16) & 0xFF;
	gdt_entries[index].base_high = (base >> 24) & 0xFF;

	gdt_entries[index].limit_low = limit & 0xFFFF;

	gdt_entries[index].access = access;

	gdt_entries[index].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
}

void init_gdt()
{
	gdt_ptr.limit = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;
	gdt_ptr.base  = (u32int)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);					// Null segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);		// Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);		// Data segment
	// gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);	// User mode code segment
	// gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);	// User mode data segment
	gdt_set((u32int)&gdt_ptr);
}