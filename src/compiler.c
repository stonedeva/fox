#include "compiler.h"
#include "lib/utils.h"
#include <errno.h>
#include <string.h>

static int addr_counter = 0;
static int block_counter = 0;

Compiler* compiler_init(char* output_path, Lexer* lexer, bool has_entry)
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

    compiler->has_entry = has_entry;
    compiler->output = output;
    compiler->tokens = lexer->tokens;
    compiler->tok_sz = lexer->tok_sz;
    compiler->tok_ptr = 0;
    compiler->var_count = 0;
    compiler->literal_count = 0;

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
    fprintf(out, "puts:\n");
    fprintf(out, "	mov rax, 1\n");
    fprintf(out, "	mov rdi, 1\n");
    fprintf(out, "	syscall\n");
    fprintf(out, "	ret\n");

    fprintf(out, "\nglobal _start\n");
    fprintf(out, "_start:\n");
    if (compiler->has_entry) {
	fprintf(out, "	mov byte [call_flag], 1\n");
	fprintf(out, "	call main\n");
    }
}

void compiler_emit_puts(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t lit_count = compiler->literal_count;
    fprintf(out, "addr_%d:\n", addr_counter);
    fprintf(out, "	mov rsi, str%d\n", lit_count - 1);
    fprintf(out, "	mov rdx, str%d_len\n", lit_count - 1);
    fprintf(out, "	call puts\n");
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

void compiler_emit_reference(Compiler* compiler)
{
    FILE* out = compiler->output;
    char* name = compiler->tokens[compiler->tok_ptr].token;
    name++;

    fprintf(out, "addr_%d:\n", addr_counter);
    fprintf(out, "	mov rax, [%s]\n", name);
    fprintf(out, "	push rax\n");
}

void compiler_emit_func(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
    
    Token name_tok = compiler->tokens[ptr + 1];
    char* name = name_tok.token;

    fprintf(out, "%s:\n", name);
    fprintf(out, "	cmp byte [call_flag], 1\n");
    fprintf(out, "	mov byte [call_flag], 0\n");
    fprintf(out, "	jne block_addr_%d\n", block_counter);
    compiler->tok_ptr++;
}

void compiler_emit_return(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    Token val = compiler->tokens[ptr + 1];
    if (val.type == TOK_NUMBER) {
	fprintf(out, "	mov rax, %s\n", val.token);
    }
    fprintf(out, "	ret\n");
}

void compiler_emit_condition(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "addr_%d:\n", addr_counter);
    fprintf(out, "	pop rax\n");
    fprintf(out, "	cmp rax, 1\n");
    fprintf(out, "	je addr_%d\n", addr_counter + 1);
    fprintf(out, "	jne block_addr_%d\n", block_counter);
}

void compiler_emit_func_call(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    Token name_tok = compiler->tokens[ptr];
    name_tok.token++;
    fprintf(out, "	mov byte [call_flag], 1\n");
    fprintf(out, "	call %s\n", name_tok.token);
    fprintf(out, "addr_%d:\n", addr_counter);
}

void compiler_emit_push(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    Token tok = compiler->tokens[ptr];
    char* val = tok.token;

    fprintf(out, "addr_%d:\n", addr_counter);
    fprintf(out, "	mov rax, %s\n", val);
    fprintf(out, "	push rax\n");
}

void compiler_emit_binaryop(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    Token tok = compiler->tokens[ptr];
    char op = tok.token[0];

    fprintf(out, "addr_%d:\n", addr_counter);
    fprintf(out, "	pop rax\n");
    fprintf(out, "	pop rbx\n");

    switch (op) {
    case '+':
	fprintf(out, "	add rax, rbx\n");
	break;
    case '-':
	fprintf(out, "	sub rax, rbx\n");
	break;
    case '*':
	fprintf(out, "	mul rax\n");
	break;
    case '/':
	fprintf(out, "	div rax\n");
	break;
    case '=':
	fprintf(out, "	cmp rax, rbx\n");
	fprintf(out, "	sete al\n");
	fprintf(out, "	movzx rax, al\n");
	break;
    case '<':
	fprintf(out, "	cmp rax, rbx\n");
	fprintf(out, "	setl al\n");
	fprintf(out, "	movzx rax, al\n");
	break;
    case '>':
	fprintf(out, "	cmp rax, rbx\n");
	fprintf(out, "	setg al\n");
	fprintf(out, "	movzx rax, al\n");
	break;
    }

    fprintf(out, "        push rax\n");
}

void compiler_emit_segments(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "segment .text\n");

    for (size_t i = 0; i < compiler->var_count; i++) {
	Variable var = compiler->vars[i];
	fprintf(out, "%s: db %s\n", var.name, var.value);
    }

    fprintf(out, "segment .data\n");
    fprintf(out, "call_flag db 0\n");
    for (size_t i = 0; i < compiler->literal_count; i++) {
	char* literal = compiler->literals[i];
	size_t lit_len = strlen(literal) - 2;
	
	fprintf(out, "str%d: db %s, 0xA\n", i, literal);
	fprintf(out, "str%d_len: equ $ - str%d\n", i, i);
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
	    compiler_emit_func(compiler);
	    addr_counter++;
	    break;
	case TOK_END:
	    fprintf(out, "block_addr_%d:\n", block_counter);
	    block_counter++;
	    break;
	case TOK_CONDITION:
	    compiler_emit_condition(compiler);
	    addr_counter++;
	    break;
	case TOK_RETURN:
	    compiler_emit_return(compiler);
	    break;
	case TOK_DEF_VAR:
	    compiler_emit_variable(compiler);
	    break;
	case TOK_PRINT:
	    compiler_emit_puts(compiler);
	    addr_counter++;
	    break;
	case TOK_NUMBER:
	    compiler_emit_push(compiler);
	    addr_counter++;
	    break;
	case TOK_BINARYOP:
	    compiler_emit_binaryop(compiler);
	    addr_counter++;
	    break;
	case TOK_STRING_LITERAL:
	    compiler->literals[compiler->literal_count] = tok.token;
	    compiler->literal_count++;
	    break;
	case TOK_FUNC_CALL:
	    compiler_emit_func_call(compiler);
	    addr_counter++;
	    break;
	case TOK_VAR_REF:
	    compiler_emit_reference(compiler);
	    addr_counter++;
	    break;
	case TOK_DROP:
	    fprintf(out, "addr_%d:\n", addr_counter);
	    fprintf(out, "	pop rdi\n");
	    addr_counter++;
	    break;
	default:
	    fprintf(out, "; Unhandled token: %s\n", tok.token);
	    break;
	}

	i = compiler->tok_ptr;
	compiler->tok_ptr++;
    }

    fprintf(out, "addr_%d:\n", addr_counter);
    fprintf(out, "	mov rax, 60\n");
    fprintf(out, "	mov rdi, 0\n");
    fprintf(out, "	syscall\n");

    compiler_emit_segments(compiler);
    fflush(compiler->output);

    compiler_assemble(compiler, false);
}

void compiler_assemble(Compiler* compiler, bool remove_tmp)
{
    system("nasm -felf64 hello.asm && ld -o hello hello.o");

    if (remove_tmp) {
	system("rm -r hello.asm hello.o");
    }
}
