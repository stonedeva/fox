#include "lexer.h"
#include "compiler.h"
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
    compiler_proc(lexer);
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
char* lexer_get_nexttok(const lexer_t* lexer, const size_t index) {
    return lexer->tokens->data[index + 1];
}

char* lexer_get_prevtok(const lexer_t* lexer, const size_t index) {
    return lexer->tokens->data[index - 1];
}
