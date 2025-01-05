#include "lexer.h"
#include "context.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/*
 * Public functions
*/
Lexer lexer_init(char* filename, char* import_path) 
{
    Lexer lexer = {
	.file = fopen(filename, "r"),
	.line_count = 1,
	.import_path = import_path,
	.filename = filename
    };
    if (lexer.file == NULL) {
	perror(filename);
	exit(1);
    }

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
    return isspace(ch) || ch == ',' || ch == ':' || ch == ';';
}

static void _lexer_tokenize(Lexer* lexer) 
{
    size_t row = 1;

    const char *line = lexer->line;
    size_t len = strlen(line);
    char token[MAX_TOKENS]; 
    size_t token_index = 0;
    bool inside_string = false;

    if (strncmp("import", line, 6) == 0) {
        (void) strtok(line, " ");
        char* path =  strtok(NULL, " ");
        path++;
        path[len - 6 - 4] = '\0'; // Remove '\n' and quotes in path

        _lexer_import_file(lexer, path);
        return;
    }

    for (size_t i = 0; i < len; i++) {
        char ch = line[i];

	if (ch == '/' && line[i + 1] == '/') {
	    return;
	}
        
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

void _lexer_import_file(Lexer* lexer, const char* path)
{
    char cwd[1024];

    if (lexer->import_path != NULL && path[0] != '.' && path[1] != '/') {
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
	    fprintf(stderr, "Lexer Error: getcwd(): '%s': %s\n",
		    path, strerror(errno));    
	    exit(1);
	}
	chdir(lexer->import_path);
    }

    FILE* file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Lexer Error: Could not import file: '%s': %s\n",
                path, strerror(errno));
        exit(1);
    }

    Lexer import_lexer = lexer_init(path, NULL);
    lexer_proc(&import_lexer);

    if (import_lexer.tok_sz == 0) {
        fprintf(stderr, "Lexer Warning: Importing empty file!\n");
        return;
    }

    for (size_t i = 0; i < import_lexer.tok_sz; i++) {
        lexer->tokens[lexer->tok_sz++] = import_lexer.tokens[i];
    }
    fclose(file);

    chdir(cwd);
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
    } else if (strcmp("print", cstr) == 0) {
	return TOK_PRINT;
    } else if (strcmp("dup", cstr) == 0) {
	return TOK_DUP;
    } else if (strcmp("swap", cstr) == 0) {
	return TOK_SWAP;
    } else if (strcmp("over", cstr) == 0) {
	return TOK_OVER;
    } else if (strcmp("rot", cstr) == 0) {
	return TOK_ROT;
    } else if (strcmp("drop", cstr) == 0) {
	return TOK_DROP;
    } else if (strcmp("set8", cstr) == 0) {
	return TOK_PTR_SET8;
    } else if (strcmp("set32", cstr) == 0) {
	return TOK_PTR_SET32;
    } else if (strcmp("set64", cstr) == 0) {
	return TOK_PTR_SET64;
    } else if (strcmp("get8", cstr) == 0) {
	return TOK_PTR_GET8;
    } else if (strcmp("get32", cstr) == 0) {
	return TOK_PTR_GET32;
    } else if (strcmp("get64", cstr) == 0) {
	return TOK_PTR_GET64;
    } else if (strcmp("memory", cstr) == 0) {
	return TOK_DEF_MEM;
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
    } else if (strcmp("const", cstr) == 0) {
	return TOK_DEF_CONST;
    } else if (strcmp("peek", cstr) == 0) {
	return TOK_PEEK;
    } else if (strcmp("take", cstr) == 0) {
	return TOK_TAKE;
    } else if (strcmp("continue", cstr) == 0) {
	return TOK_CONTINUE;
    } else if (strcmp("argc", cstr) == 0) {
	return TOK_ARGC;
    } else if (strcmp("argv", cstr) == 0) {
	return TOK_ARGV;
    } else if (utils_is_number(cstr)) {
	return TOK_NUMBER;
    } else if (utils_is_operator(cstr)) {
	return TOK_BINARYOP;
    } else if (cstr[0] == '"'){
	return TOK_STRING_LITERAL;
    } else if (cstr[0] == '\'') {
	return TOK_CHAR;
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
