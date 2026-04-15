#ifndef TAPE_H
#define TAPE_H

typedef unsigned char uchar;

#define MAX_TAPE_SIZE 30000

typedef struct Tape {
	uchar *data;
	uchar *dp;
	int used_size;
	bool selected;
} Tape;

void init_tape(Tape *t);
void print_cells(Tape *t);

#endif
