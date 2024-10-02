#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>

typedef struct {
    char* input_path;
    size_t line;
} ErrorHandler;

typedef enum {
    FATAL,
    WARNING,
    INFO
} ErrorLevel;

ErrorHandler* error_init(char* input_path);
void error_free(ErrorHandler* handler);
void error_throw(ErrorHandler* handler, ErrorLevel lvl, char* err, char* token);

/*
 * Private
*/
static const char* _error_cstr_from_level(ErrorLevel lvl);

#endif // ERROR_H
