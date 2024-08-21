#include "parser.h"
#include "lib/vector.h"
#include <unistd.h>
#include <limits.h>

parser_t parser_init(lexer_t* lexer) {
    parser_t parser;
    parser.lexer = lexer;
    parser.variable_count = 0;
    parser.variables = (variable_expr_t**)malloc(sizeof(variable_expr_t*) * 20);
    parser.function_count = 0;
    parser.functions = (function_expr_t**)malloc(sizeof(function_expr_t*) * 20);

    return parser;
}

void parser_delete(parser_t* parser) {
    parser->variable_count = 0;
    parser->function_count = 0;
    parser->lexer = NULL;
    free(parser->variables);
    free(parser->functions);
    parser->variables = NULL;
    parser->functions = NULL;
}

void parser_evaluate(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    char** data = tokens->data;
    size_t size = tokens->size;

    for (size_t i = 0; i < size; i++) {
	char* current_tok = data[i];
	if (lexer_compare("var", current_tok)) {
	    //_parser_evaluate_function(parser, data[i + 1], data[i + 3]);
	    _parser_evaluate_variable(parser);
	    printf("Name: %s, Value: %d\n", parser->variables[0]->name, parser->variables[0]->value);
	}
	if (lexer_compare("end", current_tok)) {
	    _parser_evaluate_end(parser);
	}
	if (lexer_compare("proc", current_tok)) {
	    _parser_evaluate_function(parser);
	}

	tokens->pointer++;
    }
}

static void _parser_throw_error(parser_t* parser, char* error) {
    char* filename = parser->lexer->filename;

    fprintf(stderr, "[1m%s[0m: \033[31mERROR[0m: %s!\n", filename, error);
    exit(1);
}

static void _parser_evaluate_variable(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    char** data = tokens->data;
    size_t pointer = tokens->pointer;

    variable_expr_t variable_expr;

    char* name = data[pointer + 1];
    int value = atoi(data[pointer + 3]);
    if (value == NULL)
	_parser_throw_error(parser, "expected value after variable name decleration");
    if (name == NULL)
	_parser_throw_error(parser, "expected name after 'var' expression"); 

    variable_expr.name = name;
    variable_expr.value = value;

    parser->variables[parser->variable_count] = &variable_expr;
    parser->variable_count++;
}

static void _parser_evaluate_function(parser_t* parser) {
    function_expr_t function_expr;

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
    function_expr.name = name;
    function_expr.arguments = arguments;
    parser->functions[parser->function_count] = &function_expr;
    parser->function_count++;

    printf("Define function: %s()\n", function_expr.name);
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
