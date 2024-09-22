#include "compiler.h"
#include <errno.h>

Compiler* compiler_init(char* output_path, char** tokens, size_t tok_sz)
{
    Compiler* compiler = (Compiler*)malloc(sizeof(Compiler));
    if (!compiler) {
	fprintf(stderr, "Memory allocation failed for Compiler!\n");
	exit(1);
    }

    FILE* output = fopen(output_path, "w");
    if (!output) {
	perror(output_path);
	exit(1);
    }

    compiler->output = output;
    compiler->tokens = tokens;
    compiler->tok_sz = tok_sz;
    compiler->tok_ptr = 0;

    return compiler;
}

void compiler_free(Compiler* compiler) 
{
    free(compiler);
}

void compiler_emit_base(Compiler* compiler)
{
    FILE* out = compiler->output;

    fprintf(out, "BITS 64\n");
    fprintf(out, "segment .text\n");
    fprintf(out, "global _start:\n");
    fprintf(out, "	ret\n");
}

void compiler_emit(Compiler* compiler)
{
    compiler_emit_base(compiler);
}
