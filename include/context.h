#ifndef CONTEXT_H
#define CONTEXT_H

#include "lexer.h"

#define MAX_STACK_SIZE 200
#define MAX_INSTANCES 100
#define MAX_ARGS 20

typedef struct {
    char* name;
    char* value;
} Variable;

typedef struct {
    char* name;
    size_t arg_count;
    char* args[MAX_ARGS];
} Function;

typedef struct {
    size_t stack_count;
    size_t if_count;
    size_t loop_count;
    size_t literal_count;
    size_t var_count;
    size_t func_count;
    TokenType stack[MAX_STACK_SIZE];
    size_t addr_count;
    size_t block_count;
    size_t temp_addr;
    Variable vars[MAX_INSTANCES];
    Function funcs[MAX_INSTANCES];
    char* literals[MAX_INSTANCES];
} Context;

Context* context_init();
void context_free(Context* context);
void context_push(Context* context, TokenType type);
TokenType context_pop(Context* context);
Function context_func_by_name(Context* context, char* name);

#endif // CONTEXT_H
