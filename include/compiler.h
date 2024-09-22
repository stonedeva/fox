#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE* output;
    char** tokens;
    size_t tok_sz;
    size_t tok_ptr;
} Compiler;


Compiler* compiler_init(char* output_path, char** tokens, size_t tok_sz);
void compiler_free(Compiler* compiler);

#endif // COMPILER_H
