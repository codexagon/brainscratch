#include <stdbool.h>
#include <stdio.h>

#include "../include/interpreter.h"
#include "../include/tape.h"

void interpret_file(Tape *t1, Tape *t2, uchar *program, long filesize, bool debug_mode) {
	int tape_pos[2] = {0, 0};

	bool second = false;
	Tape *t;

	for (int i = 0; i < filesize; i++) {
		char c = program[i];
		if (second) {
			t = t2;
		} else {
			t = t1;
		}

		if (c == '+') {
			++(*t->dp);
		} else if (c == '-') {
			--(*t->dp);
		} else if (c == '>') {
			if (tape_pos[second] < MAX_TAPE_SIZE - 1) {
				t->dp++;
				tape_pos[second]++;
				if (tape_pos[second] > t->used_size) {
					t->used_size = tape_pos[second];
				}
			}
		} else if (c == '<') {
			if (tape_pos[second] > 0) {
				t->dp--;
				tape_pos[second]--;
			}
		} else if (c == '.') {
			putchar(*t->dp);
			if (debug_mode) {
				printf("\n\n");
			}
		} else if (c == ',') {
			*t->dp = getchar();
		} else if (c == '[') {
			if (*t->dp == 0) {
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
			if (*t->dp != 0) {
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
			if (*t->dp == 0) {
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
		} else if (c == '$') {
			second = !second;
		} else if (c >= '0' && c <= '9') {
			int num = 0;
			int j = i;
			while (program[j] >= '0' && program[j] <= '9') {
				num = num * 10 + (program[j] - '0');
				j++;
			}
			i = j;

			char cn = program[i];
			for (j = 0; j < num; j++) {
				if (cn == '+') {
					++(*t->dp);
				} else if (cn == '-') {
					--(*t->dp);
				} else if (cn == '>') {
					if (tape_pos[second] < MAX_TAPE_SIZE - 1) {
						t->dp++;
						tape_pos[second]++;
						if (tape_pos[second] > t->used_size) {
							t->used_size = tape_pos[second];
						}
					}
				} else if (cn == '<') {
					if (tape_pos[second] > 0) {
						t->dp--;
						tape_pos[second]--;
					}
				} else if (cn == '.') {
					putchar(*t->dp);
					if (debug_mode) {
						printf("\n\n");
					}
				}
			}
		}

		if (debug_mode) {
			printf("Step %-5d:   '%c' | ", i + 1, c);
			print_cells(t);
		}
	}
}
