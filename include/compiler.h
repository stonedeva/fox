#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"
#include "context.h"

typedef struct {
    Context* context;
    FILE* output;
    char* output_path;
    size_t tok_sz;
    size_t tok_ptr;
    size_t var_count;
    Token* tokens;
    bool has_entry;
    char* input_name;
    size_t mem_capacity;
} Compiler;


Compiler compiler_init(Context* context, char* output_path, Lexer* lexer, bool has_entry, size_t mem_capacity);
void compiler_free(Compiler* compiler);
void compiler_crossreference(Compiler* compiler);

void compiler_emit_binaryop(Compiler* compiler);
void compiler_emit_push(Compiler* compiler);
void compiler_emit_func(Compiler* compiler);
void compiler_emit_base(char* out_path, size_t main_addr);
void compiler_emit(Compiler* compiler);
void compiler_assemble(Compiler* compiler);

#endif // COMPILER_H
