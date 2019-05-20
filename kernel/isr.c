#include "isr.h"
#include "common.h"

// common isr handler function
void isr_handler(registers_t *regs)
{
 	const char *str = "Interrupt: ";
	k_putstr(str);
	k_putnbr(regs->int_no);
	k_putstr("\n");
}
