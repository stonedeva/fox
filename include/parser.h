#ifndef _PARSER_H_
#define _PARSER_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "lexer.h"

typedef struct {
    enum {
	VARIABLE_EXPR,
	FUNCTION_EXPR,
	IF_EXPR,
	ELSE_EXPR,
	SWITCH_EXPR,
	CASE_EXPR,
	DEFAULT_EXPR,
	IMPORT_EXPR
    };

    char value[25];
} expr_t;

typedef struct {
    lexer_t* lexer;
    expr_t* expressions;
} parser_t;

void parser_evaluate(parser_t* parser);
parser_t parser_init(lexer_t* lexer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PARSER_H_ */
