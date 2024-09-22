#include "compiler.h"
#include "lib/utils.h"
#include <errno.h>
#include <string.h>

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

    fprintf(out, "dump:\n");
    fprintf(out, "        mov  r8, -3689348814741910323\n");
    fprintf(out, "        sub     rsp, 40\n");
    fprintf(out, "        mov     BYTE [rsp+31], 10\n");
    fprintf(out, "        lea     rcx, [rsp+30]\n");
    fprintf(out, ".L2:\n");
    fprintf(out, "        mov     rax, rdi\n");
    fprintf(out, "        mul     r8\n");
    fprintf(out, "        mov     rax, rdi\n");
    fprintf(out, "        shr     rdx, 3\n");
    fprintf(out, "        lea     rsi, [rdx+rdx*4]\n");
    fprintf(out, "        add     rsi, rsi\n");
    fprintf(out, "        sub     rax, rsi\n");
    fprintf(out, "        mov     rsi, rcx\n");
    fprintf(out, "        sub     rcx, 1\n");
    fprintf(out, "        add     eax, 48\n");
    fprintf(out, "        mov     BYTE [rcx+1], al\n");
    fprintf(out, "        mov     rax, rdi\n");
    fprintf(out, "        mov     rdi, rdx\n");
    fprintf(out, "        cmp     rax, 9\n");
    fprintf(out, "        ja      .L2\n");
    fprintf(out, "        lea     rdx, [rsp+32]\n");
    fprintf(out, "        mov     edi, 1\n");
    fprintf(out, "        sub     rdx, rsi\n");
    fprintf(out, "        mov     rax, 1\n");
    fprintf(out, "        syscall\n");
    fprintf(out, "        add     rsp, 40\n");
    fprintf(out, "        ret\n");


    fprintf(out, "\nglobal _start\n");
    fprintf(out, "_start:\n");
    fprintf(out, "	call main\n");
    fprintf(out, "	mov rax, 60\n");
    fprintf(out, "	mov rdi, 0\n");
    fprintf(out, "	syscall\n");
}

void compiler_emit_print(Compiler* compiler)
{
    FILE* out = compiler->output;

    fprintf(out, "	pop rdi\n");
    fprintf(out, "	call dump\n");
}

void compiler_emit_function(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
    char* name = compiler->tokens[ptr + 1];

    fprintf(out, "%s:\n", name);
}

void compiler_emit_push(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
    char* val = compiler->tokens[ptr];

    fprintf(out, "	push %s\n", val);
}

void compiler_emit_binaryop(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    char op = compiler->tokens[ptr][0];

    fprintf(out, "	pop rax\n");
    fprintf(out, "	pop rbx\n");

    switch (op) {
    case '+':
	fprintf(out, "        add rax, rbx\n");
	break;
    case '-':
	fprintf(out, "        sub rax, rbx\n");
	break;
    case '*':
	fprintf(out, "        mul rax, rbx\n");
	break;
    case '/':
	fprintf(out, "        div rax, rbx\n");
	break;
    case '=':
	fprintf(out, "	      cmp rax, rbx\n");
	fprintf(out, "	      sete al\n");
	fprintf(out, "	      movzx rax, al\n");
	break;
    }

    fprintf(out, "        push rax\n");
}

void compiler_emit(Compiler* compiler)
{
    FILE* out = compiler->output;

    compiler_emit_base(compiler);

    for (size_t i = 0; i < compiler->tok_sz; i++) {
	char* tok = compiler->tokens[i];
	if (strcmp("func", tok) == 0) {
	    compiler_emit_function(compiler);
	} else if (strcmp("end", tok) == 0) {
	    fprintf(out, "	ret\n");
	} else if (strcmp("print", tok) == 0) {
	    compiler_emit_print(compiler);
	} else if (utils_is_number(tok)) {
	    compiler_emit_push(compiler);
	} else if (utils_is_operator(tok)) {
	    compiler_emit_binaryop(compiler);
	}

	compiler->tok_ptr++;
    }
}
