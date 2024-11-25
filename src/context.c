#include "context.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Context* context_init()
{
    Context* context = (Context*)malloc(sizeof(Context));
    if (!context) {
	fprintf(stderr, "Memory allocation failed for Context\n");
	exit(1);
    }

    context->temp_addr = 0;
    context->main_addr = 0;
    context->func_count = 0;
    context->var_count = 0;
    context->literal_count = 0;
    context->stmt_count = 0;
}

void context_free(Context* context)
{
    free(context);
}

void context_push(Context* context, TokenType type)
{
    context->stmts[context->stmt_count] = type;
    context->stmt_count++;
}

TokenType context_pop(Context* context)
{
    if (context->stmt_count < 1) {
	return 0;
    }
    TokenType type = context->stmts[context->stmt_count - 1];
    context->stmt_count--;
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
