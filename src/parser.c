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

    return parser;
}

void parser_evaluate(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    char** data = tokens->data;
    size_t size = tokens->size;

    for (size_t i = 0; i < size; i++) {
	if (lexer_compare("var", data[i])) {
	    //_parser_evaluate_function(parser, data[i + 1], data[i + 3]);
	    _parser_evaluate_variable(parser, i);
	    printf("Name: %s, Value: %x\n", parser->variables[0]->name, parser->variables[0]->value);
	}

	tokens->pointer++;
    }
}

static void _parser_throw_error(parser_t* parser, char* error) {
    char* filename = parser->lexer->filename;

    fprintf(stderr, "[1m%s[0m: \033[31mERROR[0m: %s!", filename, error);
    exit(1);
}

static void _parser_evaluate_variable(parser_t* parser, size_t pointer) {
    char** tokens = parser->lexer->tokens->data;

    variable_expr_t variable_expr;

    char* name = tokens[pointer + 1];
    char* value = tokens[pointer + 3];
    if (name == NULL) {
	_parser_throw_error(parser, "expected name after 'var' expression"); 
    }
    if (value == NULL) {
	_parser_throw_error(parser, "expected value after variable name decleration");
    }

    variable_expr.name = name;
    variable_expr.value = value;

    parser->variables[parser->variable_count] = &variable_expr;
    parser->variable_count++;
}

static void _parser_evaluate_function(parser_t* parser, char* name, char* arguments[]) {
    function_expr_t function_expr;
    function_expr.name = name;
    function_expr.arguments = arguments;

    parser->functions[parser->function_count] = &function_expr;
    parser->function_count++;

    vector_t* tokens = parser->lexer->tokens;
    size_t pointer = tokens->pointer;

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
}
