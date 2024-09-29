#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"

#define MAX_VARIABLES 20
#define MAX_LITERALS 20

typedef struct {
    char* name;
    char* value;
} Variable;

typedef struct {
    FILE* output;
    size_t tok_sz;
    size_t tok_ptr;
    size_t var_count;
    size_t literal_count;
    Token* tokens;
    Variable vars[MAX_VARIABLES];
    char* literals[MAX_LITERALS];
} Compiler;


Compiler* compiler_init(char* output_path, Token* tokens, size_t tok_sz);
void compiler_free(Compiler* compiler);

void compiler_emit_binaryop(Compiler* compiler);
void compiler_emit_push(Compiler* compiler);
void compiler_emit_func(Compiler* compiler);
void compiler_emit_base(Compiler* compiler);
void compiler_emit(Compiler* compiler);
void compiler_assemble(Compiler* compiler, bool remove_tmp);

#endif // COMPILER_H
