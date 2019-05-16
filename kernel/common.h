#ifndef __COMMON_H
#define __COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// typedefs are written for 32 bit X86
typedef	unsigned int u32int;
typedef	int s32int;
typedef unsigned short u16int;
typedef	short s16int;
typedef unsigned char u8int;
typedef	char s8int;

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);
u32int k_strlen(const char *str);
void *k_memcpy(void *str1, const void *str2, u32int n);
void *k_memset(void *dest, int c, size_t n);
void k_putnbr(int nb);
void terminal_writestring(const char* data);
void terminal_putchar(char c);

#endif