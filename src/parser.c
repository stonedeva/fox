#include "parser.h"
#include "compiler.h"
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

parser_t parser_init(lexer_t* lexer) {
    parser_t parser;
    parser.lexer = lexer;
    parser.variables = vector_init(MAX_EXPRESSIONS);
    parser.functions = vector_init(MAX_EXPRESSIONS);
    parser.write_calls = vector_init(MAX_EXPRESSIONS);
    parser.macros = vector_init(MAX_EXPRESSIONS);

    return parser;
}

void parser_delete(parser_t* parser) {
    for (size_t i = 0; i < parser->variables->size; i++) { 
        free(vector_get(parser->variables, i)); 
    }
    for (size_t i = 0; i < parser->functions->size; i++) { 
        free(vector_get(parser->functions, i)); 
    }
    for (size_t i = 0; i < parser->write_calls->size; i++) { 
        free(vector_get(parser->write_calls, i)); 
    }
    for (size_t i = 0; i < parser->macros->size; i++) { 
        free(vector_get(parser->macros, i)); 
    }

    parser->lexer = NULL;
}

void parser_evaluate(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t size = tokens->size;

    for (size_t i = 0; i < size; i++) {
        char* current_tok = data[i];
        if (lexer_compare("int8", current_tok)) 
	    parser_evaluate_variable(parser, BIT8_INT_DATATYPE);
	else if (lexer_compare("int16", current_tok))
	    parser_evaluate_variable(parser, BIT16_INT_DATATYPE);
	else if (lexer_compare("int32", current_tok))
	    parser_evaluate_variable(parser, BIT32_INT_DATATYPE);
	else if (lexer_compare("int64", current_tok))
	    parser_evaluate_variable(parser, BIT64_INT_DATATYPE);
	else if (lexer_compare("string", current_tok))
	    parser_evaluate_variable(parser, STRING_DATATYPE);
	else if (lexer_compare("float32", current_tok))
	    parser_evaluate_variable(parser, FLOAT32_DATATYPE);
	else if (lexer_compare("float64", current_tok))
	    parser_evaluate_variable(parser, FLOAT64_DATATYPE);
	else if (lexer_compare("proc", current_tok))
	    parser_evaluate_function(parser);
	else if (lexer_compare("write", current_tok)) 
	    parser_evaluate_write(parser);
	else if (lexer_compare("define", current_tok)) 
	    parser_evaluate_macro(parser);

        tokens->pointer++;
    }

    _parser_print_expressions(parser);
    compiler_proc(parser);

    parser_delete(parser);
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

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    char* name = data[pointer + 1];
    
    int value_int;
    char* value_str;
    if (datatype == STRING_DATATYPE)
	value_str = data[pointer + 3];
    else
	value_int = atoi(data[pointer + 3]);

    if (name == NULL)
        _parser_throw_error(parser, "expected name after 'var' expression"); 

    variable_expr->name = name;

    switch (datatype) {
    case BIT8_INT_DATATYPE:
	variable_expr->value = (uint8_t*)value_int;
	break;
    case BIT16_INT_DATATYPE:
	variable_expr->value = (uint16_t*)value_int;
	break;
    case BIT32_INT_DATATYPE:
	variable_expr->value = (uint32_t*)value_int;
	break;
    case BIT64_INT_DATATYPE:
	variable_expr->value = (uint64_t*)value_int;
	break;
    case FLOAT32_DATATYPE:
	variable_expr->value = (float*)value_int;
	break;
    case FLOAT64_DATATYPE:
	variable_expr->value = (double*)value_int;
    default:
	break;
    }

    vector_push(parser->variables, variable_expr);
}

void parser_evaluate_function(parser_t* parser) {
    function_expr_t* function_expr = (function_expr_t*)malloc(sizeof(function_expr_t));
    if (!function_expr)
        _parser_throw_error(parser, "Memory allocation failed for function_expr");

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    char* name = data[pointer + 1];
    if (name == NULL)
        _parser_throw_error(parser, "expected name after 'proc' expression");

    function_expr->name = name;
    function_expr->arguments = NULL; // Assuming no arguments for now
    function_expr->tokens = vector_init(MAX_TOKENS);

    pointer += 2;
    while (strcmp(data[pointer], "end")) {
	vector_push(function_expr->tokens, data[pointer]);
	pointer++;
    }

    vector_push(parser->functions, function_expr);
}

void parser_evaluate_write(parser_t* parser) {
    write_expr_t* write_expr = (write_expr_t*)malloc(sizeof(write_expr_t));
    if (!write_expr)
        _parser_throw_error(parser, "Memory allocation failed for write_expr");

    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    char* content = data[pointer + 1];
    if (content == NULL)
        _parser_throw_error(parser, "expected content after 'write' expression");

    write_expr->content = content;
    write_expr->byte_amount = strlen(content);

    vector_push(parser->write_calls, write_expr);
}

void parser_evaluate_macro(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    char** data = (char**)tokens->data;
    size_t pointer = tokens->pointer;

    char* macro = data[pointer + 1];
    if (macro == NULL)
        _parser_throw_error(parser, "expected macro after '%define' keyword");

    vector_push(parser->macros, strdup(macro));
}

static void _parser_print_expressions(parser_t* parser) {
    printf("Variables (%zu)\n=======\n", parser->variables->size);
    for (size_t i = 0; i < parser->variables->size; i++) {
        variable_expr_t* var = (variable_expr_t*)parser->variables->data[i]; // Correct type casting
        printf("Name: %s: Value: %d\n", var->name, var->value);
    }
    
    printf("\nFunctions (%zu)\n=======\n", parser->functions->size);
    for (size_t i = 0; i < parser->functions->size; i++) {
        function_expr_t* func = (function_expr_t*)parser->functions->data[i]; // Correct type casting
        printf("Name: %s(), Arguments: -\n", func->name);
    }

    printf("\nWrite Calls (%zu)\n=======\n", parser->write_calls->size);
    for (size_t i = 0; i < parser->write_calls->size; i++) {
        write_expr_t* write = (write_expr_t*)parser->write_calls->data[i]; // Correct type casting
        printf("Content: %s, Amount of bytes: %d\n", write->content, write->byte_amount);
    }

    printf("\nMacros (%zu)\n=======\n", parser->macros->size);
    for (size_t i = 0; i < parser->macros->size; i++) {
        char* macro = (char*)parser->macros->data[i];
        printf("Macro: %s\n", macro);
    }
}

