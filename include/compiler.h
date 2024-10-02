#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"
#include "context.h"
#include "error.h"

typedef struct {
    Context* context;
    ErrorHandler* error;
    FILE* output;
    size_t tok_sz;
    size_t tok_ptr;
    size_t var_count;
    Token* tokens;
    bool has_entry;
} Compiler;


Compiler* compiler_init(char* output_path, Lexer* lexer, bool has_entry);
void compiler_free(Compiler* compiler);

void compiler_emit_binaryop(Compiler* compiler);
void compiler_emit_push(Compiler* compiler);
void compiler_emit_func(Compiler* compiler);
void compiler_emit_base(Compiler* compiler);
void compiler_emit(Compiler* compiler);
void compiler_assemble(Compiler* compiler, bool remove_tmp);

#endif // COMPILER_H
