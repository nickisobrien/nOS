#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "common.h"
#include "gdt.h"
#include "idt.h"
#include "terminal.h"

void k_main(void) 
{
	// initialize gdt and idt
	init_gdt();
	init_idt();

	// initialize terminal interface
	terminal_initialize();
	
 	const char *str = "Welcome to nOS!\n";

	k_putstr(str);
	asm volatile ("int $3");
	asm volatile ("int $4");
	// asm volatile ("int $32");
}
