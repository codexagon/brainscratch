#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "helpers.h"

#define MAX_TAPE_SIZE 30000

int interpret_file(uchar **data_pointer, uchar *tape, uchar *program, long filesize, bool debug_mode);

#endif
