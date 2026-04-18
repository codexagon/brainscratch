#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/helpers.h"
#include "../include/interpreter.h"

void init_program(Program *p, FILE *bsfile) {
	p->show_status = false;
	p->show_program = false;
	p->debug_mode = false;

	p->progsize = 0;

	fseek(bsfile, 0, SEEK_END);
	long filesize = ftell(bsfile);
	fseek(bsfile, 0, SEEK_SET);

	p->program = malloc(filesize + 1);

	p->second_tape = false;
}

void close_program(Program *p) { free(p->program); }

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <file> [options]", argv[0]);
		return 1;
	}

	FILE *bsfile = NULL;
	for (int i = 1; i < argc; i++) {
		if (str_ends_with(argv[i], ".bs")) {
			bsfile = fopen(argv[i], "r");
		}
	}
	if (bsfile == NULL) {
		printf("Could not read file.\n");
		return 2;
	}

	Program p;
	init_program(&p, bsfile);

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--debug") == 0) {
			p.debug_mode = true;
		} else if (strcmp(argv[i], "--show-status") == 0) {
			p.show_status = true;
		} else if (strcmp(argv[i], "--show-program") == 0) {
			p.show_program = true;
		} else if (argv[i][0] == '-') {
			for (int j = 0; argv[i][j] != '\0'; j++) {
				if (argv[i][j] == 'd') {
					p.debug_mode = true;
				} else if (argv[i][j] == 's') {
					p.show_status = true;
				} else if (argv[i][j] == 'p') {
					p.show_program = true;
				}
			}
		}
	}

	int c = 0;
	while ((c = fgetc(bsfile)) != EOF) {
		if (c == '#') {
			while (strchr("\r\n", fgetc(bsfile)) == NULL) {
				continue;
			}
		} else if (!isspace(c)) {
			p.program[p.progsize++] = (uchar)c;
		}
	}

	p.program[p.progsize] = '\0';

	Tape tape1, tape2;
	init_tape(&tape1);
	init_tape(&tape2);

	if (p.show_program) {
		printf("Program:\n%s\n\n", p.program);
	}

	interpret_file(&tape1, &tape2, &p);

	fclose(bsfile);
	printf("\n");

	if (p.show_status) {
		printf("\nMemory cells status:\n");
		printf("Tape 1: ");
		print_cells(&tape1);
		printf("Tape 2: ");
		print_cells(&tape2);
	}

	free(tape1.data);
	free(tape2.data);

	close_program(&p);
	return 0;
}
