#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/helpers.h"
#include "../include/interpreter.h"

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

	bool show_status = false;
	bool debug_mode = false;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--debug") == 0) {
			debug_mode = true;
		} else if (strcmp(argv[i], "--show-status") == 0) {
			show_status = true;
		} else if (argv[i][0] == '-') {
			for (int j = 0; argv[i][j] != '\0'; j++) {
				if (argv[i][j] == 'd') {
					debug_mode = true;
				} else if (argv[i][j] == 's') {
					show_status = true;
				}
			}
		}
	}

	fseek(bsfile, 0, SEEK_END);
	long filesize = ftell(bsfile);
	fseek(bsfile, 0, SEEK_SET);

	uchar *program = malloc(filesize + 1);

	fread(program, 1, filesize, bsfile);
	program[filesize] = '\0';

	Tape tape;
	init_tape(&tape);

	interpret_file(&tape, program, filesize, debug_mode);

	fclose(bsfile);

	if (show_status) {
		printf("\nMemory cells status:\n");
		print_cells(&tape);
	}

	free(tape.data);
	free(program);
	return 0;
}
