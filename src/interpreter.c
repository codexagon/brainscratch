#include <stdbool.h>
#include <stdio.h>

#include "../include/helpers.h"
#include "../include/interpreter.h"

int interpret_file(uchar **data_pointer, uchar *tape, uchar *program, long filesize, bool debug_mode) {
	uchar *dp = *data_pointer;
	int tape_pos = 0;
	int max_used = 0;

	for (int i = 0; i < filesize; i++) {
		char c = program[i];
		if (!is_valid_character(c)) {
			continue;
		}

		if (c == '+') {
			++(*dp);
		} else if (c == '-') {
			--(*dp);
		} else if (c == '>') {
			if (tape_pos < MAX_TAPE_SIZE - 1) {
				dp++;
				tape_pos++;
				if (tape_pos > max_used) {
					max_used = tape_pos;
				}
			}
		} else if (c == '<') {
			if (tape_pos > 0) {
				dp--;
				tape_pos--;
			}
		} else if (c == '.') {
			putchar(*dp);
			if (debug_mode) {
				printf("\n\n");
			}
		} else if (c == ',') {
			*dp = getchar();
		} else if (c == '[') {
			if (*dp == 0) {
				int depth = 1;
				while (depth > 0) {
					i++;
					if (program[i] == '[') {
						depth++;
					} else if (program[i] == ']') {
						depth--;
					}
				}
			}
		} else if (c == ']') {
			if (*dp != 0) {
				int depth = 1;
				while (depth > 0) {
					i--;
					if (program[i] == ']') {
						depth++;
					} else if (program[i] == '[') {
						depth--;
					}
				}
			}
		} else if (c == '?') {
			if (*dp == 0) {
				int depth = 1;
				while (depth > 0) {
					i++;
					if (program[i] == '?') {
						depth++;
					} else if (program[i] == ';') {
						depth--;
					}
				}
			}
		}

		if (debug_mode) {
			printf("Step %-5d:   '%c' | ", i + 1, c);
			print_memory_cells(dp, tape, max_used);
		}
	}

	*data_pointer = dp;
	return max_used;
}
