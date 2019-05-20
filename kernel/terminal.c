#include "terminal.h"
#include "common.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer = (uint16_t *)0xB8000;
 
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
 
static inline void vga_set_color(enum vga_color fg, enum vga_color bg) 
{
	terminal_color = fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc) 
{
	return (uint16_t) uc | (uint16_t) terminal_color << 8;
}

static inline uint16_t get_index(size_t x, size_t y)
{
	return y * VGA_WIDTH + x;
}

static void terminal_putentryat(char c, size_t x, size_t y) 
{
	terminal_buffer[get_index(x, y)] = vga_entry(c);
}

void terminal_initialize(void) 
{
	terminal_row = VGA_HEIGHT-1;
	terminal_column = 0;
	vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			terminal_buffer[get_index(x, y)] = vga_entry(' ');
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
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
		terminal_buffer[i] = vga_entry(' ');
	}
}

void terminal_clear(void)
{
	for (uint16_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
	{
		terminal_putchar(' ');
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
	terminal_putentryat(c, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		terminal_scroll();
	}
}
