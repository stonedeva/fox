#ifndef _PARSER_H_
#define _PARSER_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "expressions.h"
#include "lexer.h"
#include "lib/hashtable.h"

typedef struct {
    lexer_t* lexer;
    vector_t* nodes;
    int exit_code;
    bool inside_parameters;
    size_t node_count;
    hashtable_t* variable_map;
} parser_t;

void parser_evaluate(parser_t* parser);
parser_t parser_init(lexer_t* lexer);
void parser_delete(parser_t* parser);

void parser_evaluate_variable(parser_t* parser, char datatype);
void parser_evaluate_function(parser_t* parser, char datatype);
void parser_evaluate_syscall(parser_t* parser);
void parser_evaluate_calculation(parser_t* parser);
void parser_evaluate_macro(parser_t* parser);
static char _parser_evaluate_datatype(char* str);
static void _parser_throw_error(parser_t* parser, char* error);
static void _parser_print_nodes(parser_t* parser);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PARSER_H_ */
