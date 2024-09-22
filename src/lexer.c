#include "lexer.h"
#include "compiler.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Public functions
*/
Lexer lexer_init(char* filename) 
{
    Lexer lexer;
    lexer.file = fopen(filename, "r");
    lexer.line_count = 0;
    if (lexer.file == NULL) {
	perror(filename);
	exit(1);
    }

    lexer.tokens = vector_init(MAX_TOKENS); 
    lexer.filename = filename;

    return lexer;
}

void lexer_proc(Lexer* lexer) 
{
    while (fgets(lexer->line, sizeof(lexer->line), lexer->file)) {
	_lexer_tokenize(lexer);
	lexer->line_count++;
    }

    char** tokens = lexer->tokens->data;
    size_t tok_sz = lexer->tokens->size;

    Compiler* compiler = compiler_init("hello.asm", tokens, tok_sz);
    compiler_emit(compiler);
}

/*
 * Private functions
*/
static bool _lexer_is_delimiter(const char ch)
{
    return isspace(ch) || ch == '#' || ch == ',' || ch == '.' || ch == ':' 
	    || ch == '!' || ch == '?' || ch == '<' || ch == '>' || ch == '"'
	    || ch == '(' || ch == ')' || ch == ';';
}

static void _lexer_tokenize(const Lexer* lexer) 
{
    const char *line = lexer->line;
    size_t len = strlen(line);
    char token[MAX_TOKENS]; 
    size_t token_index = 0;
    bool inside_string = false;

    for (size_t i = 0; i < len; i++) {
        char ch = line[i];
        
	// Inside String
        if (ch == '"' || ch == '\'') {
            inside_string = !inside_string;
            token[token_index++] = ch;
            continue;
        }

	// Skip comments
	if (ch == '#')
	    continue;

        if (!inside_string && _lexer_is_delimiter(ch)) {
            if (token_index > 0) {
                token[token_index] = '\0';
		vector_push(lexer->tokens, strdup(token));
		token_index = 0;
	    }

	    if (ch == ';') {
		vector_push(lexer->tokens, strdup(";"));
	    }

	    if (ch == ':') {
		char* doubledot = ":";
		vector_push(lexer->tokens, strdup(":"));
	    }

	    continue;
	}
	token[token_index++] = ch;
    }
    
    if (token_index > 0) {
        token[token_index] = '\0';
	vector_push(lexer->tokens, strdup(token));
    }
}

/*
 * Public
*/

char* token_prev(const Vector* tokens, const size_t offset) 
{
    if (tokens->pointer + offset > tokens->size)
	return NULL;

    return tokens->data[tokens->pointer + offset];
}

char* token_next(const Vector* tokens, const size_t offset) 
{
    if (tokens->pointer - offset < 0)
	return NULL;
    return tokens->data[tokens->pointer - offset];
}

void token_skip(Vector* tokens, const size_t offset) 
{
    tokens->pointer += offset;
}

bool lexer_compare(char* token1, char* token2) 
{
    if (token1 == NULL)
	return false;
    if (token2 == NULL)
	return false;

    while (*token1++ != '\0') {
	*token2++;
	if (*token1 != *token2) return false;
    }

    return true;
}

bool lexer_contains(char ch, char* token) 
{
    while (*token++ != '\0') {
	if (*token == ch) return true;
    }
    return false;
}

char* lexer_cut(char ch, char* token) 
{
    while (*token++ != '\0')
	if (*token == ch) *token = '\0';
    return token;
}
