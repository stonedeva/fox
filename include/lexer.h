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
    Vector* tokens;
    char line[MAX_TOKENS];
    size_t line_count;
    char* filename;
} Lexer;

Lexer lexer_init(char* filename);
void lexer_proc(Lexer* lexer);

/*
 * Private
*/
static bool _lexer_is_delimiter(const char ch);
static void _lexer_tokenize(const Lexer* lexer);

/*
 * Public
*/
char* token_next(const Vector* tokens, const size_t offset);
char* token_prev(const Vector* tokens, const size_t offset);
void token_skip(Vector* tokens, const size_t offset);
bool lexer_compare(char* token1, char* token2);
bool lexer_contains(char ch, char* token);
char* lexer_cut(char ch, char* token);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TOKEN_H_ */
