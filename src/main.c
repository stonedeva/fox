#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "compiler.h"
#include "lexer.h"

static void fox_print_help(int code) {
    FILE* stream = code ? stderr : stdout;

    fprintf(stream, "Usage: foxc <file> [options...]\n\n");
    fprintf(stream, "Options:\n");
    fprintf(stream, "-h	Show help map\n");
    fprintf(stream, "-o	Set output file\n");
    fprintf(stream, "-s	Compile to assembly\n");
    fprintf(stream, "-v	Get compiler version\n");

    exit(code);
}

static int fox_init(int argc, char* argv[]) {
    size_t path_len = strlen(argv[1]);
    char input_path[path_len];
    strcpy(input_path, argv[1]);

    lexer_t fox_lexer = lexer_init(argv[1]);
    lexer_proc(&fox_lexer);
    
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
	fprintf(stderr, "Usage: %s <file> [options...]\n", argv[0]);
	return 1;
    }

    return fox_init(argc, argv);
}
