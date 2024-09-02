#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "compiler.h"
#include "lexer.h"

#define DEBUG

static void fox_print_help(int code) {
    FILE* stream = code ? stderr : stdout;

    fprintf(stream, "Usage: foxc <file> [options...]\n\n");
    fprintf(stream, "Options:\n");
    fprintf(stream, "-h	Show help map\n");
    fprintf(stream, "-o	Set output file\n");
    fprintf(stream, "-l	Compile to assembly\n");
    fprintf(stream, "-v	Get compiler version\n");

    exit(code);
}

static int fox_init(int argc, char* argv[]) {
    char* program_path = argv[0];
    char* input_path = argv[1];
    char* output_path;

    size_t i = 2;
    while (i < argc) {
	if (argv[i][0] != '-') {
	    if (i + 1 > argc)
		break;
	    i++;
	}

	char option = argv[i][1];
	switch (option) {
	case 'h':
	    fox_print_help(0);
	    break;
	case 'o':
	    if (i + 1 > argc) {
		fprintf(stderr, "%s: No output file provided!\n", program_path);
		exit(1);
	    }

	    output_path = argv[i + 1];
	    break;
	case 'v':
	    printf("v0.01\n");
	    break;

	default:
	    fprintf(stderr, "%s: Invalid option provided!\n", program_path);
	    fox_print_help(1);
	    break;
	}

	i++;
    }

    lexer_t fox_lexer = lexer_init(input_path);
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
