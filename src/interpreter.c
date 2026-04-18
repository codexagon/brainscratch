#include <stdio.h>
#include <string.h>

#include "../include/interpreter.h"
#include "../include/tape.h"

void execute_opcode(char opcode, Tape *t1, Tape *t2, Program *pr) {
	Tape *t = pr->second_tape ? t2 : t1;
	switch (opcode) {
	case '+':
		++(*t->dp);
		break;
	case '-':
		--(*t->dp);
		break;
	case '>':
		if (t->dp - t->data < MAX_TAPE_SIZE - 1) {
			t->dp++;
			if (t->dp - t->data > t->used_size) {
				t->used_size = t->dp - t->data;
			}
		}
		break;
	case '<':
		if (t->dp - t->data > 0) {
			t->dp--;
		}
		break;
	case '.':
		putchar(*t->dp);
		if (pr->debug_mode) {
			printf("\n\n");
		}
		break;
	case ',':
		*t->dp = getchar();
		break;
	case '$':
		pr->second_tape = !pr->second_tape;
		break;
	}
}

void interpret_file(Tape *t1, Tape *t2, Program *pr) {
	Tape *t;

	for (int i = 0; i < pr->progsize; i++) {
		char c = pr->program[i];
		t = pr->second_tape ? t2 : t1;

		if (strchr("+-<>.,$", c) != NULL) {
			execute_opcode(c, t1, t2, pr);
		} else if (c == '[') {
			if (*t->dp == 0) {
				int depth = 1;
				while (depth > 0) {
					i++;
					if (pr->program[i] == '[') {
						depth++;
					} else if (pr->program[i] == ']') {
						depth--;
					}
				}
			}
		} else if (c == ']') {
			if (*t->dp != 0) {
				int depth = 1;
				while (depth > 0) {
					i--;
					if (pr->program[i] == ']') {
						depth++;
					} else if (pr->program[i] == '[') {
						depth--;
					}
				}
			}
		} else if (c == '?') {
			if (*t->dp == 0) {
				int depth = 1;
				while (depth > 0) {
					i++;
					if (pr->program[i] == '?') {
						depth++;
					} else if (pr->program[i] == ';') {
						depth--;
					}
				}
			}
		} else if (c >= '0' && c <= '9') {
			int num = 0;
			int j = i;
			while (pr->program[j] >= '0' && pr->program[j] <= '9') {
				num = num * 10 + (pr->program[j] - '0');
				j++;
			}
			i = j;

			char cn = pr->program[i];
			for (j = 0; j < num; j++) {
				if (strchr("+-<>.,$", cn) != NULL) {
					execute_opcode(cn, t1, t2, pr);
				}
			}
		}

		if (pr->debug_mode) {
			printf("Step %-5d:   '%c' | (tape %i) ", i + 1, c, pr->second_tape + 1);
			print_cells(t);
		}
	}
}
