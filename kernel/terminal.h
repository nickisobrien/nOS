#ifndef __TERMINAL_H
#define __TERMINAL_H

#include "common.h"
void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_scroll(void);
void terminal_clear(void);
void terminal_putchar(char c);

#endif