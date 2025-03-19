#ifndef DEBUG_H
#define DEBUG_H

#include <stdarg.h>
#include <stdio.h>

void set_debug_level(int debug_level);
int dprintf(int debug_level, const char *fmt, ...);

#endif // DEBUG_H
