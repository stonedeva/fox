#ifndef _TOKEN_H_
#define _TOKEN_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdbool.h>

#define MAX_TOKENS 255
#define SEMICOLON ';'

/*
 * Public
*/

typedef enum {
    TOK_BINARYOP,
    TOK_NUMBER,
    TOK_CONDITION,
    TOK_ELSE,
    TOK_LOOP,
    TOK_DO,
    TOK_DUMP,
    TOK_DUP,
    TOK_SWAP,
    TOK_DROP,
    TOK_DEF_FUNC,
    TOK_FUNC_CALL,
    TOK_VAR_REF,
    TOK_DEF_VAR,
    TOK_REDEF_VAR,
    TOK_DEF_ARRAY,
    TOK_SYSCALL,
    TOK_RETURN,
    TOK_END,
    TOK_CHARACTER,
    TOK_STRING_LITERAL,
    TOK_IMPORT
} TokenType;

typedef struct {
    TokenType type;
    char* token;
    size_t line;
    size_t row;
} Token;

typedef struct {
    FILE* file;
    Token tokens[MAX_TOKENS];
    size_t tok_sz;
    char line[MAX_TOKENS];
    size_t line_count;
    char* filename;
} Lexer;

Lexer* lexer_init(char* filename);
void lexer_proc(Lexer* lexer);

/*
 * Private
*/
static bool _lexer_is_delimiter(const char ch);
static void _lexer_tokenize(Lexer* lexer);
static TokenType _lexer_type_from_cstr(char* cstr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TOKEN_H_ */
