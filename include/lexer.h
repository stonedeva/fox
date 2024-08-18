#ifndef _TOKEN_H_
#define _TOKEN_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdbool.h>
#include "lib/vector.h"


#define MAX_TOKENS 255

static char* token_keywords[] = {
    "int", "char", "string", "short",
    "long", "double", "struct",
    "function", "import",
    "if", "else", "switch", "case",
    "break", "default", "return"
};

/*
 * Public
*/
typedef struct {
    FILE* file;
    vector_t* tokens;
    size_t cursor;
    char line[MAX_TOKENS];
} lexer_t;

lexer_t lexer_init(const char filename[]);
void lexer_proc(const lexer_t* lexer);

/*
 * Private
*/
static bool _lexer_is_delimiter(const char ch);
static void _lexer_proc_string(const lexer_t* lexer);
char* _lexer_get_nexttok(const lexer_t* lexer, const size_t index);
char* _lexer_get_prevtok(const lexer_t* lexer, const size_t index);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TOKEN_H_ */
