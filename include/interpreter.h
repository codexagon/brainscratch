#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "helpers.h"
#include "tape.h"

void interpret_file(Tape *t1, Tape *t2, uchar *program, long filesize, bool debug_mode);

#endif
