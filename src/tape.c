#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/tape.h"

void init_tape(Tape *t) {
	t->data = calloc(MAX_TAPE_SIZE, sizeof(uchar));
	t->dp = t->data;
	t->used_size = 1;
	t->selected = false;
}

void print_cells(Tape *t) {
	for (int i = 0; i < t->used_size + 1; i++) {
		if (t->dp == &t->data[i]) {
			printf("\033[32m(%i)\033[0m", t->data[i]);
		} else {
			printf("[%i]", t->data[i]);
		}
	}
	printf("\n");
}
