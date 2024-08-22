#ifndef _PARSER_H_
#define _PARSER_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "expressions.h"
#include "lexer.h"
#include "lib/vector.h"

#define DEBUG

typedef struct {
    lexer_t* lexer;
    vector_t* functions;
    vector_t* variables;
    vector_t* write_calls;
    vector_t* macros;
    int exit_code;
} parser_t;

void parser_evaluate(parser_t* parser);
parser_t parser_init(lexer_t* lexer);
void parser_delete(parser_t* parser);

static void _parser_evaluate_variable(parser_t* parser);
static void _parser_evaluate_function(parser_t* parser);
static void _parser_evaluate_end(parser_t* parser);
static void _parser_evaluate_write(parser_t* parser);
static void _parser_evaluate_macro(parser_t* parser);
static void _parser_throw_error(parser_t* parser, char* error);
static void _parser_print_expressions(parser_t* parser);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PARSER_H_ */
