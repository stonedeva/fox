#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void error_throw(Compiler* compiler, ErrorLevel lvl, char* err)
{
    char* input_path = compiler->input_name;
    Token tok = compiler->tokens[compiler->tok_ptr];

    error_from_parts(input_path, lvl, err, tok); 
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
	return "\033[35mWARNING\033";
    case INFO:
	return "\033[32mINFO\033";
    }
}

void error_from_parts(char* input_path, ErrorLevel lvl, char* err, Token tok)
{
    const char* lvl_cstr = _error_cstr_from_level(lvl);

    fprintf(stderr, "\033[1m%s:%d,%d: %s\033[0m: %s\n", input_path, tok.line, tok.row, lvl_cstr, err);
    if (lvl == FATAL) {
	exit(1);
    }
}
