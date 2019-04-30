#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "common.h"
#include "gdt.h"
#include "idt.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer = (uint16_t *)0xB8000;
uint16_t *cursor = (uint16_t *)0x3D4;
 
/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

static inline uint16_t get_index(size_t x, size_t y)
{
	return y * VGA_WIDTH + x;
}
 
void terminal_initialize(void) 
{
	terminal_row = VGA_HEIGHT-1;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			terminal_buffer[get_index(x, y)] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	terminal_buffer[get_index(x, y)] = vga_entry(c, color);
}

void terminal_scroll(void)
{
	uint16_t i = 0;
	for (; i < VGA_WIDTH * VGA_HEIGHT - VGA_WIDTH; i++)
	{
		terminal_buffer[i] = terminal_buffer[i + VGA_WIDTH];
	}
	for (; i < VGA_WIDTH * VGA_HEIGHT; i++)
	{
		terminal_buffer[i] = vga_entry(' ', terminal_color);
	}
}

void terminal_clear(void)
{
	for (uint16_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
	{
		terminal_buffer[i] = vga_entry(' ', terminal_color);
	}
}

void terminal_putchar(char c) 
{
	if (c == '\n')
	{
		terminal_column = 0;
		terminal_scroll();
		return ;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		terminal_scroll();
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, k_strlen(data));
}

void terminal_disable_cursor(void)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void kernel_main(void) 
{
	// initialize gdt and idt
	init_gdt();
	init_idt();

	// initialize terminal interface
	terminal_initialize();
	
 	const char *str = "Hello world!\n";

	terminal_writestring(str);
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");
}
