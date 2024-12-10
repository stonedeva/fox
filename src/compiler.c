#include "compiler.h"
#include "error.h"
#include "lib/utils.h"
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

Compiler compiler_init(Context* context, char* output_path, Lexer* lexer, bool has_entry, size_t mem_capacity)
{
    Compiler compiler = {0};

    FILE* output = fopen(output_path, "a");

    if (!output) {
	perror(output_path);
	exit(1);
    }

    if (context == NULL) {
	compiler.context = context_init();
    } else {
	compiler.context = context;
    }
    compiler.output_path = output_path;
    compiler.input_name = lexer->filename;
    compiler.has_entry = has_entry;
    compiler.output = output;
    compiler.tokens = lexer->tokens;
    compiler.tok_sz = lexer->tok_sz;
    compiler.tok_ptr = 0;
    compiler.mem_capacity = mem_capacity;

    compiler_crossreference(&compiler);

    return compiler;
}

void compiler_free(Compiler* compiler) 
{
    if (compiler->output) {
	fflush(compiler->output);
	fclose(compiler->output);
    }
    free(compiler);
    compiler = NULL;
}

void compiler_crossreference(Compiler* compiler)
{
    size_t stack[200] = {0};
    size_t stack_sz = 0;
    
    for (size_t i = 0; i < compiler->tok_sz; i++) {
	TokenType tok = compiler->tokens[i].type;

	switch (tok) {
	case TOK_LOOP:
	case TOK_CONDITION:
	    stack[stack_sz++] = i;
	    context_push(compiler->context, tok);
	    break;
	case TOK_DEF_VAR:
	case TOK_BINDING:
	    context_push(compiler->context, tok);
	    break;
	case TOK_ELSE:
	    if (context_pop(compiler->context) != TOK_CONDITION) {
		break;
	    }
	    context_push(compiler->context, TOK_ELSE);

	    size_t if_ip = stack[stack_sz - 1];
	    compiler->tokens[if_ip].operand = i;
	    stack[stack_sz - 1] = i;
	    break;
	case TOK_DEF_FUNC:
	    if (strcmp("main", compiler->tokens[i + 1].token) == 0) {
		compiler->context->main_addr = i;
	    }
	    stack[stack_sz++] = i;
	    context_push(compiler->context, TOK_DEF_FUNC);
	    break;
	case TOK_END:
	    TokenType ref = context_pop(compiler->context);
	    if (ref == TOK_DEF_VAR || ref == TOK_BINDING) {
		break;
	    }
	    if (stack_sz < 1) {
		error_throw(compiler, FATAL, "Uncorresponding token 'end'");
	    }
	    size_t ref_ip = stack[stack_sz - 1];
	    compiler->tokens[ref_ip].operand = i;
	    compiler->tokens[i].operand = ref_ip;
	    stack_sz--;
	    break;
	}
    }

    if (stack_sz != 0) {
	error_from_parts(compiler->input_name, FATAL, "Block is unclosed", compiler->tokens[stack_sz - 1]);
    }

    compiler->context->stmt_count = 0;
}

char* compiler_next_tok(Compiler* compiler)
{
    size_t ptr = compiler->tok_ptr;
    return compiler->tokens[ptr + 1].token;
}

char* compiler_prev_tok(Compiler* compiler)
{
    size_t ptr = compiler->tok_ptr;
    return compiler->tokens[ptr - 1].token;
}

char* compiler_curr_tok(Compiler* compiler)
{
    size_t ptr = compiler->tok_ptr;
    return compiler->tokens[ptr].token;
}

void compiler_emit_base(char* out_path, size_t main_addr)
{
    FILE* out = fopen(out_path, "w");
    if (!out) {
	perror(out_path);
	exit(1);
    }

    fprintf(out, "format ELF64 executable 0\n");
    fprintf(out, "entry _start\n");
    fprintf(out, "segment readable executable\n");
    fprintf(out, "print:\n");
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
    fprintf(out, "	pop [argc]\n");
    fprintf(out, "	pop [argv]\n");
    fprintf(out, "	call addr_%d\n", main_addr);
    fprintf(out, "	mov rdi, rax\n");
    fprintf(out, "	mov rax, 60\n");
    fprintf(out, "	syscall\n");

    fclose(out);
}

void compiler_emit_syscall(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "	pop rdx\n");
    fprintf(out, "	pop rsi\n");
    fprintf(out, "	pop rdi\n");
    fprintf(out, "	pop rax\n");
    fprintf(out, "	syscall\n");
    fprintf(out, "	push rax\n");
}

void compiler_emit_print(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "	pop rdi\n");
    fprintf(out, "	call print\n");
}

void compiler_emit_printc(Compiler* compiler)
{
    assert(0 && "TODO: compiler_emit_printc(): Not implemented yet\n");
}

void compiler_emit_dup(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "	pushq [rsp]\n"); 
}

void compiler_emit_swap(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    fprintf(out, "	pop rax\n");
    fprintf(out, "	pop rbx\n");
    fprintf(out, "	push rax\n");
    fprintf(out, "	push rbx\n");
}

void compiler_emit_over(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "	pushq [rsp+8]\n");
}

void compiler_emit_drop(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "	add rsp, 8\n");
}

void compiler_emit_mem(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "	mov rax, mem\n");
    fprintf(out, "	push rax\n");
}

void compiler_emit_binding(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    size_t ptr = compiler->tok_ptr;
    ptr++;

    while (strcmp("in", compiler->tokens[ptr].token) != 0) {
	context->bindings[context->binding_count++] = compiler->tokens[ptr].token;
	ptr++;
    }

    for (size_t i = 0; i < context->binding_count; i++) {
	fprintf(out, "	pop r%d\n", i + 9);
    }
    compiler->tok_ptr = ptr;
}

void compiler_emit_var(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    char* name = compiler_next_tok(compiler);

    Variable var = {
	.name = strdup(name),
	.value = NULL
    };

    context->vars[context->var_count] = var;
    context->var_count++;

    compiler->tok_ptr++;
}

void compiler_emit_redef_var(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
    char* name = compiler_curr_tok(compiler);
    name++;

    Context* context = compiler->context;

    fprintf(out, "	pop rax\n");
    fprintf(out, "	mov [%s], rax\n", name);
}

void compiler_emit_reference(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    char* name = compiler_curr_tok(compiler);
    size_t ptr = compiler->tok_ptr;

    bool exists = false;
    for (size_t i = 0; i < context->var_count; i++) {
	if (strcmp(name, context->vars[i].name) == 0) {
	    exists = true;
	}
    }

    /*if (!exists) {
	error_throw(compiler, FATAL, "Unknown typename!");
    }*/

    fprintf(out, "	mov rax, [%s]\n", name);
    fprintf(out, "	push rax\n");
}

void compiler_emit_ptr_ref(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    char* name = compiler_curr_tok(compiler);
    name++;

    fprintf(out, "	mov rax, %s\n", name);
    fprintf(out, "	push rax\n");
}

void compiler_emit_ptr_set(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    char* name = compiler_curr_tok(compiler);
    name++;

    fprintf(out, "	pop rax\n");
    fprintf(out, "	pop rbx\n");
    fprintf(out, "	mov [rbx], rax\n");
}

void compiler_emit_ptr_get(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    fprintf(out, "	pop rbx\n");
    fprintf(out, "	mov rax, [rbx]\n");
    fprintf(out, "	push rax\n");
}

void compiler_emit_func(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
    Context* context = compiler->context;
    
    char* name = compiler_next_tok(compiler);

    Function func = {
	.name = strdup(name),
	.addr = ptr
    };
    
    context->cw_func = name;
    ptr += 2;

    while (strcmp("in", compiler->tokens[ptr].token) != 0) {
	char* arg_name = compiler->tokens[ptr].token;
	VarType arg_type = typestack_type_from_cstr(arg_name);
	
	if (arg_type == TYPE_INVALID) {
	    error_throw(compiler, FATAL, "Invalid argument type");
	}

	func.args[func.arg_count++] = arg_type;
	ptr++;
    }

    context->funcs[context->func_count] = func;
    context->func_count++;

    fprintf(out, "addr_%d:\n", compiler->tok_ptr);
    if (context->main_addr != func.addr) {
	fprintf(out, "	pop rbp\n");
    }

    compiler->tok_ptr = ptr;
}

void compiler_emit_return(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "	pop rax\n");
    fprintf(out, "	ret\n");
}

void compiler_emit_else(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    
    fprintf(out, "	jmp addr_%d\n", context->temp_addr);
    fprintf(out, "addr_%d:\n", compiler->tok_ptr);
}

void compiler_emit_loop(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    fprintf(out, "addr_%d:\n", compiler->tok_ptr);
}

void compiler_emit_do(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    fprintf(out, "	pop rax\n");
    fprintf(out, "	cmp rax, 1\n");

    TokenType type = context->stmts[context->stmt_count - 1];
    
    switch (type) {
    case TOK_LOOP:
    case TOK_CONDITION:
	fprintf(out, "	jne addr_%d\n", context->temp_addr);
	break;
    default:
	error_throw(compiler, FATAL, "Trying to perform 'do' without context");
	break;
    }
}

void compiler_emit_func_call(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    char* name = compiler_curr_tok(compiler);
    name++;
    
    Function func = context_func_by_name(context, name);
    if (func.name == NULL) {
	error_throw(compiler, FATAL, "Function does not exist");
	return;
    }

    fprintf(out, "	call addr_%d\n", func.addr);
    //fprintf(out, "	push rax\n");
}

void compiler_emit_push(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "	mov rax, %s\n", compiler_curr_tok(compiler));
    fprintf(out, "	push rax\n");
}

void compiler_emit_str(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    size_t ptr = compiler->tok_ptr;

    bool is_cstr = false;

    char* str = compiler_curr_tok(compiler);
    if (context->cw_func == NULL) {
	error_throw(compiler, FATAL, "Strings are not allowed at top-level");
	return;
    }

    if (str[strlen(str) - 1] == 'c') {
	is_cstr = true;
	str[strlen(str) - 1] = '\0';
    }

    context->literals[context->literal_count] = str;

    if (!is_cstr) {
	fprintf(out, "	mov rax, str%d_len\n", context->literal_count);
	fprintf(out, "	push rax\n");
    }
    fprintf(out, "	mov rax, str%d\n", context->literal_count);
    fprintf(out, "	push rax\n");

    context->literal_count++;
}

void compiler_emit_binaryop(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    char* op = compiler_curr_tok(compiler);

    fprintf(out, "	pop rax\n");
    fprintf(out, "	pop rbx\n");

    if (strcmp(op, "==") == 0) {
	fprintf(out, "	cmp rax, rbx\n");
	fprintf(out, "	sete al\n");
	fprintf(out, "	movzx rax, al\n");
	fprintf(out, "	push rax\n");
	return;
    } else if (strcmp(op, "!=") == 0) {
	fprintf(out, "	cmp rax, rbx\n");
	fprintf(out, "	setne al\n");
	fprintf(out, "	movzx rax, al\n");
	fprintf(out, "	push rax\n");
	return;
    } else if (strcmp(op, "&&") == 0) {
	fprintf(out, "	and rax, rbx\n");
	fprintf(out, "	push rax\n");
	return;
    } else if (strcmp(op, "||") == 0) {
	fprintf(out, "	or rax, rbx\n");
	fprintf(out, "	push rax\n");
	return;
    } else if (strcmp(op, "<<") == 0) {
	fprintf(out, "	mov cl, al\n");
	fprintf(out, "	shl rbx, cl\n");
	fprintf(out, "	push rbx\n");
	return;
    } else if (strcmp(op, ">>") == 0) {
	fprintf(out, "	mov cl, al\n");
	fprintf(out, "	shr rbx, cl\n");
	fprintf(out, "	push rbx\n");
	return;
    }

    switch (op[0]) {
    case '+':
	fprintf(out, "	add rax, rbx\n");
	break;
    case '-':
	fprintf(out, "	sub rbx, rax\n");
	fprintf(out, "	mov rax, rbx\n");
	break;
    case '*':
	fprintf(out, "	mul rbx\n");
	break;
    case '/':
	fprintf(out, "	xchg rax, rbx\n");
	fprintf(out, "	xor rdx, rdx\n");
	fprintf(out, "	div rbx\n");
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
	fprintf(out, "	xchg rax, rbx\n");
	fprintf(out, "	xor rdx, rdx\n");
	fprintf(out, "	div rbx\n");
	fprintf(out, "	mov rax, rdx\n");
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

    if (!compiler->has_entry) {
	return;
    }

    fprintf(out, "segment readable writeable\n");

    for (size_t i = 0; i < context->var_count; i++) {
	Variable var = context->vars[i];
	fprintf(out, "%s dq 0\n", var.name);
    }
    
    fprintf(out, "argc dq 0\n");
    fprintf(out, "argv dq 0\n");
    
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
		case 'r':
		    fprintf(out, "0x%02x, ", (unsigned int)0x0D);
		    break;
		case 't':
		    fprintf(out, "0x%02x, ", (unsigned int)0x09);
		    break;
		case 'b':
		    fprintf(out, "0x%02x, ", (unsigned int)0x08);
		    break;
		case 'v':
		    fprintf(out, "0x%02x, ", (unsigned int)0x0B);
		    break;
		case '\\':
		    fprintf(out, "0x%02x, ", (unsigned int)0x5C);
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
    fprintf(out, "mem rb %d\n", compiler->mem_capacity);
}

void compiler_emit_import(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;

    char* path = compiler_next_tok(compiler);
    size_t path_len = strlen(path) - 1;
    path++;
    path[path_len - 1] = '\0';

    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "stdlib/%s", path);

    struct stat buffer;
    if (stat(full_path, &buffer) != 0) {
	error_throw(compiler, FATAL, "Import path not found!");
	return;
    }

    Lexer sub_lexer = lexer_init(full_path);
    lexer_proc(&sub_lexer);

    Compiler sub_compiler = compiler_init(compiler->context, "output.asm", &sub_lexer, false, (size_t)compiler->mem_capacity / 2);
    compiler_emit(&sub_compiler);

    compiler->tok_ptr++;
}

void compiler_emit_macro(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    size_t ptr = compiler->tok_ptr;

    context->macros[context->macro_count++] = (Macro) {
	.name = compiler->tokens[ptr + 1].token,
	.value = compiler->tokens[ptr + 2].token
    };
    compiler->tok_ptr += 2;
}

void compiler_emit(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    for (size_t i = 0; i < compiler->tok_sz; i++) {
	Token tok = compiler->tokens[i];

	for (size_t j = 0; j < context->macro_count; j++) {
	    if (strcmp(tok.token, context->macros[j].name) == 0) {
		strcpy(tok.token, context->macros[j].value);
		tok.type = TOK_NUMBER;
	    }
	}

	bool binding_res = false;
	if (context->active_binding) {
	    for (size_t j = 0; j < context->binding_count; j++) {
		if (strcmp(tok.token, context->bindings[j]) == 0) {
		    fprintf(out, "	push r%d\n", j + 9); 
		    binding_res = true;
		}
	    }
	}

	if (binding_res) {
	    compiler->tok_ptr++;
	    continue;
	}

	switch (tok.type) {
	case TOK_DEF_FUNC:
	    context_push(context, TOK_DEF_FUNC);
	    compiler_emit_func(compiler);
	    break;
	case TOK_END:
	    if (context->stmt_count == 0) {
		error_throw(compiler, FATAL, "Uncorresponding 'end' statement");
		break;
	    }

	    TokenType type = context_pop(context);
	    if (type == TOK_CONDITION) {
		fprintf(out, "addr_%d:\n", i);
		break;
	    }
	    if (type == TOK_DEF_FUNC) {
		fprintf(out, "	mov rax, 0\n");
		if (strcmp("main", context->cw_func) != 0) {
		    fprintf(out, "	push rbp\n");
		}
		fprintf(out, "	ret\n");
		context->cw_func = NULL;
		break;
	    }
	    if (type == TOK_LOOP) {
		fprintf(out, "	jmp addr_%d\n", compiler->tokens[i].operand);
		fprintf(out, "addr_%d:\n", i);
		break;
	    }
	    if (type == TOK_DEF_VAR) {
		char* var_name = context->vars[context->var_count - 1].name;
		fprintf(out, "	pop [%s]\n", var_name);
		break;
	    }
	    if (type == TOK_BINDING) {
		context->active_binding = false;
		context->binding_count = 0;
		break;
	    }

	    break;
	case TOK_CONDITION:
	    context_push(context, TOK_CONDITION);
	    context->temp_addr = compiler->tokens[i].operand;
	    break;
	case TOK_ELSE:
	    context->temp_addr = compiler->tokens[i].operand;
	    compiler_emit_else(compiler);
	    break;
	case TOK_LOOP:
	    context_push(context, TOK_LOOP);
	    context->temp_addr = compiler->tokens[i].operand;
	    compiler_emit_loop(compiler);
	    break;
	case TOK_DO:
	    compiler_emit_do(compiler);
	    break;
	case TOK_RETURN:
	    compiler_emit_return(compiler);
	    break;
	case TOK_DEF_VAR:
	    context_push(context, TOK_DEF_VAR);
	    compiler_emit_var(compiler);
	    break;
	case TOK_REDEF_VAR:
	    compiler_emit_redef_var(compiler);
	    break;
	case TOK_NUMBER:
	    compiler_emit_push(compiler);
	    break;
	case TOK_BINARYOP:
	    compiler_emit_binaryop(compiler);
	    break;
	case TOK_STRING_LITERAL:
	    compiler_emit_str(compiler);
	    break;
	case TOK_FUNC_CALL:
	    if (context->cw_func == NULL) {
		error_throw(compiler, FATAL, "Words are not allowed at top-level");
		return;
	    }
	    compiler_emit_func_call(compiler);
	    break;
	case TOK_VAR_REF:
	    compiler_emit_reference(compiler);
	    break;
	case TOK_PTR_REF:
	    compiler_emit_ptr_ref(compiler);
	    break;
	case TOK_PTR_SET:
	    compiler_emit_ptr_set(compiler);
	    break;
	case TOK_PTR_GET:
	    compiler_emit_ptr_get(compiler);
	    break;
	case TOK_PRINT:
	    compiler_emit_print(compiler);
	    break;
	case TOK_PRINTC:
	    compiler_emit_printc(compiler);
	    break;
	case TOK_DUP:
	    compiler_emit_dup(compiler);
	    break;
	case TOK_SWAP:
	    compiler_emit_swap(compiler);
	    break;
	case TOK_OVER:
	    compiler_emit_over(compiler);
	    break;
	case TOK_DROP:
	    compiler_emit_drop(compiler);
	    break;
	case TOK_MEM:
	    compiler_emit_mem(compiler);
	    break;
	case TOK_SYSCALL:
	    compiler_emit_syscall(compiler);
	    break;
	case TOK_IMPORT:
	    compiler_emit_import(compiler);
	    break;
	case TOK_MACRO_DEF:
	    compiler_emit_macro(compiler);
	    break;
	case TOK_BINDING:
	    context->active_binding = true;
	    context_push(context, TOK_BINDING);
	    compiler_emit_binding(compiler);
	    break;
	default:
	    error_throw(compiler, FATAL, "Unknown token!");
	    break;
	}

	i = compiler->tok_ptr;
	compiler->tok_ptr++;
    }

    compiler_emit_segments(compiler);
    fflush(compiler->output);

    if (compiler->has_entry) {
	compiler_assemble(compiler);
    }
}

void compiler_assemble(Compiler* compiler)
{
    char* command = (char*)malloc(sizeof(strlen(compiler->output_path) + 6));
    if (command == NULL) {
	perror("Allocating memory for assembly command");
	exit(1);
    }
    
    strcpy(command, "fasm ");
    strcat(command, compiler->output_path);

    system(command);

    free(command);
    command = NULL;
}
