#include "error.h"
#include <stdio.h>
#include <stdlib.h>

ErrorHandler* error_init(char* input_path)
{
    ErrorHandler* handler = (ErrorHandler*)malloc(sizeof(ErrorHandler));
    if (!handler) {
	fprintf(stderr, "Memory allocation failed for ErrorHandler\n");
	exit(1);
    }

    handler->input_path = input_path;

    return handler;
}

void error_free(ErrorHandler* handler)
{
    free(handler);
}

void error_throw(ErrorHandler* handler, ErrorLevel lvl, char* err, char* token)
{
    char* input_path = handler->input_path;
    char* lvl_cstr = _error_cstr_from_level(lvl);

    fprintf(stderr, "%s: %s: %s '%s'\n", input_path, lvl_cstr, err, token);

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
	return "FATAL";
    case WARNING:
	return "WARNING";
    case INFO:
	return "INFO";
    }
}
