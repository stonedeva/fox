#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"
#include "context.h"

#define MAX_VARIABLES 20
#define MAX_LITERALS 50
#define MAX_RETURN_STACK 50

typedef struct {
    char* name;
    char* value;
} Variable;

typedef struct {
    Context* context;
    FILE* output;
    size_t tok_sz;
    size_t tok_ptr;
    size_t var_count;
    size_t literal_count;
    size_t return_stack_count;
    Token* tokens;
    Variable vars[MAX_VARIABLES];
    char* literals[MAX_LITERALS];
    bool has_entry;
    int return_stack[MAX_RETURN_STACK];
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
