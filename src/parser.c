#include "parser.h"
#include "lib/vector.h"
#include <unistd.h>
#include <limits.h>
#include <string.h>

parser_t parser_init(lexer_t* lexer) {
    parser_t parser;
    parser.lexer = lexer;
    parser.variable_count = 0;
    parser.variables = (variable_expr_t**)malloc(sizeof(variable_expr_t*) * MAX_EXPRESSIONS);
    parser.function_count = 0;
    parser.functions = (function_expr_t**)malloc(sizeof(function_expr_t*) * MAX_EXPRESSIONS);
    parser.write_call_count = 0;
    parser.write_calls = (write_expr_t**)malloc(sizeof(write_expr_t*) * MAX_EXPRESSIONS);

    return parser;
}

void parser_delete(parser_t* parser) {
    for (size_t i = 0; i < parser->variable_count; i++) {
	free(parser->variables[i]);
    }
    free(parser->variables);

    for (size_t i = 0; i < parser->function_count; i++) {
	free(parser->functions[i]);
    }
    free(parser->functions);
    
    for (size_t i = 0; i < parser->write_call_count; i++) {
	free(parser->write_calls[i]);
    }
    free(parser->write_calls);

    parser->variable_count = 0;
    parser->function_count = 0;
    parser->write_call_count = 0;
    parser->lexer = NULL;
}

void parser_evaluate(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    char** data = tokens->data;
    size_t size = tokens->size;

    for (size_t i = 0; i < size; i++) {
	char* current_tok = data[i];
	if (lexer_compare("var", current_tok)) _parser_evaluate_variable(parser);
	if (lexer_compare("end", current_tok)) _parser_evaluate_end(parser);
	if (lexer_compare("proc", current_tok)) _parser_evaluate_function(parser);
	if (lexer_compare("write", current_tok)) _parser_evaluate_write(parser);
	
	tokens->pointer++;
    }

#ifdef DEBUG
    _parser_print_expressions(parser);
#endif
}

static void _parser_throw_error(parser_t* parser, char* error) {
    char* filename = parser->lexer->filename;

    fprintf(stderr, "[1m%s[0m: \033[31mERROR[0m: %s!\n", filename, error);
    exit(1);
}

static void _parser_evaluate_variable(parser_t* parser) {
    variable_expr_t* variable_expr = (variable_expr_t*)malloc(sizeof(variable_expr_t));

    vector_t* tokens = parser->lexer->tokens;
    char** data = tokens->data;
    size_t pointer = tokens->pointer;

    char* name = data[pointer + 1];
    int value = atoi(data[pointer + 3]);
    if (value == NULL)
	_parser_throw_error(parser, "expected value after variable name decleration");
    if (name == NULL)
	_parser_throw_error(parser, "expected name after 'var' expression"); 

    variable_expr->name = name;
    variable_expr->value = value;

    parser->variables[parser->variable_count] = variable_expr;
    parser->variable_count++;
}

static void _parser_evaluate_function(parser_t* parser) {
    function_expr_t* function_expr = (function_expr_t*)malloc(sizeof(function_expr_t));

    vector_t* tokens = parser->lexer->tokens;
    char** data = tokens->data;
    size_t pointer = tokens->pointer;

    char* name = data[pointer + 1];
    char* arguments[10];
    if (name == NULL)
	_parser_throw_error(parser, "expected name after 'proc' expression");

/*    while (*tokens->data[pointer++] != "var") {
	if (lexer_compare("var", tokens->data[pointer])) {
	    char* variable_name = tokens->data[pointer + 1];
	    char* variable_value = tokens->data[pointer + 3];
	    if (variable_name == NULL) {
		_parser_throw_error(parser, "expected name after 'var' expression"); 
	    }
	    if (variable_value == NULL) {
		_parser_throw_error(parser, "expected value after variable name decleration")
	    }
	}
    }*/
    function_expr->name = name;
    function_expr->arguments = arguments;
    parser->functions[parser->function_count] = function_expr;
    parser->function_count++;
}

static void _parser_evaluate_write(parser_t* parser) {
    write_expr_t* write_expr = (write_expr_t*)malloc(sizeof(write_expr_t));

    vector_t* tokens = parser->lexer->tokens;
    char** data = tokens->data;
    size_t pointer = tokens->pointer;

    char* content = data[pointer + 1];
    char byte_amount = strlen(content);
    if (content == NULL)
	_parser_throw_error(parser, "exptected content after 'write' expression");
    /* If no content given byte_amount is automatically 0 */

    write_expr->content = content;
    write_expr->byte_amount = byte_amount;
    parser->write_calls[parser->write_call_count] = write_expr;
    parser->write_call_count++;
}

static void _parser_evaluate_end(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    size_t pointer = tokens->pointer;
    char** data = tokens->data;
    if (pointer + 1 > tokens->size)
	parser->exit_code = 0;

    int exit_code = atoi(data[pointer + 1]);
    if (exit_code > 1)
	_parser_throw_error(parser, "expected exit code of 0 or 1");

    parser->exit_code = exit_code;
}

static void _parser_print_expressions(parser_t* parser) {
    printf("Variables (%d)\n=======\n", parser->variable_count);
    for (size_t i = 0; i < parser->variable_count; i++) {
	printf("Name: %s: Value: %d\n", parser->variables[i]->name, parser->variables[i]->value);
    }
    
    printf("Functions (%d)\n=======\n", parser->function_count);
    for (size_t i = 0; i < parser->function_count; i++) {
	printf("Name: %s, Arguments: -\n", parser->functions[i]->name);
    }

    printf("Write Calls (%d)\n=======\n", parser->write_call_count);
    for (size_t i = 0; i < parser->write_call_count; i++) {
	printf("Content: %s, Amount of bytes: %d\n", parser->write_calls[i]->content, parser->write_calls[i]->byte_amount);
    }
}
