#include "type.h"
#include "error.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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

	switch (tok.type) {
	case TOK_NUMBER:
	    typestack_push(stack, INTEGER);
	    break;
	
	case TOK_BINARYOP:
	    VarType top_operand = typestack_pop(stack);
	    VarType sec_operand = typestack_pop(stack);

	    if (stack->type_count < 2) {
		error_from_parts(filename, FATAL, "Operation requires two values", tok);
	    }

	    if (strcmp("==", tok.token) == 0 ||
		strcmp("!=", tok.token) == 0 ||
		strcmp("&&", tok.token) == 0 ||
		strcmp("||", tok.token) == 0) {
		
		typestack_push(stack, BOOLEAN);
		break;
	    }

	    if (strcmp("<<", tok.token) == 0 ||
		strcmp(">>", tok.token) == 0) {

		typestack_push(stack, INTEGER);
		break;
	    }

	    switch (tok.token[0]) {
	    case '+':
	    case '-':
		if (top_operand == POINTER || 
		    sec_operand == POINTER) {

		    typestack_push(stack, POINTER);
		    continue;
		}
	    case '<':
	    case '>':
		typestack_push(stack, BOOLEAN);
		continue;
	    }

	    typestack_push(stack, INTEGER);
	    break;

	case TOK_VAR_REF:
	    typestack_push(stack, INTEGER);
	    break;
	
	case TOK_PTR_REF:
	    typestack_push(stack, POINTER);
	    break;
	
	case TOK_STRING_LITERAL:
	    typestack_push(stack, INTEGER);
	    typestack_push(stack, POINTER);
	    break;
	
	case TOK_DO:
	    if (typestack_pop(stack) != BOOLEAN) {
		error_from_parts(filename, WARNING, "Trying condition with a non-boolean", tok);
	    }
	    break;
	
	case TOK_DUMP:
	    if (typestack_pop(stack) != INTEGER) {
		error_from_parts(filename, WARNING, "Trying to dump a non-integer", tok);
	    }
	    break;
	
	case TOK_SWAP:
    	    VarType top = typestack_pop(stack);
	    VarType second = typestack_pop(stack);
	    typestack_push(stack, second);
	    typestack_push(stack, top);
	    break;
	
	case TOK_DUP:
	    typestack_push(stack, stack->types[stack->type_count - 1]);
	    break;
	
	case TOK_DROP:
	    (void) typestack_pop(stack);
	    break;
	
	case TOK_PTR_SET:
	    if (typestack_pop(stack) != INTEGER) {
		error_from_parts(filename, WARNING, "Trying to set a non-integer", tok);
	    }

	    if (typestack_pop(stack) != POINTER) {
		error_from_parts(filename, FATAL, "Memory address is not a pointer", tok);
	    }
	    break;
	
	case TOK_PTR_GET:
	    if (typestack_pop(stack) != POINTER) {
		error_from_parts(filename, FATAL, "Memory address is not a pointer", tok);
	    }
	    break;
	
	case TOK_RETURN:
	    (void) typestack_pop(stack);

	    if (stack->type_count != 0) {
		error_from_parts(filename, INFO, "Unused data on the stack from function", tok);
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
