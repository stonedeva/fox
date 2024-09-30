#ifndef ERROR_H
#define ERROR_H

typedef struct {
    Compiler* compiler;
    char* file_path;
    size_t line;
} ErrorHandler;

typedef enum {
    FATAL,
    WARNING,
    INFO
} ErrorLevel;

void error_throw(ErrorHandler handler, ErrorLevel lvl, char* err);

#endif // ERROR_H
