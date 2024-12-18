#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdlib.h>
#include "type.h"

#define MAX_STACK_SIZE 200
#define MAX_INSTANCES 100
#define MAX_ARGS 20

typedef struct {
    VarType type;
    char* name;
    size_t value;
    bool is_const;
} Variable;

typedef struct {
    char* name;
    size_t arg_count;
    VarType args[MAX_ARGS];
    size_t addr;
} Function;

typedef struct {
    char* name;
    char* value;
} Macro;

typedef struct {
    size_t stmt_count;
    size_t literal_count;
    size_t func_count;
    size_t var_count;
    size_t macro_count;
    size_t temp_addr;
    char* bindings[8];
    size_t binding_count;
    bool active_binding;
    size_t main_addr;
    TokenType stmts[MAX_STACK_SIZE];
    Variable vars[MAX_INSTANCES];
    Function funcs[MAX_INSTANCES];
    char* literals[MAX_INSTANCES];
    Macro macros[MAX_INSTANCES];
    char* cw_func;
} Context;

Context* context_init();
void context_free(Context* context);
void context_push(Context* context, TokenType type);
TokenType context_pop(Context* context);
Function context_func_by_name(Context* context, char* name);
Variable context_var_by_name(Context* context, char* name);

#endif // CONTEXT_H
