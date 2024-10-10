#include "type.h"
#include "error.h"
#include <stdlib.h>
#include <errno.h>

TypeStack* typestack_init(Lexer* lexer)
{
    TypeStack* stack = (TypeStack*)malloc(sizeof(TypeStack));
    if (!stack) {
	perror("Memory allocation failed for TypeStack");
	exit(1);
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

void typestack_evaluate(TypeStack* stack)
{
    char* filename = stack->filename;

    for (size_t i = 0; i < stack->tok_sz; i++) {
	Token tok = stack->tokens[i];

	VarType top = stack->types[stack->type_count - 1];
	VarType second = stack->types[stack->type_count - 2];

	switch (tok.type) {
	case TOK_NUMBER:
	    typestack_push(stack, INTEGER);
	    break;
	case TOK_BINARYOP:
	    (void) typestack_pop(stack);
	    (void) typestack_pop(stack);

	    char op = tok.token[0];
	    switch (op) {
	    case '=':
	    case '<':
	    case '>':
	    case '|':
	    case '&':
	    case '^':
	    case '!':
		typestack_push(stack, BOOLEAN);
		break;
	    default:
		typestack_push(stack, INTEGER);
		break;
	    }

	    break;
	case TOK_STRING_LITERAL:
	    typestack_push(stack, STRING);
	    typestack_push(stack, INTEGER);
	    break;
	case TOK_CONDITION:
	case TOK_DO:
	    VarType type = typestack_pop(stack);
	    if (type != BOOLEAN) {
		error_from_parts(filename, WARNING, "Trying condition with a non-boolean", tok);
	    }
	    break;
	case TOK_DUMP:
	    if (typestack_pop(stack) != INTEGER) {
		error_from_parts(filename, WARNING, "Trying to dump a non-integer", tok);
	    }
	    break;
	case TOK_SWAP:
	    if (!(top == INTEGER && second == INTEGER)) {
		error_from_parts(filename, WARNING, "Trying to swap a non-integer", tok);
	    }
	    break;
	case TOK_DROP:
	    VarType top = typestack_pop(stack);
	    if (top != INTEGER) {
		error_from_parts(filename, WARNING, "Trying to drop a non-integer", tok);
	    }
	    break;
	}
    }
}

void typestack_push(TypeStack* stack, VarType type)
{
    stack->types[stack->type_count] = type;
    stack->type_count++;
}

VarType typestack_pop(TypeStack* stack)
{
    VarType type = stack->types[stack->type_count - 1];
    stack->type_count--;
    return type;
}
