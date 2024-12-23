#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "type.h"
#include "compiler.h"

#define DEBUG

static void fox_print_help(int code) 
{
    FILE* stream = code ? stderr : stdout;

    fprintf(stream, "Usage: foxc <file> [options...]\n\n");
    fprintf(stream, "Options:\n");
    fprintf(stream, "	-h	Show help map\n");
    fprintf(stream, "	-o	Set output file\n");
    fprintf(stream, "	-l	Compile to assembly\n");
    fprintf(stream, "	-r 	Execute after compiling\n");
    fprintf(stream, "	-v	Get compiler version\n");
    fprintf(stream, "	-e 	Set NO entry point\n");

    exit(code);
}

static char* fox_out_path_from_input(char* input_path)
{
    char out_path[strlen(input_path) + 1];
    strcpy(out_path, input_path);
    size_t out_len = strlen(out_path);

    out_path[out_len - 1] = 'm';
    out_path[out_len - 2] = 's';
    out_path[out_len - 3] = 'a';

    return out_path;
}

static int fox_init(int argc, char* argv[]) 
{
    char* program_path = argv[0];
    char* input_path = argv[1];

    size_t mem_capacity = 2400;
    bool has_typecheck = true;

    size_t i = 2;
    while (i < argc) {
	if (argv[i][0] != '-') {
	    if (i + 1 > argc) {
		break;
	    }
	}

	char option = argv[i][1];
	switch (option) {
	case 'h':
	    fox_print_help(0);
	    return 0;
	case 'v':
	    printf("v0.01\n");
	    return 0;
	case 't':
	    has_typecheck = false;
	    break;
	case 'm':
	    if (i >= argc) {
		fprintf(stderr, "%s: Invalid option provided!\n", program_path);
		fprintf(stderr, "ERROR: Option '-m' requires integer");
		break;
	    }
	    mem_capacity = (size_t)strtoull(argv[i + 1], NULL, 10);
	    i++;
	    break;
	default:
	    fprintf(stderr, "%s: Invalid option provided!\n", program_path);
	    return 1;
	}

	i++;
    }

    Lexer lexer = lexer_init(input_path, "stdlib");
    lexer_proc(&lexer);

    if (has_typecheck) {
	TypeStack typestack = typestack_init(&lexer);
	typestack_evaluate(&typestack);
    }

    char output_path[20];

#ifndef DEBUG
    strcpy(output_path, fox_out_path_from_input(input_path));
#else
    strcpy(output_path, "output.asm");
#endif

    Compiler compiler = compiler_init(output_path, &lexer, mem_capacity);
    compiler_emit_base(output_path, compiler.context->main_addr);
    compiler_emit(&compiler);

    return 0;
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
	fprintf(stderr, "Usage: %s <file> [options...]\n", argv[0]);
	return 1;
    }

    return fox_init(argc, argv);
}
