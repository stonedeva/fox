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
    parser.nodes = vector_init(MAX_NODES);
    parser.inside_parameters = false;
    parser.node_count = 0;
    parser.variable_map = hashtable_create(MAX_VARIABLES);

    return parser;
}

void parser_delete(parser_t* parser) {
    for (size_t i = 0; i < parser->nodes->size; i++) {
        node_t* wrapped_node = (node_t*)vector_get(parser->nodes, i);
        if (wrapped_node == NULL) continue;

        switch (wrapped_node->type) {
            case VARIABLE_NODE: {
                variable_node_t* var = (variable_node_t*)wrapped_node->node;
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
            case FUNCTION_NODE: {
                function_node_t* func = (function_node_t*)wrapped_node->node;
                if (func) {
                    for (size_t j = 0; j < 0; j++) {
                        variable_node_t* arg = (variable_node_t*)vector_get(func->arguments, j);
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
            case SYSCALL_NODE: {
                syscall_node_t* syscall = (syscall_node_t*)wrapped_node->node;
                if (syscall) {
		    free(syscall);
		    syscall = NULL;
		}
		break;
            }
            case MACRO_NODE: {
                char* macro = (char*)wrapped_node->node;
                if (macro) {
		    free(macro);
		    macro = NULL;
		}
		break;
            }
            default:
                free(wrapped_node->node); // Free unknown node types safely
                break;
        }
        free(wrapped_node); // Free the wrapper node itself
    }

    vector_delete(parser->nodes);
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
	} else if (lexer_compare(current_tok, "if")) {
	    parser_evaluate_condition(parser);
	} else if (_parser_evaluate_datatype(current_tok) != INVALID_DATATYPE) {
	    char datatype = _parser_evaluate_datatype(current_tok);
	    parser_evaluate_variable(parser, datatype);
	}

	tokens->pointer++;
	pointer_copy++;
    }

    _parser_print_nodes(parser);
    compiler_init(parser, "hello.ll", "hello.o");

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
    variable_node_t* variable_node = (variable_node_t*)malloc(sizeof(variable_node_t));
    if (!variable_node)
        _parser_throw_error(parser, "Memory allocation failed for variable_node");

    memset(variable_node, 0, sizeof(variable_node_t));

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    char* name;
    
    if (lexer_compare(data[pointer + 1], "const")) {
	variable_node->is_constant = true;
	name = data[pointer + 2];
    } else {
	name = data[pointer + 1];
	variable_node->is_constant = false;
    }

    pointer++; // Skip '=' sign
    
    int value_int;
    char* value_str;
    if (datatype == STRING_DATATYPE)
	value_str = data[pointer + 3];
    else
	value_int = atoi(data[pointer + 3]);

    if (name == NULL)
        _parser_throw_error(parser, "expected name after variable node"); 

    variable_node->name = strdup(name);
    variable_node->datatype = datatype;

    switch (datatype) {
    case BIT8_INT_DATATYPE:
        variable_node->value = malloc(sizeof(uint8_t));
        *(uint8_t*)variable_node->value = (uint8_t)atoi(data[pointer + 3]);
        break;
    case BIT16_INT_DATATYPE:
        variable_node->value = malloc(sizeof(uint16_t));
        *(uint16_t*)variable_node->value = (uint16_t)atoi(data[pointer + 3]);
        break;
    case BIT32_INT_DATATYPE:
        variable_node->value = malloc(sizeof(uint32_t));
        *(uint32_t*)variable_node->value = (uint32_t)atoi(data[pointer + 3]);
        break;
    case BIT64_INT_DATATYPE:
        variable_node->value = malloc(sizeof(uint64_t));
        *(uint64_t*)variable_node->value = (uint64_t)atoll(data[pointer + 3]);
        break;
    case FLOAT32_DATATYPE:
        variable_node->value = malloc(sizeof(float));
        *(float*)variable_node->value = atof(data[pointer + 3]);
        break;
    case FLOAT64_DATATYPE:
        variable_node->value = malloc(sizeof(double));
        *(double*)variable_node->value = atof(data[pointer + 3]);
        break;
    case STRING_DATATYPE:
        variable_node->value = strdup(data[pointer + 3]);
        break;
    default:
        free(variable_node);
	variable_node = NULL;
        _parser_throw_error(parser, "Invalid datatype for variable");
        return;
    }

    bool inserted = hashtable_insert(parser->variable_map, variable_node->name, variable_node);
    if (!inserted) {
	free(variable_node->name);
	free(variable_node->value);
	free(variable_node);
	variable_node = NULL;

	_parser_throw_error(parser, "Failed to insert variable into hash table");
    }

    node_t* node_wrapper = (node_t*)malloc(sizeof(node_t));
    if (!node_wrapper)
	_parser_throw_error(parser, "Memory allocation failed for node_wrapper");

    node_wrapper->type = VARIABLE_NODE;
    node_wrapper->node = variable_node;

    vector_push(parser->nodes, node_wrapper);
    parser->node_count++;
}

void parser_evaluate_function(parser_t* parser, char datatype) {
    function_node_t* function_node = (function_node_t*)malloc(sizeof(function_node_t));
    if (!function_node)
        _parser_throw_error(parser, "Memory allocation failed for function_node");

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
	variable_node_t* arg_node = (variable_node_t*)malloc(sizeof(variable_node_t));
	if (!arg_node)
	    _parser_throw_error(parser, "Memory allocation failed for arg_node");

	char arg_datatype = _parser_evaluate_datatype(data[pointer]);
	if (arg_datatype == INVALID_DATATYPE)
	    _parser_throw_error(parser, "invalid function argument datatype");

	char* arg_name = data[pointer + 1];

	arg_node->datatype = arg_datatype;
	arg_node->name = arg_name;
	arg_node->value = NULL;

	vector_push(arguments, arg_node);

	arg_node->scope = vector_get_last(arguments);
	pointer += 2;
    }

    parser->inside_parameters = false;

    function_node->name = name;
    function_node->arguments = arguments;
    function_node->return_type = datatype;
    function_node->tokens = vector_init(MAX_TOKENS);

    pointer++;
    while (!lexer_compare(data[pointer], "end")) {
	vector_push(function_node->tokens, data[pointer]);
	pointer++;
    }

    node_t* node_wrapper = (node_t*)malloc(sizeof(node_t));
    if (!node_wrapper)
	_parser_throw_error(parser, "Memory allocation failed for node_wrapper");

    node_wrapper->type = FUNCTION_NODE;
    node_wrapper->node = function_node;

    vector_push(parser->nodes, node_wrapper);
    parser->node_count++;
}

void parser_evaluate_condition(parser_t* parser) {
    condition_node_t* condition_node = (condition_node_t*)malloc(sizeof(condition_node_t));
    if (!condition_node)
	_parser_throw_error(parser, "Memory allocation failed for condition node");

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    pointer++; // Skip 'if' keyword
    while (!lexer_compare(data[pointer], "do")) {
	/*
	 * Read condition
	*/
	pointer++;
    }

    pointer++; // Skip 'do' keyword
    while (!lexer_compare(data[pointer], "end")) {
	/*
	 * Read body
	*/
	printf("If node body: %s\n", data[pointer]);
	pointer++;
    }

    node_t* node_wrapper = (node_t*)malloc(sizeof(node_t));
    if (!node_wrapper)
	_parser_throw_error(parser, "Memory allocation failed for node_wrapper");

    node_wrapper->type = CONDITION_NODE;
    node_wrapper->node = condition_node;

    vector_push(parser->nodes, node_wrapper);
    parser->node_count++;
}

void parser_evaluate_calculation(parser_t* parser) {
    calculation_node_t* calc_node = (calculation_node_t*)malloc(sizeof(calculation_node_t));
    if (!calc_node)
	_parser_throw_error(parser, "Memory allocation failed for calc_node");

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    char operation = data[pointer][0];
    int left = atoi(data[pointer - 1]);
    int right = atoi(data[pointer + 1]);

    switch (operation) {
    case '+':
	calc_node->type = OP_PLUS;
	calc_node->result = left + right;
	break;
    case '-':
	calc_node->type = OP_MINUS;
	calc_node->result = left - right;
	break;
    case '*':
	calc_node->type = OP_MUL;
	calc_node->result = left * right;
	break;
    case '/':
	calc_node->type = OP_DIV;
	calc_node->result = left / right;
	break;
    case '%':
	calc_node->type = OP_MODULO;
	calc_node->result = left % right;
	break;
    case '=':
	calc_node->type = OP_EQUALS;
	break;
    default:
	break;
    }

    node_t* node_wrapper = (node_t*)malloc(sizeof(node_t));
    if (!node_wrapper)
	_parser_throw_error(parser, "Memory allocation failed for node_wrapper");

    node_wrapper->type = CALCULATION_NODE;
    node_wrapper->node = calc_node;

    vector_push(parser->nodes, node_wrapper);
    parser->node_count++;
}

void parser_evaluate_syscall(parser_t* parser) {
    syscall_node_t* syscall_node = (syscall_node_t*)malloc(sizeof(syscall_node_t));
    if (!syscall_node)
        _parser_throw_error(parser, "Memory allocation failed for syscall_node");

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    pointer++; // Skip 'syscall' keyword

    int rax = atoi(data[pointer++]);
    void* rdi = data[pointer++];
    void* rsi = data[pointer++];
    int rdx = atoi(data[pointer++]);

    syscall_node->rax = rax;
    syscall_node->rdi = rdi;
    syscall_node->rsi = rsi;
    syscall_node->rdx = rdx;

    node_t* node_wrapper = (node_t*)malloc(sizeof(node_t));
    node_wrapper->type = SYSCALL_NODE;
    node_wrapper->node = syscall_node;

    vector_push(parser->nodes, node_wrapper);
    parser->node_count++;
}

void parser_evaluate_macro(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    char* macro = data[pointer + 1];
    if (macro == NULL)
        _parser_throw_error(parser, "expected macro after '%define' keyword");

    vector_push(parser->nodes, strdup(macro));
}

static void _parser_print_nodes(parser_t* parser) {
    printf("Expressions (%zu)\n=======\n", parser->nodes->size);
    for (size_t i = 0; i < parser->nodes->size; i++) {
        node_t* wrapped_node = (node_t*)vector_get(parser->nodes, i);
        if (wrapped_node == NULL || wrapped_node->node == NULL) continue;

        switch (wrapped_node->type) {
            case VARIABLE_NODE: {
                variable_node_t* var = (variable_node_t*)wrapped_node->node;
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
            case FUNCTION_NODE: {
                function_node_t* func = (function_node_t*)wrapped_node->node;
                printf("Function:\n   Name: %s()\nArguments:\n", func->name);
                for (size_t j = 0; j < 0; j++) {
                    variable_node_t* arg = (variable_node_t*)vector_get(func->arguments, j);
                    printf(" - %s\n", arg->name);
                }
                break;
            }
            case SYSCALL_NODE: {
                syscall_node_t* syscall = (syscall_node_t*)wrapped_node->node;
                printf("Syscall:\n   rax: %d\n   rdi: %p\n   rsi: %p\n   rdx: %d\n",
                       syscall->rax, syscall->rdi, syscall->rsi, syscall->rdx);
                break;
            }
            case MACRO_NODE: {
                char* macro = (char*)wrapped_node->node;
                printf("Macro: %s\n", macro);
                break;
            }
            default:
                printf("Unknown node type\n");
                break;
        }
    }
}

