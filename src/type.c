#include "type.h"
#include "error.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

TypeStack typestack_init(Lexer* lexer)
{
    TypeStack stack = {
	.filename = lexer->filename,
	.tok_sz = lexer->tok_sz,
	.tokens = lexer->tokens,
	.type_count = 0
    };
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
	case TOK_BINARYOP:
	    if (stack->type_count < 2) {
		error_from_parts(filename, WARNING, "Binaryop requires two values", tok);
	    }
	    VarType a = typestack_pop(stack);
	    VarType b = typestack_pop(stack);
	    
	    if (strcmp("==", tok.token) == 0 ||
		strcmp("!=", tok.token) == 0 ||
		strcmp("&&", tok.token) == 0 ||
		strcmp("||", tok.token) == 0) {

		typestack_push(stack, BOOLEAN);
		break;
	    }

	    if (tok.token[0] == '<' || tok.token[0] == '>') {
		typestack_push(stack, BOOLEAN);
		break;
	    }

	    if (a == POINTER || b == POINTER) {
		typestack_push(stack, POINTER);
		break;
	    }

	    typestack_push(stack, INTEGER);
	    break;
	case TOK_NUMBER:
	    typestack_push(stack, INTEGER);
	    break;
	case TOK_CONDITION:
	    break;
	case TOK_ELSE:
	    break;
	case TOK_LOOP:
	    break;
	case TOK_DO:
	    if (stack->type_count < 1) {
		error_from_parts(filename, FATAL, "Operation 'do' requires one argument", tok);
	    }
	    if (typestack_pop(stack) != BOOLEAN) {
		error_from_parts(filename, WARNING, "Trying operation 'do' with non-boolean", tok);
		break;
	    }
	    break;
	case TOK_PRINT:
	    if (stack->type_count < 1) {
		error_from_parts(filename, FATAL, "Trying operation 'print' with empty stack", tok);
	    }
	    (void) typestack_pop(stack);
	    break;
	case TOK_DUP:
	    if (stack->type_count < 1) {
		error_from_parts(filename, FATAL, "Trying operation 'dup' with empty stack", tok);
	    }
	    typestack_push(stack, stack->types[stack->type_count - 1]);
	    break;
	case TOK_SWAP:
	    if (stack->type_count < 2) {
		error_from_parts(filename, FATAL, "Operation 'swap' requires two arguments", tok);
	    }

	    a = typestack_pop(stack);
	    b = typestack_pop(stack);
	    typestack_push(stack, b);
	    typestack_push(stack, a);
	    break;
	case TOK_OVER:
	    if (stack->type_count < 2) {
		error_from_parts(filename, FATAL, "Operation 'over' requires two arguments", tok);
	    }
	    
	    typestack_push(stack, stack->types[stack->type_count - 2]);
	    break;
	case TOK_DROP:
	    (void) typestack_pop(stack);
	    break;
	case TOK_DEF_FUNC:
	    while (strcmp("in", stack->tokens[i].token) != 0) {
		i++;
	    }
	    break;
	case TOK_FUNC_CALL:
	    break;
	case TOK_VAR_REF:
	    typestack_push(stack, INTEGER);
	    break;
	case TOK_PTR_REF:
	    typestack_push(stack, POINTER); 
	    break;
	case TOK_PTR_SET8:
	case TOK_PTR_SET32:
	case TOK_PTR_SET64:
	    if (stack->type_count < 2) {
		error_from_parts(filename, FATAL, "Operation 'ptr-set' requires two arguments", tok);
	    }

	    (void) typestack_pop(stack);
	    (void) typestack_pop(stack);
	    break;
	case TOK_PTR_GET8:
	case TOK_PTR_GET32:
	case TOK_PTR_GET64:
	    if (stack->type_count < 1) {
		error_from_parts(filename, WARNING, "Operation 'ptr-get' requires one argument", tok);
		break;
	    }

	    (void) typestack_pop(stack);
	    typestack_push(stack, INTEGER);
	    break;
	case TOK_DEF_CONST:
	case TOK_DEF_MEM:
	case TOK_DEF_VAR:
	    while (strcmp("end", stack->tokens[i].token) != 0) {
		i++;
	    }
	    break;
	case TOK_REDEF_VAR:
	    (void) typestack_pop(stack);
	    break;
	case TOK_SYSCALL:
	    if (stack->type_count < 4) {
		error_from_parts(filename, FATAL, "Operation 'syscall' requires four arguments", tok);
	    }
	    for (size_t i = 0; i < 4; i++) {
		(void) typestack_pop(stack);
	    }
	    typestack_push(stack, INTEGER);

	    break;
	case TOK_RETURN:
	    (void) typestack_pop(stack);
	    break;
	case TOK_END:
	    break;
	case TOK_STRING_LITERAL:
	    typestack_push(stack, INTEGER);
	    typestack_push(stack, POINTER);
	    break;
	case TOK_IMPORT:
	    i++;
	    break;
	}
    }

    if (stack->type_count != 0) {
	Token tok = stack->tokens[stack->tok_sz - 1];
	error_from_parts(filename, INFO, "Unused data on the stack", tok);
    }
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
