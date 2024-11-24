#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include "lexer.h"
#include "type.h"
#include "compiler.h"

typedef enum {
    FATAL,
    WARNING,
    INFO
} ErrorLevel;

void error_throw(Compiler* compiler, ErrorLevel lvl, char* err);
void error_from_parts(char* input_path, ErrorLevel lvl, char* err, Token tok);

/*
 * Private
*/
static const char* _error_cstr_from_level(ErrorLevel lvl);

#endif // ERROR_H
