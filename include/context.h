#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdlib.h>
#include "type.h"

#define MAX_STACK_SIZE 2000
#define MAX_INSTANCES 1000
#define MAX_ARGS 20

typedef struct {
    VarType type;
    char* name;
    size_t value;
    bool is_const;
    bool is_mem;
    size_t addr;
} Variable;

typedef struct {
    char* name;
    size_t arg_count;
    VarType args[MAX_ARGS];
    size_t addr;
} Function;

typedef struct {
    char* name;
    size_t addr;
    size_t offset;
} Memory;

typedef struct {
    char* name;
    VarType type;
} Binding;

typedef struct {
    size_t stmt_count;
    size_t literal_count;
    size_t func_count;
    size_t var_count;
    size_t memory_count;
    size_t temp_addr;
    Binding bindings[8];
    size_t binding_count;
    bool active_binding;
    size_t main_addr;
    size_t current_loop;
    TokenType stmts[MAX_STACK_SIZE];
    Variable vars[MAX_INSTANCES];
    Function funcs[MAX_INSTANCES];
    Memory memories[MAX_INSTANCES];
    char* literals[MAX_INSTANCES];
    char* cw_func;
} Context;

Context* context_init();
void context_free(Context* context);
void context_push(Context* context, TokenType type);
TokenType context_pop(Context* context);
Function context_func_by_name(Context* context, char* name);
Variable context_var_by_name(Context* context, char* name);
Memory context_mem_by_name(Context* context, char* name);

#endif // CONTEXT_H
