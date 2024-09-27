#include "compiler.h"
#include "lib/utils.h"
#include <errno.h>
#include <string.h>

Compiler* compiler_init(char* output_path, Token* tokens, size_t tok_sz)
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
    compiler->var_count = 0;

    return compiler;
}

void compiler_free(Compiler* compiler) 
{
    if (compiler->output) {
	fflush(compiler->output);
	fclose(compiler->output);
    }
    free(compiler);
}

void compiler_emit_base(Compiler* compiler)
{
    FILE* out = compiler->output;

    fprintf(out, "BITS 64\n");
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

void compiler_emit_variable(Compiler* compiler)
{
    size_t ptr = compiler->tok_ptr;
    Token name = compiler->tokens[ptr + 1];
    Token value = compiler->tokens[ptr + 3];

    compiler->vars[compiler->var_count] = (Variable) {
	.name = name.token,
	.value = value.token
    };

    compiler->var_count++;
    compiler->tok_ptr += 3;
}

void compiler_emit_function(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
    
    Token name_tok = compiler->tokens[ptr + 1];
    char* name = name_tok.token;

    fprintf(out, "%s:\n", name);
}

void compiler_emit_func_call(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    Token name_tok = compiler->tokens[ptr];
    char* name = name_tok.token[ptr + 1];

    fprintf(out, "call %s\n", name);
}

void compiler_emit_push(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    Token tok = compiler->tokens[ptr];
    char* val = tok.token;

    fprintf(out, "	push %s\n", val);
}

void compiler_emit_cstr(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
}

void compiler_emit_binaryop(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    Token tok = compiler->tokens[ptr];
    char op = tok.token[0];

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
	fprintf(out, "        mul rax\n");
	break;
    case '/':
	fprintf(out, "        div rax\n");
	break;
    case '=':
	fprintf(out, "	      cmp rax, rbx\n");
	fprintf(out, "	      sete al\n");
	fprintf(out, "	      movzx rax, al\n");
	break;
    }

    fprintf(out, "        push rax\n");
}

void compiler_emit_textseg(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "segment .text\n");

    for (size_t i = 0; i < compiler->var_count; i++) {
	Variable var = compiler->vars[i];
	fprintf(out, "        %s: db %s\n", var.name, var.value);
    }
}

void compiler_emit(Compiler* compiler)
{
    FILE* out = compiler->output;

    compiler_emit_base(compiler);

    for (size_t i = 0; i < compiler->tok_sz; i++) {
	Token tok = compiler->tokens[i];

	switch (tok.type) {
	case TOK_DEF_FUNC:
	    compiler_emit_function(compiler);
	    break;
	case TOK_END:
	    fprintf(out, "	ret\n");
	    break;
	case TOK_DEF_VAR:
	    compiler_emit_variable(compiler);
	    break;
	case TOK_PRINT:
	    compiler_emit_print(compiler);
	    break;
	case TOK_NUMBER:
	    compiler_emit_push(compiler);
	    break;
	case TOK_BINARYOP:
	    compiler_emit_binaryop(compiler);
	    break;
	default:
	    break;
	}

	i = compiler->tok_ptr;
	compiler->tok_ptr++;
    }

    compiler_emit_textseg(compiler);
    compiler_free(compiler);
}

void compiler_assemble(Compiler* compiler, bool remove_tmp)
{
    system("nasm -felf64 hello.asm");

    if (remove_tmp) {
	system("rm -r hello.asm hello.o");
    }
}
