#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>
#include <stdio.h>

#include "tape.h"

typedef struct Program {
	bool show_status, show_program, debug_mode;
	uchar *program;
	long progsize;

	bool second_tape;
} Program;

bool str_ends_with(const char *s, const char *end);

#endif
