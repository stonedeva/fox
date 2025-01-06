#include "type.h"
#include "error.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

TypeStack* typestack_init(Lexer* lexer)
{
    TypeStack* stack = (TypeStack*)malloc(sizeof(TypeStack));
    if (!stack) {
	fprintf(stderr, "ERROR: Unable to allocate TypeStack\n");
    }

    stack->filename = lexer->filename;
    stack->tok_sz = lexer->tok_sz;
    stack->tokens = lexer->tokens;
    stack->type_count = 0;

    return stack;
}

void typestack_free(TypeStack* stack)
{
    free(stack);
}

void typestack_push(TypeStack* stack, VarType type)
{
    stack->types[stack->type_count++] = type;
}

VarType typestack_pop(TypeStack* stack)
{
    VarType type = stack->types[stack->type_count - 1];
    stack->type_count--;
    return type;
}

char* typestack_cstr_from_type(VarType type) 
{
    switch (type) {
    case INTEGER: return "int";
    case BOOLEAN: return "bool";
    case POINTER: return "ptr";
    case BYTE: return "byte";
    default:
	assert(0 && "typestack_cstr_from_type(): Illegal VarType provided!\n");
    }
}

VarType typestack_type_from_cstr(const char* cstr)
{
    if (strcmp("int", cstr) == 0) {
	return INTEGER;
    } else if (strcmp("bool", cstr) == 0) {
	return BOOLEAN;
    } else if (strcmp("ptr", cstr) == 0) {
	return POINTER;
    } else if (strcmp("byte", cstr) == 0) {
	return BYTE;
    } else {
	return TYPE_INVALID;
    }
}
