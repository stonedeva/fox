#ifndef CONTEXT_H
#define CONTEXT_H

#include "lexer.h"

#define MAX_STACK_SIZE 200

typedef struct {
    size_t stack_count;
    size_t if_count;
    TokenType stack[MAX_STACK_SIZE];
    char* func_name;
} Context;

Context* context_init();
void context_free(Context* context);
void context_push(Context* context, TokenType type);
TokenType context_pop(Context* context);

#endif // CONTEXT_H
