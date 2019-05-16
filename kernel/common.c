// some klib stuff (needs to be better organized)
#include "common.h"

// write to ports
void outb(u16int port, u8int value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
	u8int ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}


u16int inw(u16int port)
{
	u16int ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

u32int k_strlen(const char *str)
{
	u32int i = 0;
	while (str[i++])
		;
	return i;
}

void	*k_memcpy(void *dest, const void *src, u32int n)
{
	while (n)
	{
		((char *)dest)[n] = ((char *)src)[n];
		n--;
	}
	return dest;
}

void	*k_memset(void *dest, int c, size_t n)
{
	while (n)
		((char *)dest)[n--] = (char)c;
	return (dest);
}

void	k_putnbr(int nb)
{
	if (nb < 0)
	{
		terminal_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
	{
		k_putnbr(nb / 10);
		k_putnbr(nb % 10);
	}
	else
		terminal_putchar(nb + '0');
}

