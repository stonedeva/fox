#include "compiler.h"
#include "lib/utils.h"
#include <errno.h>
#include <string.h>
#include <assert.h>

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

    compiler->context = context_init();
    compiler->error = error_init(lexer->filename);
    compiler->has_entry = has_entry;
    compiler->output = output;
    compiler->tokens = lexer->tokens;
    compiler->tok_sz = lexer->tok_sz;
    compiler->tok_ptr = 0;

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

    fprintf(out, "format ELF64 executable 0\n");
    fprintf(out, "entry _start\n");
    fprintf(out, "segment readable executable\n");
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

    fprintf(out, "_start:\n");
    fprintf(out, "	mov byte [call_flag], 1\n");
    fprintf(out, "	call main\n");
}

void compiler_emit_puts(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    fprintf(out, "addr_%d:\n", context->addr_count);
    fprintf(out, "	pop rdx\n");
    fprintf(out, "	pop rsi\n");
    fprintf(out, "	mov rax, 1\n");
    fprintf(out, "	mov rdi, 1\n");
    fprintf(out, "	syscall\n");
}

void compiler_emit_syscall(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    fprintf(out, "addr_%d:\n", context->addr_count);
    fprintf(out, "	pop rdx\n");
    fprintf(out, "	pop rsi\n");
    fprintf(out, "	pop rdi\n");
    fprintf(out, "	pop rax\n");
    fprintf(out, "	syscall\n");
}

void compiler_emit_dump(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    fprintf(out, "addr_%d:\n", context->addr_count);
    fprintf(out, "	pop rdi\n");
    fprintf(out, "	call dump\n");
}

void compiler_emit_var(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
    Context* context = compiler->context;

    Token name = compiler->tokens[ptr + 1];

    context->vars[context->var_count] = (Variable) {
	.name = name.token,
	.value = NULL
    };

    context->var_count++;
    compiler->tok_ptr++;
}

void compiler_emit_redef_var(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
    char* name = compiler->tokens[ptr].token;
    name++;

    Context* context = compiler->context;

    fprintf(out, "addr_%d:\n", compiler->context->addr_count);
    fprintf(out, "	pop rax\n");
    fprintf(out, "	mov [%s], rax\n", name);
}

void compiler_emit_reference(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    char* name = compiler->tokens[compiler->tok_ptr].token;

    bool exists = true;
    for (size_t i = 0; i < context->var_count; i++) {
	if (strcmp(name, context->vars[i].name)) {
	    exists = true;
	}
    }

    if (!exists) {
	error_throw(compiler->error, FATAL, "Unknown typename!", name);
    }

    fprintf(out, "addr_%d:\n", compiler->context->addr_count);
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
    fprintf(out, "	jne block_addr_%d\n", compiler->context->block_count);
    compiler->tok_ptr++;
}

void compiler_emit_return(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "addr_%d:\n", compiler->context->addr_count);
    fprintf(out, "	pop rax\n");
    fprintf(out, "	ret\n");
}

void compiler_emit_condition(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    fprintf(out, "addr_%d:\n", context->addr_count);
    fprintf(out, "	pop rax\n");
    fprintf(out, "	cmp rax, 1\n");
    fprintf(out, "	mov byte [cond_flag], al\n");
    fprintf(out, "	je addr_%d\n", context->addr_count + 1);
    fprintf(out, "	jne endif_addr_%d\n", context->if_count);
}

void compiler_emit_else(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    fprintf(out, "endif_addr_%d:\n", context->if_count);
    fprintf(out, "	cmp [cond_flag], 1\n");
    fprintf(out, "	je endif_addr_%d\n", context->if_count + 1);
}

void compiler_emit_loop(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    fprintf(out, "loopaddr_%d:\n", context->loop_count);
}

void compiler_emit_do(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    fprintf(out, "addr_%d:\n", context->addr_count);
    fprintf(out, "	pop rax\n");
    fprintf(out, "	cmp rax, 1\n");
    fprintf(out, "	je addr_%d\n", context->addr_count + 1);
    fprintf(out, "	jne endloop_addr_%d\n", context->loop_count);
}

void compiler_emit_func_call(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    Token name_tok = compiler->tokens[ptr];
    name_tok.token++;
    fprintf(out, "addr_%d:\n", compiler->context->addr_count);
    fprintf(out, "	mov byte [call_flag], 1\n");
    fprintf(out, "	call %s\n", name_tok.token);
}

void compiler_emit_push(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    Token tok = compiler->tokens[ptr];
    char* val = tok.token;

    fprintf(out, "addr_%d:\n", compiler->context->addr_count);
    fprintf(out, "	mov rax, %s\n", val);
    fprintf(out, "	push rax\n");
}

void compiler_emit_cstr(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    Token cstr = compiler->tokens[compiler->tok_ptr];
    context->literals[context->literal_count] = cstr.token;

    fprintf(out, "addr_%d:\n", context->addr_count);
    fprintf(out, "	mov rax, str%d\n", context->literal_count);
    fprintf(out, "	push rax\n");
    fprintf(out, "	mov rax, str%d_len\n", context->literal_count);
    fprintf(out, "	push rax\n");
    context->literal_count++;
}

void compiler_emit_binaryop(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    Token tok = compiler->tokens[ptr];
    char op = tok.token[0];

    fprintf(out, "addr_%d:\n", compiler->context->addr_count);
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
	fprintf(out, "	mov rcx, rbx\n");
	fprintf(out, "	xor rdx, rdx\n");
	fprintf(out, "	div rcx\n");
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
    case '%':
	fprintf(out, "	xor rdx, rdx\n");
	fprintf(out, "	div rbx\n");
	fprintf(out, "	mov rax, rdx\n");
	break;
    case '&':
	fprintf(out, "	and rax, rbx\n");
	break;
    case '|':
	fprintf(out, "	or rax, rbx\n");
	break;
    case '^':
	fprintf(out, "	xor rax, rbx\n");
	break;
    }

    fprintf(out, "        push rax\n");
}

void compiler_emit_segments(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    fprintf(out, "segment readable writeable\n");

    for (size_t i = 0; i < context->var_count; i++) {
	Variable var = context->vars[i];
	fprintf(out, "%s dq 0\n", var.name);
    }

    fprintf(out, "call_flag db 0\n");
    fprintf(out, "cond_flag db 0\n");

    for (size_t i = 0; i < context->literal_count; i++) {
	char* literal = context->literals[i];
	size_t lit_len = strlen(literal) - 1;

	literal++;
	literal[lit_len - 1] = '\0';
	
	fprintf(out, "str%d db ", i);
	for (size_t i = 0; i < lit_len - 1; i++) {
	    if (literal[i] == '\\' && i + 1 <= lit_len) {
		char escaped = literal[i + 1];
		switch (escaped) {
		case 'n':
		    fprintf(out, "0x%02x, ", (unsigned int)0xA);
		    break;
		}
		i++;
	    } else {
		fprintf(out, "0x%02x, ", (unsigned int)literal[i]);
	    }    
	}
	fprintf(out, "0x%02x\n", (unsigned int)0x00);
	fprintf(out, "str%d_len = %d\n", i, strlen(literal));
    }
}

void compiler_emit_preproc_stmt(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    assert(0 && "TODO: compiler_emit_preproc_stmt() not implemented yet!");
}

void compiler_emit(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    compiler_emit_base(compiler);

    for (size_t i = 0; i < compiler->tok_sz; i++) {
	Token tok = compiler->tokens[i];

	switch (tok.type) {
	case TOK_DEF_FUNC:
	    context_push(context, TOK_DEF_FUNC);
	    compiler_emit_func(compiler);
	    compiler->context->addr_count++;
	    break;
	case TOK_END:
	    TokenType type = context_pop(context);
	    if (type == TOK_CONDITION) {
		fprintf(out, "endif_addr_%d:\n", context->if_count);
		context->if_count++;
		break;
	    }
	    if (type == TOK_DEF_FUNC) {
		fprintf(out, "block_addr_%d:\n", context->block_count);
		context->block_count++;
		break;
	    }
	    if (type == TOK_LOOP) {
		fprintf(out, "	jmp loopaddr_%d\n", context->loop_count);
		fprintf(out, "endloop_addr_%d:\n", context->loop_count);
		context->loop_count++;
		break;
	    }

	    if (type == TOK_DEF_VAR) {
		char* var_name = context->vars[context->var_count - 1].name;
		fprintf(out, "	pop [%s]\n", var_name);
		break;
	    }

	    break;
	case TOK_CONDITION:
	    context_push(context, TOK_CONDITION);
	    compiler_emit_condition(compiler);
	    context->addr_count++;
	    break;
	case TOK_ELSE:
	    compiler_emit_else(compiler);
	    context->if_count++;
	    break;
	case TOK_LOOP:
	    context_push(context, TOK_LOOP);
	    compiler_emit_loop(compiler);
	    context->addr_count++;
	    break;
	case TOK_DO:
	    compiler_emit_do(compiler);
	    context->addr_count++;
	    break;
	case TOK_RETURN:
	    compiler_emit_return(compiler);
	    context->addr_count++;
	    break;
	case TOK_DEF_VAR:
	    context_push(context, TOK_DEF_VAR);
	    compiler_emit_var(compiler);
	    break;
	case TOK_REDEF_VAR:
	    compiler_emit_redef_var(compiler);
	    context->addr_count++;
	    break;
	case TOK_PRINT:
	    compiler_emit_puts(compiler);
	    context->addr_count++;
	    break;
	case TOK_NUMBER:
	    compiler_emit_push(compiler);
	    context->addr_count++;
	    break;
	case TOK_BINARYOP:
	    compiler_emit_binaryop(compiler);
	    context->addr_count++;
	    break;
	case TOK_STRING_LITERAL:
	    compiler_emit_cstr(compiler);
	    context->addr_count++;
	    break;
	case TOK_FUNC_CALL:
	    compiler_emit_func_call(compiler);
	    context->addr_count++;
	    break;
	case TOK_VAR_REF:
	    compiler_emit_reference(compiler);
	    context->addr_count++;
	    break;
	case TOK_DUMP:
	    compiler_emit_dump(compiler);
	    context->addr_count++;
	    break;
	case TOK_SYSCALL:
	    compiler_emit_syscall(compiler);
	    context->addr_count++;
	    break;
	case TOK_PREPROC_STMT:
	    compiler_emit_preproc_stmt(compiler);
	    break;
	default:
	    error_throw(compiler->error, FATAL, "Unknown token!", tok.token);
	}

	i = compiler->tok_ptr;
	compiler->tok_ptr++;
    }

    fprintf(out, "addr_%d:\n", compiler->context->addr_count);
    fprintf(out, "	mov rdi, rax\n");
    fprintf(out, "	mov rax, 60\n");
    fprintf(out, "	syscall\n");



    compiler_emit_segments(compiler);
    fflush(compiler->output);

    compiler_assemble(compiler, false);
}

void compiler_assemble(Compiler* compiler, bool remove_tmp)
{
    system("fasm output.asm");

    if (remove_tmp) {
	system("rm -r hello.asm hello.o");
    }
}
