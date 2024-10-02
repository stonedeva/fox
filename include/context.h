#ifndef CONTEXT_H
#define CONTEXT_H

#include "lexer.h"

#define MAX_STACK_SIZE 200
#define MAX_VARIABLES 20
#define MAX_LITERALS 50

typedef struct {
    char* name;
    char* value;
} Variable;

typedef struct {
    size_t stack_count;
    size_t if_count;
    size_t literal_count;
    size_t var_count;
    TokenType stack[MAX_STACK_SIZE];
    size_t addr_counter;
    size_t block_counter;
    Variable vars[MAX_VARIABLES];
    char* literals[MAX_LITERALS];
} Context;

Context* context_init();
void context_free(Context* context);
void context_push(Context* context, TokenType type);
TokenType context_pop(Context* context);

#endif // CONTEXT_H
