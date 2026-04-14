#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>

typedef unsigned char uchar;

void print_memory_cells(uchar *dp, uchar *tape, long used_size);
bool is_valid_character(uchar c);
bool str_ends_with(const char *s, const char *end);

#endif
