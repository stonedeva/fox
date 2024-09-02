#ifndef _TOKEN_H_
#define _TOKEN_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdbool.h>
#include "lib/vector.h"


#define MAX_TOKENS 255
#define SEMICOLON ';'

/*
 * Public
*/
typedef struct {
    FILE* file;
    vector_t* tokens;
    char line[MAX_TOKENS];
    size_t line_count;
    char* filename;
} lexer_t;

lexer_t lexer_init(char* filename);
void lexer_proc(lexer_t* lexer);

/*
 * Private
*/
static bool _lexer_is_delimiter(const char ch);
static void _lexer_tokenize(const lexer_t* lexer);

/*
 * Public
*/
char* lexer_get_nexttok(const vector_t* tokens, const size_t offset);
char* lexer_get_prevtok(const vector_t* tokens, const size_t offset);
bool lexer_compare(char* token1, char* token2);
bool lexer_contains(char ch, char* token);
char* lexer_cut(char ch, char* token);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TOKEN_H_ */
