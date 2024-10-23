#include "lexer.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/*
 * Public functions
*/
Lexer* lexer_init(char* filename) 
{
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));;
    lexer->file = fopen(filename, "r");
    lexer->line_count = 1;
    if (lexer->file == NULL) {
	perror(filename);
	exit(1);
    }

    lexer->filename = filename;

    return lexer;
}

void lexer_proc(Lexer* lexer) 
{
    while (fgets(lexer->line, sizeof(lexer->line), lexer->file)) {
	_lexer_tokenize(lexer);
	lexer->line_count++;
    }
}

static bool _lexer_is_delimiter(const char ch)
{
    return isspace(ch) || ch == ',' || ch == '.' || ch == ':' 
	    || ch == '!' || ch == '?' || ch == '(' || ch == ')' || ch == ';';
}

static void _lexer_tokenize(Lexer* lexer) 
{
    size_t row = 1;

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

        if (!inside_string && _lexer_is_delimiter(ch)) {
            if (token_index > 0) {
                token[token_index] = '\0';
		lexer->tokens[lexer->tok_sz] = (Token) {
		    .type = _lexer_type_from_cstr(token),
		    .token = strdup(token),
		    .line = lexer->line_count,
		    .row = row
		};
		lexer->tok_sz++;
		row++;
		token_index = 0;
	    }

	    continue;
	}
	token[token_index++] = ch;
    }
    
    if (token_index > 0) {
        token[token_index] = '\0';
	lexer->tokens[lexer->tok_sz] = (Token) {
	    .type = _lexer_type_from_cstr(token),
	    .token = strdup(token),
	    .line = lexer->line_count,
	    .row = row
	};
	lexer->tok_sz++;
	row++;
    }
}

/*
 * Private
*/
static TokenType _lexer_type_from_cstr(char* cstr)
{
    if (strcmp("func", cstr) == 0) {
	return TOK_DEF_FUNC;
    } else if (strcmp("var", cstr) == 0) {
	return TOK_DEF_VAR;
    } else if (strcmp("end", cstr) == 0) {
	return TOK_END;
    } else if (strcmp("dump", cstr) == 0) {
	return TOK_DUMP;
    } else if (strcmp("dup", cstr) == 0) {
	return TOK_DUP;
    } else if (strcmp("swap", cstr) == 0) {
	return TOK_SWAP;
    } else if (strcmp("drop", cstr) == 0) {
	return TOK_DROP;
    } else if (strcmp("return", cstr) == 0) {
	return TOK_RETURN;
    } else if (strcmp("if", cstr) == 0) {
	return TOK_CONDITION;
    } else if (strcmp("else", cstr) == 0) {
	return TOK_ELSE;
    } else if (strcmp("while", cstr) == 0) {
	return TOK_LOOP;
    } else if (strcmp("do", cstr) == 0) {
	return TOK_DO;
    } else if (strcmp("syscall", cstr) == 0) {
	return TOK_SYSCALL;
    } else if (strcmp("import", cstr) == 0) {
	return TOK_IMPORT;
    } else if (strcmp("array", cstr) == 0) {
	return TOK_DEF_ARRAY;
    } else if (utils_is_number(cstr)) {
	return TOK_NUMBER;
    } else if (utils_is_operator(cstr)) {
	return TOK_BINARYOP;
    } else if (cstr[0] == '"' && cstr[strlen(cstr) - 1] == '"'){
	return TOK_STRING_LITERAL;
    } else if (cstr[0] == '@') {
	return TOK_FUNC_CALL;
    } else if (cstr[0] == '#') {
	return TOK_REDEF_VAR;
    } else if (cstr[0] == '&') {
	return TOK_PTR_REF;
    } else {
	return TOK_VAR_REF;
    }
}
