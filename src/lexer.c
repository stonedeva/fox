#include "lexer.h"
#include "compiler.h"
#include "parser.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Public functions
*/
lexer_t lexer_init(const char filename[]) {
    lexer_t lexer;
    lexer.file = fopen(filename, "r");
    if (lexer.file == NULL) {
	perror(filename);
	exit(1);
    }

    lexer.tokens = vector_init(MAX_TOKENS); 
    
    return lexer;
}

void lexer_proc(const lexer_t* lexer) {
    while (fgets(lexer->line, sizeof(lexer->line), lexer->file)) {
	_lexer_proc_string(lexer);
    }

    //compiler_proc(lexer);
    parser_t parser = parser_init(lexer);
    parser_evaluate(&parser);
}

/*
 * Private functions
*/
static bool _lexer_is_delimiter(const char ch) {
    return isspace(ch) || ch == '#' || ch == ',' || ch == '.' || ch == ';' || ch == ':' 
	    || ch == '!' || ch == '?' || ch == '<' || ch == '>' || ch == '(' 
	    || ch == ')' || ch == '"';
}

static void _lexer_proc_string(const lexer_t* lexer) {
    const char *line = lexer->line;
    size_t len = strlen(line);
    char token[MAX_TOKENS]; 
    size_t token_index = 0;
    bool inside_string = false;

    for (size_t i = 0; i < len; i++) {
        char ch = line[i];
        
        if (ch == '"') {
            inside_string = !inside_string;
            token[token_index++] = ch;
            continue;
        }

        if (!inside_string && _lexer_is_delimiter(ch)) {
            if (token_index > 0) {
                token[token_index] = '\0';  
		vector_push(lexer->tokens, token);
                token_index = 0;
	    }
	    continue;
	}
	token[token_index++] = ch;
    }
    
    if (token_index > 0) {
        token[token_index] = '\0';
	vector_push(lexer->tokens, token);
    }
}

/*
 * Public
*/

char* lexer_get_nexttok(const vector_t* tokens, const size_t offset) {
    if (tokens->pointer + offset > tokens->size)
	return NULL;

    return tokens->data[tokens->pointer + offset];
}

char* lexer_get_prevtok(const vector_t* tokens, const size_t offset) {
    if (tokens->pointer - offset < 0)
	return NULL;
    return tokens->data[tokens->pointer - offset];
}

bool lexer_compare(char* token1, char* token2) {
    while (*token1++ != '\0') {
	*token2++;
	if (*token1 != *token2) return false;
    }

    return true;
}
