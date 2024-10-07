#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include "lexer.h"
#include "compiler.h"

typedef enum {
    FATAL,
    WARNING,
    INFO
} ErrorLevel;

void error_throw(Compiler* compiler, ErrorLevel lvl, char* err);

/*
 * Private
*/
static const char* _error_cstr_from_level(ErrorLevel lvl);

#endif // ERROR_H
