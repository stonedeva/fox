#ifndef _PARSER_H_
#define _PARSER_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "lexer.h"
#include "expressions.h"

typedef struct {
    lexer_t* lexer;
    function_expr_t** functions;
    variable_expr_t** variables;
    size_t variable_count;
    size_t function_count;
    int exit_code;
} parser_t;

void parser_evaluate(parser_t* parser);
parser_t parser_init(lexer_t* lexer);
void parser_delete(parser_t* parser);

static void _parser_evaluate_variable(parser_t* parser);
static void _parser_evaluate_function(parser_t* parser);
static void _parser_evaluate_end(parser_t* parser);
static void _parser_throw_error(parser_t* parser, char* error);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PARSER_H_ */
