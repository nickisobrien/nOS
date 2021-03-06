#include "common.h"
#include "idt.h"
#include "isr.h"

extern void idt_set(u32int); // set_dt.s

static void idt_set_gate(u8int,u32int,u16int,u8int);

idt_entry_t idt_entries[256];
idt_ptr_t	idt_ptr;

// map to 32-47
static void irq_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void init_idt()
{
	idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
	idt_ptr.base  = (u32int)&idt_entries;

	k_memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

	irq_remap();

	// irqs 8, 10-14 (inclusive) have error codes, the rest don't
	idt_set_gate( 0, (u32int)isr0 , 0x08, 0x8E); // Division By Zero Exception
	idt_set_gate( 1, (u32int)isr1 , 0x08, 0x8E); // Debug Exception
	idt_set_gate( 2, (u32int)isr2 , 0x08, 0x8E); // Non Maskable Interrupt Exception
	idt_set_gate( 3, (u32int)isr3 , 0x08, 0x8E); // Breakpoint Exception
	idt_set_gate( 4, (u32int)isr4 , 0x08, 0x8E); // Into Detected Overflow Exception
	idt_set_gate( 5, (u32int)isr5 , 0x08, 0x8E); // Out of Bounds Exception
	idt_set_gate( 6, (u32int)isr6 , 0x08, 0x8E); // Invalid Opcode Exception
	idt_set_gate( 7, (u32int)isr7 , 0x08, 0x8E); // No Coprocessor Exception
	idt_set_gate( 8, (u32int)isr8 , 0x08, 0x8E); // Double Fault Exception
	idt_set_gate( 9, (u32int)isr9 , 0x08, 0x8E); // Coprocessor Segment Overrun Exception
	idt_set_gate( 10, (u32int)isr10 , 0x08, 0x8E); // Bad TSS Exception
	idt_set_gate( 11, (u32int)isr11 , 0x08, 0x8E); // Segment Not Present Exception
	idt_set_gate( 12, (u32int)isr12 , 0x08, 0x8E); // Stack Fault Exception
	idt_set_gate( 13, (u32int)isr13 , 0x08, 0x8E); // General Protection Fault Exception
	idt_set_gate( 14, (u32int)isr14 , 0x08, 0x8E); // Page Fault Exception
	idt_set_gate( 15, (u32int)isr15 , 0x08, 0x8E); // Unknown Interrupt Exception
	idt_set_gate( 16, (u32int)isr16 , 0x08, 0x8E); // Coprocessor Fault Exception
	idt_set_gate( 17, (u32int)isr17 , 0x08, 0x8E); // Alignment Check Exception
	idt_set_gate( 18, (u32int)isr18 , 0x08, 0x8E); // Machine Check Exception
	idt_set_gate( 19, (u32int)isr19 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 20, (u32int)isr20 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 21, (u32int)isr21 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 22, (u32int)isr22 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 23, (u32int)isr23 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 24, (u32int)isr24 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 25, (u32int)isr25 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 26, (u32int)isr26 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 27, (u32int)isr27 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 28, (u32int)isr28 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 29, (u32int)isr29 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 30, (u32int)isr30 , 0x08, 0x8E); // Reserved Exceptions 19-31
	idt_set_gate( 31, (u32int)isr31 , 0x08, 0x8E); // Reserved Exceptions 19-31

	idt_set_gate( 32, (u32int)isr32 , 0x08, 0x8E); // timer?
	idt_set_gate( 33, (u32int)isr33 , 0x08, 0x8E); // keyboard?

	idt_set((u32int)&idt_ptr);
}

static void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

	idt_entries[num].sel = sel;
	idt_entries[num].always0 = 0;
	idt_entries[num].flags = flags;
}
