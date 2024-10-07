#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void error_throw(Compiler* compiler, ErrorLevel lvl, char* err)
{
    char* input_path = compiler->input_name;
    char* lvl_cstr = _error_cstr_from_level(lvl);

    Token tok = compiler->tokens[compiler->tok_ptr];

    fprintf(stderr, "\033[1m%s:%d,%d: %s\033[0m: %s\n", input_path, tok.line, tok.row, lvl_cstr, err);

    if (lvl == FATAL) {
	exit(1);
    }
}

/*
 * Private
*/
static const char* _error_cstr_from_level(ErrorLevel lvl)
{
    switch (lvl) {
    case FATAL:
	return "\033[31mFATAL\033";
    case WARNING:
	return "\033[34mWARNING\033";
    case INFO:
	return "\033[32mINFO\033";
    }
}
