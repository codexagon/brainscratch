#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;

#define MAX_TAPE_SIZE 30000

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
		if (strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0) {
			debug_mode = true;
		}
		if (strcmp(argv[i], "--show-status") == 0) {
			show_status = true;
		}
	}

	fseek(bsfile, 0, SEEK_END);
	long filesize = ftell(bsfile);
	fseek(bsfile, 0, SEEK_SET);

	uchar *program = malloc(filesize + 1);

	fread(program, 1, filesize, bsfile);
	program[filesize] = '\0';

	uchar *tape = calloc(MAX_TAPE_SIZE, sizeof(char));
	uchar *dp = tape;

	int used_size = interpret_file(&dp, tape, program, filesize, debug_mode);

	fclose(bsfile);

	if (show_status) {
		printf("\nMemory cells status:\n");
		print_memory_cells(dp, tape, used_size);
	}

	free(tape);
	free(program);
	return 0;
}
