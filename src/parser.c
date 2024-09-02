#include "parser.h"
#include "compiler.h"
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

static size_t pointer_copy = 0;

parser_t parser_init(lexer_t* lexer) {
    parser_t parser;
    parser.lexer = lexer;
    parser.expressions = vector_init(MAX_EXPRESSIONS);
    parser.inside_parameters = false;
    parser.expression_count = 0;
    parser.variable_map = hashtable_create(100);

    return parser;
}

void parser_delete(parser_t* parser) {
    for (size_t i = 0; i < parser->expressions->size; i++) {
        expression_t* wrapped_expr = (expression_t*)vector_get(parser->expressions, i);
        if (wrapped_expr == NULL) continue;

        switch (wrapped_expr->type) {
            case VARIABLE_EXPR: {
                variable_expr_t* var = (variable_expr_t*)wrapped_expr->expr;
                if (var) {
                    if (var->value) {
			free(var->value);
			var->value = NULL;
		    }

		    free(var);
		    var = NULL;
                }
                break;
            }
            case FUNCTION_EXPR: {
                function_expr_t* func = (function_expr_t*)wrapped_expr->expr;
                if (func) {
                    for (size_t j = 0; j < 0; j++) {
                        variable_expr_t* arg = (variable_expr_t*)vector_get(func->arguments, j);
                        if (arg) {
                            free(arg);
			    arg = NULL;
                        }
                    }
                    vector_delete(func->arguments);
                    vector_delete(func->tokens);
                    free(func->name);
                    free(func);
		    
		    func->name = NULL;
		    func->arguments = NULL;
		    func->tokens = NULL;
		    func = NULL;
                }
                break;
            }
            case SYSCALL_EXPR: {
                syscall_expr_t* syscall = (syscall_expr_t*)wrapped_expr->expr;
                if (syscall) {
		    free(syscall);
		    syscall = NULL;
		}
		break;
            }
            case MACRO_EXPR: {
                char* macro = (char*)wrapped_expr->expr;
                if (macro) {
		    free(macro);
		    macro = NULL;
		}
		break;
            }
            default:
                free(wrapped_expr->expr); // Free unknown expression types safely
                break;
        }
        free(wrapped_expr); // Free the wrapper expression itself
    }

    vector_delete(parser->expressions);
    parser->lexer = NULL;
}


void parser_evaluate(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t size = tokens->size;

    while (tokens->pointer < size) {
        char* current_tok = data[pointer_copy];

	if (lexer_compare(current_tok, "proc")) {
	    parser_evaluate_function(parser, BIT8_INT_DATATYPE);
	} else if (lexer_compare(current_tok, "syscall")) {
	    parser_evaluate_syscall(parser);
	} else if (_parser_evaluate_datatype(current_tok) != INVALID_DATATYPE) {
	    char datatype = _parser_evaluate_datatype(current_tok);
	    parser_evaluate_variable(parser, datatype);
	} /*else if (lexer_compare(current_tok, ";")) {
	    pointer_copy++;
	    continue;
	}*/


	// Calculation
	switch (data[tokens->pointer][0]) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	    parser_evaluate_calculation(parser);
	    break;
	default:
	    break;
	}

	tokens->pointer++;
	pointer_copy++;
    }

    _parser_print_expressions(parser);
    compiler_init(parser, "hello.ll");

//    parser_delete(parser);
}

static char _parser_evaluate_datatype(char* str) {
    if (lexer_compare("int8", str))
        return BIT8_INT_DATATYPE;
    else if (lexer_compare("int16", str))
        return BIT16_INT_DATATYPE;
    else if (lexer_compare("int32", str))
        return BIT32_INT_DATATYPE;
    else if (lexer_compare("int64", str))
        return BIT64_INT_DATATYPE;
    else if (lexer_compare("float32", str))
        return FLOAT32_DATATYPE;
    else if (lexer_compare("float64", str))
        return FLOAT64_DATATYPE;
    else if (lexer_compare("string", str))
        return STRING_DATATYPE;
        
    return INVALID_DATATYPE;
}

static void _parser_throw_error(parser_t* parser, char* error) {
    char* filename = parser->lexer->filename;

    fprintf(stderr, "[1m%s:%d[0m: \033[31mERROR[0m: %s!\n", filename, parser->lexer->line_count, error);
    exit(1);
}

void parser_evaluate_variable(parser_t* parser, char datatype) {
    variable_expr_t* variable_expr = (variable_expr_t*)malloc(sizeof(variable_expr_t));
    if (!variable_expr)
        _parser_throw_error(parser, "Memory allocation failed for variable_expr");

    memset(variable_expr, 0, sizeof(variable_expr_t));

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    char* name;
    
    if (lexer_compare(data[pointer + 1], "const")) {
	variable_expr->is_constant = true;
	name = data[pointer + 2];
    } else {
	name = data[pointer + 1];
	variable_expr->is_constant = false;
    }

    pointer++; // Skip '=' sign
    
    int value_int;
    char* value_str;
    if (datatype == STRING_DATATYPE)
	value_str = data[pointer + 3];
    else
	value_int = atoi(data[pointer + 3]);

    if (name == NULL)
        _parser_throw_error(parser, "expected name after 'var' expression"); 

    variable_expr->name = strdup(name);
    variable_expr->datatype = datatype;

    switch (datatype) {
    case BIT8_INT_DATATYPE:
        variable_expr->value = malloc(sizeof(uint8_t));
        *(uint8_t*)variable_expr->value = (uint8_t)atoi(data[pointer + 3]);
        break;
    case BIT16_INT_DATATYPE:
        variable_expr->value = malloc(sizeof(uint16_t));
        *(uint16_t*)variable_expr->value = (uint16_t)atoi(data[pointer + 3]);
        break;
    case BIT32_INT_DATATYPE:
        variable_expr->value = malloc(sizeof(uint32_t));
        *(uint32_t*)variable_expr->value = (uint32_t)atoi(data[pointer + 3]);
        break;
    case BIT64_INT_DATATYPE:
        variable_expr->value = malloc(sizeof(uint64_t));
        *(uint64_t*)variable_expr->value = (uint64_t)atoll(data[pointer + 3]);
        break;
    case FLOAT32_DATATYPE:
        variable_expr->value = malloc(sizeof(float));
        *(float*)variable_expr->value = atof(data[pointer + 3]);
        break;
    case FLOAT64_DATATYPE:
        variable_expr->value = malloc(sizeof(double));
        *(double*)variable_expr->value = atof(data[pointer + 3]);
        break;
    case STRING_DATATYPE:
        variable_expr->value = strdup(data[pointer + 3]);
        break;
    default:
        free(variable_expr);
	variable_expr = NULL;
        _parser_throw_error(parser, "Invalid datatype for variable");
        return;
    }

    bool inserted = hashtable_insert(parser->variable_map, variable_expr->name, variable_expr);
    if (!inserted) {
	free(variable_expr->name);
	free(variable_expr->value);
	free(variable_expr);
	variable_expr = NULL;

	_parser_throw_error(parser, "Failed to insert variable into hash table");
    }

    expression_t* expr_wrapper = (expression_t*)malloc(sizeof(expression_t));
    if (!expr_wrapper)
	_parser_throw_error(parser, "Memory allocation failed for expr_wrapper");

    expr_wrapper->type = VARIABLE_EXPR;
    expr_wrapper->expr = variable_expr;

    vector_push(parser->expressions, expr_wrapper);
    parser->expression_count++;
}

void parser_evaluate_function(parser_t* parser, char datatype) {
    function_expr_t* function_expr = (function_expr_t*)malloc(sizeof(function_expr_t));
    if (!function_expr)
        _parser_throw_error(parser, "Memory allocation failed for function_expr");

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    pointer++; // Skip 'proc' keyword

    char* name = data[pointer];
    if (!name || !isalpha(name[0]))
	_parser_throw_error(parser, "Invalid function name");

    vector_t* arguments = vector_init(MAX_ARGUMENT_COUNT);

    parser->inside_parameters = true;
    pointer++; // Skip function name

    while (!lexer_compare(data[pointer], "do")) {
	variable_expr_t* arg_expr = (variable_expr_t*)malloc(sizeof(variable_expr_t));
	if (!arg_expr)
	    _parser_throw_error(parser, "Memory allocation failed for arg_expr");

	char arg_datatype = _parser_evaluate_datatype(data[pointer]);
	if (arg_datatype == INVALID_DATATYPE)
	    _parser_throw_error(parser, "invalid function argument datatype");

	char* arg_name = data[pointer + 1];

	arg_expr->datatype = arg_datatype;
	arg_expr->name = arg_name;
	arg_expr->value = NULL;

	vector_push(arguments, arg_expr);

	pointer += 2;
    }

    parser->inside_parameters = false;

    function_expr->name = name;
    function_expr->arguments = arguments;
    function_expr->return_type = datatype;
    function_expr->tokens = vector_init(MAX_TOKENS);

    pointer++;
    while (!lexer_compare(data[pointer], "end")) {
	vector_push(function_expr->tokens, data[pointer]);
	pointer++;
    }

    expression_t* expr_wrapper = (expression_t*)malloc(sizeof(expression_t));
    if (!expr_wrapper)
	_parser_throw_error(parser, "Memory allocation failed for expr_wrapper");

    expr_wrapper->type = FUNCTION_EXPR;
    expr_wrapper->expr = function_expr;

    vector_push(parser->expressions, expr_wrapper);
    parser->expression_count++;
}

void parser_evaluate_calculation(parser_t* parser) {
    calculation_expr_t* calc_expr = (calculation_expr_t*)malloc(sizeof(calculation_expr_t));
    if (!calc_expr)
	_parser_throw_error(parser, "Memory allocation failed for calc_expr");

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    char operation = data[pointer][0];
    int left = atoi(data[pointer - 1]);
    int right = atoi(data[pointer + 1]);

    switch (operation) {
    case '+':
	calc_expr->type = OP_PLUS;
	calc_expr->result = left + right;
	break;
    case '-':
	calc_expr->type = OP_MINUS;
	calc_expr->result = left - right;
	break;
    case '*':
	calc_expr->type = OP_MUL;
	calc_expr->result = left * right;
	break;
    case '/':
	calc_expr->type = OP_DIV;
	calc_expr->result = left / right;
	break;
    case '%':
	calc_expr->type = OP_MODULO;
	calc_expr->result = left % right;
	break;
    case '=':
	calc_expr->type = OP_EQUALS;
	break;
    default:
	break;
    }

    expression_t* expr_wrapper = (expression_t*)malloc(sizeof(expression_t));
    if (!expr_wrapper)
	_parser_throw_error(parser, "Memory allocation failed for expr_wrapper");

    expr_wrapper->type = CALCULATION_EXPR;
    expr_wrapper->expr = calc_expr;

    vector_push(parser->expressions, expr_wrapper);
    parser->expression_count++;
}

void parser_evaluate_syscall(parser_t* parser) {
    syscall_expr_t* syscall_expr = (syscall_expr_t*)malloc(sizeof(syscall_expr_t));
    if (!syscall_expr)
        _parser_throw_error(parser, "Memory allocation failed for syscall_expr");

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    pointer++; // Skip 'syscall' keyword

    int rax = atoi(data[pointer++]);
    void* rdi = data[pointer++];
    void* rsi = data[pointer++];
    int rdx = atoi(data[pointer++]);

    syscall_expr->rax = rax;
    syscall_expr->rdi = rdi;
    syscall_expr->rsi = rsi;
    syscall_expr->rdx = rdx;

    expression_t* expr_wrapper = (expression_t*)malloc(sizeof(expression_t));
    expr_wrapper->type = SYSCALL_EXPR;
    expr_wrapper->expr = syscall_expr;

    vector_push(parser->expressions, expr_wrapper);
    parser->expression_count++;
}

void parser_evaluate_macro(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    char* macro = data[pointer + 1];
    if (macro == NULL)
        _parser_throw_error(parser, "expected macro after '%define' keyword");

    vector_push(parser->expressions, strdup(macro));
}

static void _parser_print_expressions(parser_t* parser) {
    printf("Expressions (%zu)\n=======\n", parser->expressions->size);
    for (size_t i = 0; i < parser->expressions->size; i++) {
        expression_t* wrapped_expr = (expression_t*)vector_get(parser->expressions, i);
        if (wrapped_expr == NULL || wrapped_expr->expr == NULL) continue;

        switch (wrapped_expr->type) {
            case VARIABLE_EXPR: {
                variable_expr_t* var = (variable_expr_t*)wrapped_expr->expr;
                if (var->name) {
                    printf("Variable:\n   Name: %s\n", var->name);
                    switch (var->datatype) {
                        case STRING_DATATYPE:
                            printf("   Value: %s\n", (char*)var->value);
                            break;
                        case FLOAT32_DATATYPE:
                        case FLOAT64_DATATYPE:
                            printf("   Value: %f\n", *(double*)var->value);
                            break;
                        default:
                            printf("   Value: %d\n", *(int*)var->value);
                    }

		    printf("   Constant: %d\n", var->is_constant);
                }
                break;
            }
            case FUNCTION_EXPR: {
                function_expr_t* func = (function_expr_t*)wrapped_expr->expr;
                printf("Function:\n   Name: %s()\nArguments:\n", func->name);
                for (size_t j = 0; j < 0; j++) {
                    variable_expr_t* arg = (variable_expr_t*)vector_get(func->arguments, j);
                    printf(" - %s\n", arg->name);
                }
                break;
            }
            case SYSCALL_EXPR: {
                syscall_expr_t* syscall = (syscall_expr_t*)wrapped_expr->expr;
                printf("Syscall:\n   rax: %d\n   rdi: %p\n   rsi: %p\n   rdx: %d\n",
                       syscall->rax, syscall->rdi, syscall->rsi, syscall->rdx);
                break;
            }
            case MACRO_EXPR: {
                char* macro = (char*)wrapped_expr->expr;
                printf("Macro: %s\n", macro);
                break;
            }
            default:
                printf("Unknown expression type\n");
                break;
        }
    }
}

