#include "parser.h"
#include "lib/vector.h"

parser_t parser_init(lexer_t* lexer) {
    parser_t parser;
    parser.lexer = lexer;

    return parser;
}

void parser_evaluate(parser_t* parser) {
    vector_t* tokens = parser->lexer->tokens;
    char** data = tokens->data;
    size_t size = tokens->size;

    for (size_t i = 0; i < size; i++) {
	if (lexer_compare("var", data[i])) {
	    
	}
    }
}

