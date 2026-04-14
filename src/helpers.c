#include <stdio.h>
#include <string.h>

#include "../include/helpers.h"

void print_memory_cells(uchar *dp, uchar *tape, long used_size) {
	for (int i = 0; i < used_size + 1; i++) {
		if (dp == &tape[i]) {
			printf("\033[32m(%i)\033[0m", tape[i]);
		} else {
			printf("[%i]", tape[i]);
		}
	}
	printf("\n");
}

bool is_valid_character(uchar c) { return strchr("+-,.[]<>?;", c) != NULL; }

bool str_ends_with(const char *s, const char *end) {
	if (!s || !end) {
		return false;
	}

	int l = strlen(s);
	int lend = strlen(end);

	if (lend > l) {
		return false;
	}

	return strncmp(s + l - lend, end, lend) == 0;
}
