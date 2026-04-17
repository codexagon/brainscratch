#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>

#include "helpers.h"
#include "tape.h"

void execute_opcode(char opcode, Tape *t1, Tape *t2, Program *pr);
void interpret_file(Tape *t1, Tape *t2, Program *pr);

#endif
