#include "context.h"
#include <stdlib.h>
#include <stdio.h>

Context* context_init()
{
    Context* context = (Context*)malloc(sizeof(Context));
    if (!context) {
	fprintf(stderr, "Memory allocation failed for Context\n");
	exit(1);
    }

    context->if_count = 0;
    context->loop_count = 0;
    context->literal_count = 0;
    context->func_count = 0;
    context->addr_count = 0;
    context->block_count = 0;
    context->var_count = 0;
    context->literal_count = 0;
    context->stack_count = 0;
}

void context_free(Context* context)
{
    free(context);
}

void context_push(Context* context, TokenType type)
{
    context->stack[context->stack_count] = type;
    context->stack_count++;
}

TokenType context_pop(Context* context)
{
    TokenType type = context->stack[context->stack_count - 1];
    context->stack_count--;
    return type;
}

Function context_func_by_name(Context* context, char* name)
{
    for (size_t i = 0; i < context->func_count; i++) {
	Function func = context->funcs[i];
	if (strcmp(name, func.name) == 0) {
	    return func;
	}
    }

    return (Function) {};
}
