#include "isr.h"
#include "common.h"

// common isr handler function
void isr_handler(registers_t *regs)
{
 	const char *str = "Interrupt: ";
	terminal_writestring(str);
	// if (regs->int_no == 0x3)
	// {
	k_putnbr(regs->int_no);
	// }
	terminal_putchar('\n');
	// const char *str = "Handling error\n";
	// terminal_writestring(str);
}
