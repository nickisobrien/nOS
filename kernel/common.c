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

void	*k_memcpy(void *restrict str1, const void *restrict str2, u32int n)
{
	char *iter;
	char *citer;

	iter = str1;
	citer = (char *)str2;
	while (n > 0)
	{
		*iter = *citer;
		iter++;
		citer++;
		n--;
	}
	return (str1);
}

void	*k_memset(void *str, int c, size_t n)
{
	char *iter;

	iter = str;
	while (n > 0)
	{
		*iter = c;
		iter++;
		n--;
	}
	return (str);
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

