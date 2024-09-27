#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"

typedef struct {
    char* name;
    char* value;
} Variable;

typedef struct {
    FILE* output;
    size_t tok_sz;
    size_t tok_ptr;
    size_t var_count;
    Token* tokens;
    Variable vars[];
} Compiler;


Compiler* compiler_init(char* output_path, Token* tokens, size_t tok_sz);
void compiler_free(Compiler* compiler);

void compiler_emit_binaryop(Compiler* compiler);
void compiler_emit_push(Compiler* compiler);
void compiler_emit_function(Compiler* compiler);
void compiler_emit_base(Compiler* compiler);
void compiler_emit(Compiler* compiler);
void compiler_assemble(Compiler* compiler, bool remove_tmp);

#endif // COMPILER_H
