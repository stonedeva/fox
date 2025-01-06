#include "compiler.h"
#include "error.h"
#include "lib/utils.h"
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdint.h>

#define MSG_CAP 100

Compiler compiler_init(char* output_path, Lexer* lexer, size_t mem_capacity)
{
    Compiler compiler = {0};
    FILE* output = fopen(output_path, "w");

    if (!output) {
	perror(output_path);
	exit(1);
    }

    compiler.context = context_init();
    compiler.output_path = output_path;
    compiler.input_name = lexer->filename;
    compiler.output = output;
    compiler.tokens = lexer->tokens;
    compiler.tok_sz = lexer->tok_sz;
    compiler.tok_ptr = 0;
    compiler.mem_capacity = mem_capacity;
    compiler.typestack = typestack_init(lexer);

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
    size_t stack[300] = {0};
    size_t stack_sz = 0;
    
    for (size_t i = 0; i < compiler->tok_sz; i++) {
	TokenType tok = compiler->tokens[i].type;

	switch (tok) {
	case TOK_LOOP:
	case TOK_CONDITION:
	case TOK_DEF_MEM:
	case TOK_DEF_VAR:
	case TOK_DEF_CONST:
	case TOK_PEEK:
	case TOK_TAKE:
	    stack[stack_sz++] = i;
	    context_push(compiler->context, tok);
	    break;
	case TOK_ELSE:
	    if (context_pop(compiler->context) != TOK_CONDITION) {
		break;
	    }

	    context_push(compiler->context, tok);

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
	    if (stack_sz < 1) {
		error_from_parts(compiler->input_name, FATAL, 
				"Uncorresponding token 'end'", 
				compiler->tokens[0]);
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

void compiler_emit_base(FILE* out, size_t main_addr)
{
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
    fprintf(out, "	mov [argv_ptr], rsp\n");
    fprintf(out, "	mov rax, ret_stack_end\n");
    fprintf(out, "	mov [ret_stack_rsp], rax\n");
    fprintf(out, "	call addr_%d\n", main_addr);
    fprintf(out, "	mov rax, 60\n");
    fprintf(out, "	mov rdi, 0\n");
    fprintf(out, "	syscall\n");
}

void compiler_emit_syscall(Compiler* compiler)
{
    TypeStack* typestack = compiler->typestack;
    if (typestack->type_count < 4) {
	char err_msg[MSG_CAP];
	sprintf(err_msg, "Operation 'syscall' requires 4 arguments but got %d", 
		typestack->type_count);
	error_throw(compiler, FATAL, err_msg);
    }

    typestack->type_count -= 4;

    FILE* out = compiler->output;
    fprintf(out, "	pop rdx\n");
    fprintf(out, "	pop rsi\n");
    fprintf(out, "	pop rdi\n");
    fprintf(out, "	pop rax\n");
    fprintf(out, "	syscall\n");
    fprintf(out, "	push rax\n");
    
    typestack_push(typestack, INTEGER);
}

void compiler_emit_print(Compiler* compiler)
{
    FILE* out = compiler->output;
    
    TypeStack* typestack = compiler->typestack;
    if (typestack->type_count < 1) {
	error_throw(compiler, FATAL, "Operation 'print' requires one argument");
    }
    (void) typestack_pop(compiler->typestack);

    fprintf(out, "	pop rdi\n");
    fprintf(out, "	call print\n");
}

void compiler_emit_char(Compiler* compiler)
{
    FILE* out = compiler->output;
    char ch = compiler_curr_tok(compiler)[1];
    
    typestack_push(compiler->typestack, BYTE);

    fprintf(out, "	mov rax, %d\n", (int)ch);
    fprintf(out, "	push rax\n");
}

void compiler_emit_dup(Compiler* compiler)
{
    FILE* out = compiler->output;

    TypeStack* typestack = compiler->typestack;
    if (typestack->type_count < 1) {
	error_throw(compiler, FATAL, "Operation 'dup' requires one argument");
    }
    typestack_push(typestack, typestack->types[typestack->type_count - 1]);

    fprintf(out, "	mov rax, [rsp]\n");
    fprintf(out, "	push rax\n"); 
}

void compiler_emit_swap(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    TypeStack* typestack = compiler->typestack;
    if (typestack->type_count < 2) {
	char err_msg[MSG_CAP];
	sprintf(err_msg, "Operation 'swap' requires 2 arguments but got %d",
		typestack->type_count);
	error_throw(compiler, FATAL, err_msg);
    }

    VarType a = typestack_pop(typestack);
    VarType b = typestack_pop(typestack);
    typestack_push(typestack, a);
    typestack_push(typestack, b);

    fprintf(out, "	pop rax\n");
    fprintf(out, "	pop rbx\n");
    fprintf(out, "	push rax\n");
    fprintf(out, "	push rbx\n");
}

void compiler_emit_over(Compiler* compiler)
{
    FILE* out = compiler->output;
    
    TypeStack* typestack = compiler->typestack;
    if (typestack->type_count < 2) {
	char err_msg[MSG_CAP];
	sprintf(err_msg, "Operation 'over' requires 2 arguments but got %d",
		typestack->type_count);
	error_throw(compiler, FATAL, err_msg);
    }
    typestack_push(typestack, typestack->types[typestack->type_count - 2]);

    fprintf(out, "	mov rax, [rsp+8]\n");
    fprintf(out, "	push rax\n");
}

void compiler_emit_rot(Compiler* compiler)
{
    FILE* out = compiler->output;

    TypeStack* typestack = compiler->typestack;
    if (typestack->type_count < 3) {
	char err_msg[MSG_CAP];
	sprintf(err_msg, "Operation 'rot' requires 3 arguments but got %d",
		typestack->type_count);
	error_throw(compiler, FATAL, err_msg);
    }
    VarType a = typestack_pop(typestack);
    VarType b = typestack_pop(typestack);
    VarType c = typestack_pop(typestack);
    typestack_push(typestack, b);
    typestack_push(typestack, c);
    typestack_push(typestack, a);

    fprintf(out, "	mov rax, [rsp + 16]\n");
    fprintf(out, "	mov rbx, [rsp + 8]\n");
    fprintf(out, "	mov rcx, [rsp]\n");
    fprintf(out, "	mov [rsp + 16], rbx\n");
    fprintf(out, "	mov [rsp + 8], rcx\n");
    fprintf(out, "	mov [rsp], rax\n");
}

void compiler_emit_drop(Compiler* compiler)
{
    FILE* out = compiler->output;
    
    TypeStack* typestack = compiler->typestack;
    if (typestack->type_count < 1) {
	error_throw(compiler, FATAL, "Operation 'drop' requires one argument");
    }
    (void) typestack_pop(typestack);

    fprintf(out, "	add rsp, 8\n");
}

void compiler_emit_continue(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t addr = compiler->context->current_loop;
    fprintf(out, "	jmp addr_%d\n", addr);
}

void compiler_emit_bind_def(Compiler* compiler, TokenType type)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    TypeStack* typestack = compiler->typestack;

    size_t ptr = compiler->tok_ptr;
    ptr++;

    while (strcmp("in", compiler->tokens[ptr].token) != 0) {
	context->bindings[context->binding_count++] = (Binding) {
	    .name = compiler->tokens[ptr].token,
	};
	ptr++;
    }
    for (size_t i = 0; i < context->binding_count; i++) {
	context->bindings[i].type = typestack->types[typestack->type_count - context->binding_count + i];
    }
    
    fprintf(out, "	mov r15, rsp\n");
    switch (type) {
    case TOK_TAKE:
	typestack->type_count -= context->binding_count;
	fprintf(out, "	sub rsp, %d\n", 8 * context->binding_count);
	break;
    case TOK_PEEK:
	break;
    default:
	assert(0 && "compiler_emit_bind_def(): Illegal token type provided!\n");
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
	.addr = compiler->tok_ptr,
	.type = INTEGER,
    };

    context->vars[context->var_count++] = var;
    compiler->tok_ptr++;
}

void compiler_emit_redef_var(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
    char* name = compiler_curr_tok(compiler);
    name++;

    Context* context = compiler->context;

    Variable var = context_var_by_name(context, name);
    if (var.name == NULL) {
	error_from_parts(compiler->input_name, FATAL,
			 "Variable in redefinition does not exist",
			 compiler->tokens[ptr]);
    }

    if (var.is_const || var.is_mem) {
	error_from_parts(compiler->input_name, FATAL,
			 "Variable in redefinition is constant or memory",
			 compiler->tokens[ptr]);
    }

    fprintf(out, "	pop rax\n");
    fprintf(out, "	mov [addr_%d], rax\n", var.addr);
}

void compiler_emit_reference(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    char* name = compiler_curr_tok(compiler);
    size_t ptr = compiler->tok_ptr;

    Variable var = context_var_by_name(context, name);
    if (var.name != NULL) {
	typestack_push(compiler->typestack, INTEGER);
	if (var.is_const) {
	    fprintf(out, "	mov rax, %d\n", var.value);
	} else {
	    fprintf(out, "	mov rax, [addr_%d]\n", var.addr);
	}
	fprintf(out, "	push rax\n");
	return;
    }

    Memory mem = context_mem_by_name(context, name);
    if (mem.name == NULL) {
	error_from_parts(compiler->input_name, FATAL,
			 "Reference is neither variable or memory",
			 compiler->tokens[ptr]);
    }
    typestack_push(compiler->typestack, POINTER);

    fprintf(out, "	mov rax, mem\n");
    if (mem.offset > 0) {
	fprintf(out, "	add rax, %d\n", mem.offset);
    }
    fprintf(out, "	push rax\n");
}

void compiler_emit_ptr_ref(Compiler* compiler)
{
    FILE* out = compiler->output;
    size_t ptr = compiler->tok_ptr;
    Context* context = compiler->context;

    char* name = compiler_curr_tok(compiler);
    name++;

    typestack_push(compiler->typestack, POINTER);

    Variable var = context_var_by_name(context, name);
    if (var.name == NULL) {
	error_from_parts(compiler->input_name, FATAL,
			 "Variable in pointer does not exist",
			 compiler->tokens[ptr]);
    }

    fprintf(out, "	mov rax, addr_%d\n", var.addr);
    fprintf(out, "	push rax\n");
}

void compiler_emit_ptr_set(Compiler* compiler, TokenType type)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    TypeStack* typestack = compiler->typestack;
    char err_msg[MSG_CAP];
    if (typestack->type_count < 2) {
	sprintf(err_msg, "Operation 'set' requires 2 arguments but got %d",
		typestack->type_count);
	error_throw(compiler, FATAL, err_msg);
    }
    VarType a = typestack_pop(typestack);
    VarType b = typestack_pop(typestack);
    if (a != INTEGER) {
	sprintf(err_msg, "Operation 'set' expected 'int' as 2 argument but got '%s'",
		typestack_cstr_from_type(a));
	error_throw(compiler, FATAL, err_msg);
    }
    if (b != POINTER) {
	sprintf(err_msg, "Operation 'set' expected 'ptr' as 1 argument but got '%s'",
		typestack_cstr_from_type(b));
	error_throw(compiler, FATAL, err_msg);
    }

    char* name = compiler_curr_tok(compiler);
    name++;

    switch (type) {
    case TOK_PTR_SET8:
	fprintf(out, "	pop rbx\n");
	fprintf(out, "	pop rax\n");
	fprintf(out, "	mov [rax], bl\n");
	break;
    case TOK_PTR_SET32:
	fprintf(out, "	pop rbx\n");
	fprintf(out, "	pop rax\n");
	fprintf(out, "	mov [rax], ebx\n");
	break;
    case TOK_PTR_SET64:
	fprintf(out, "	pop rbx\n");
	fprintf(out, "	pop rax\n");
	fprintf(out, "	mov [rax], rbx\n");
	break;
    default:
	assert(0 && "compiler_emit_ptr_set(): Illegal token type provided!\n");
    }
}

void compiler_emit_ptr_get(Compiler* compiler, TokenType type)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;

    TypeStack* typestack = compiler->typestack;
    if (typestack->type_count < 1) {
	error_throw(compiler, FATAL, "Operation 'get' requires one argument");
    }

    VarType a = typestack_pop(typestack);
    if (a != POINTER) {
	char err_msg[MSG_CAP];
	sprintf(err_msg, "Operation 'get' expected 'ptr' but got '%s'",
		typestack_cstr_from_type(a));
	error_throw(compiler, FATAL, err_msg);
    }

    switch (type) {
    case TOK_PTR_GET8:
	fprintf(out, "	pop rax\n");
	fprintf(out, "	xor rbx, rbx\n");
	fprintf(out, "	mov bl, [rax]\n");
	fprintf(out, "	push rbx\n");
	break;
    case TOK_PTR_GET32:
	fprintf(out, "	pop rax\n");
	fprintf(out, "	xor rbx, rbx\n");
	fprintf(out, "	mov ebx, [rax]\n");
	fprintf(out, "	push rbx\n");
	break;
    case TOK_PTR_GET64:
	fprintf(out, "	pop rax\n");
	fprintf(out, "	xor rbx, rbx\n");
	fprintf(out, "	mov rbx, [rax]\n");
	fprintf(out, "	push rbx\n");
	break;
    default:
	assert(0 && "compiler_emit_ptr_get(): Illegal token type provided!\n"); 
    }
    typestack_push(typestack, INTEGER);
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
	typestack_push(compiler->typestack, arg_type);

	func.args[func.arg_count++] = arg_type;
	ptr++;
    }

    context->funcs[context->func_count] = func;
    context->func_count++;

    fprintf(out, "addr_%d:\n", compiler->tok_ptr);
    fprintf(out, "	mov [ret_stack_rsp], rsp\n");
    fprintf(out, "	mov rsp, rax\n");

    compiler->tok_ptr = ptr;
}

void compiler_emit_return(Compiler* compiler)
{
    FILE* out = compiler->output;
    fprintf(out, "	mov rax, rsp\n");
    fprintf(out, "	mov rsp, [ret_stack_rsp]\n");
    fprintf(out, "	ret\n");
    compiler->context->cw_func = NULL;
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

    TypeStack* typestack = compiler->typestack;
    if (typestack->type_count < 1) {
	error_throw(compiler, FATAL, "Operation 'do' requires one argument");
    }
    (void) typestack_pop(typestack);

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

    TypeStack* typestack = compiler->typestack;
    char err_msg[MSG_CAP];
    if (typestack->type_count < func.arg_count) {
	sprintf(err_msg, "Function '%s' expected %d arguments but got %d",
		func.name, func.arg_count, typestack->type_count);
	error_throw(compiler, FATAL, err_msg);
    }

    for (size_t i = 0; i < func.arg_count; i++) {
	VarType actual_type = typestack_pop(typestack);
	VarType expected_type = func.args[func.arg_count - i - 1];
	if (actual_type != expected_type) {
	    sprintf(err_msg, "Function '%s' expected '%s' as %d argument but got '%s'", 
		    func.name, typestack_cstr_from_type(expected_type), i + 1, 
		    typestack_cstr_from_type(actual_type));
	    error_throw(compiler, FATAL, err_msg);
	}
    }

    fprintf(out, "	mov rax, rsp\n");
    fprintf(out, "	mov rsp, [ret_stack_rsp]\n");
    fprintf(out, "	call addr_%d\n", func.addr);
    fprintf(out, "	mov [ret_stack_rsp], rsp\n");
    fprintf(out, "	mov rsp, rax\n");
}

void compiler_emit_number(Compiler* compiler)
{
    FILE* out = compiler->output;
    typestack_push(compiler->typestack, INTEGER);

    fprintf(out, "	mov rax, %s\n", compiler_curr_tok(compiler));
    fprintf(out, "	push rax\n");
}

void compiler_emit_str(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    size_t ptr = compiler->tok_ptr;

    TypeStack* typestack = compiler->typestack;
    typestack_push(typestack, INTEGER);
    typestack_push(typestack, POINTER);

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
    
    TypeStack* typestack = compiler->typestack;
    if (typestack->type_count < 2) {
	char err_msg[MSG_CAP];
	sprintf(err_msg, "Operation '%s' requires 2 arguments but got %d",
		op, typestack->type_count);
	error_throw(compiler, FATAL, err_msg);
    }
    VarType a = typestack_pop(typestack);
    VarType b = typestack_pop(typestack);

    fprintf(out, "	pop rax\n");
    fprintf(out, "	pop rbx\n");

    if (strcmp(op, "==") == 0) {
	typestack_push(typestack, BOOLEAN);
	fprintf(out, "	cmp rax, rbx\n");
	fprintf(out, "	sete al\n");
	fprintf(out, "	movzx rax, al\n");
	fprintf(out, "	push rax\n");
	return;
    } else if (strcmp(op, "!=") == 0) {
	typestack_push(typestack, BOOLEAN);
	fprintf(out, "	cmp rax, rbx\n");
	fprintf(out, "	setne al\n");
	fprintf(out, "	movzx rax, al\n");
	fprintf(out, "	push rax\n");
	return;
    } else if (strcmp(op, "&&") == 0) {
	typestack_push(typestack, BOOLEAN);
	fprintf(out, "	and rax, rbx\n");
	fprintf(out, "	push rax\n");
	return;
    } else if (strcmp(op, "||") == 0) {
	typestack_push(typestack, BOOLEAN);
	fprintf(out, "	or rax, rbx\n");
	fprintf(out, "	push rax\n");
	return;
    } else if (strcmp(op, "<<") == 0) {
	typestack_push(typestack, INTEGER);
	fprintf(out, "	mov cl, al\n");
	fprintf(out, "	shl rbx, cl\n");
	fprintf(out, "	push rbx\n");
	return;
    } else if (strcmp(op, ">>") == 0) {
	typestack_push(typestack, INTEGER);
	fprintf(out, "	mov cl, al\n");
	fprintf(out, "	shr rbx, cl\n");
	fprintf(out, "	push rbx\n");
	return;
    }

    switch (op[0]) {
    case '+':
	if (a == POINTER || b == POINTER) {
	    typestack_push(typestack, POINTER);
	} else {
	    typestack_push(typestack, INTEGER);
	}
	fprintf(out, "	add rax, rbx\n");
	break;
    case '-':
	if (a == POINTER || b == POINTER) {
	    typestack_push(typestack, POINTER);
	} else {
	    typestack_push(typestack, INTEGER);
	}
	fprintf(out, "	sub rbx, rax\n");
	fprintf(out, "	mov rax, rbx\n");
	break;
    case '*':
	typestack_push(typestack, INTEGER);
	fprintf(out, "	mul rbx\n");
	break;
    case '/':
	typestack_push(typestack, INTEGER);
	fprintf(out, "	xchg rax, rbx\n");
	fprintf(out, "	xor rdx, rdx\n");
	fprintf(out, "	div rbx\n");
	break;
    case '<':
	typestack_push(typestack, INTEGER);
	fprintf(out, "	cmp rax, rbx\n");
	fprintf(out, "	setl al\n");
	fprintf(out, "	movzx rax, al\n");
	break;
    case '>':
	typestack_push(typestack, INTEGER);
	fprintf(out, "	cmp rax, rbx\n");
	fprintf(out, "	setg al\n");
	fprintf(out, "	movzx rax, al\n");
	break;
    case '%':
	typestack_push(typestack, INTEGER);
	fprintf(out, "	xchg rax, rbx\n");
	fprintf(out, "	xor rdx, rdx\n");
	fprintf(out, "	div rbx\n");
	fprintf(out, "	mov rax, rdx\n");
	break;
    case '^':
	typestack_push(typestack, INTEGER);
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
    if (compiler->used_mem > compiler->mem_capacity) {
	error_throw(compiler, WARNING, "Maximum memory capacity has been exceed");
	fprintf(out, "mem rb %d\n", compiler->mem_capacity);
    } else {
	fprintf(out, "mem rb %d\n", compiler->used_mem);
    }
    fprintf(out, "ret_stack_rsp rq 1\n");
    fprintf(out, "ret_stack rb 2400\n");
    fprintf(out, "ret_stack_end:\n");

    for (size_t i = 0; i < context->var_count; i++) {
	Variable var = context->vars[i];
	if (!var.is_const) {
	    fprintf(out, "addr_%d dq 0\n", var.addr);
	}
    }

    fprintf(out, "argc rq 1\n");
    fprintf(out, "argv_ptr rq 1\n");
    
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
		case '0':
		    fprintf(out, "0x%02x, ", (unsigned int)0x00);
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
}

void compiler_eval_end(Compiler* compiler)
{
    TokenType type = context_pop(compiler->context);
    Context* context = compiler->context;
    FILE* out = compiler->output;
    size_t i = compiler->tok_ptr;
    
    switch (type) {
    case TOK_CONDITION:
	fprintf(out, "addr_%d:\n", i);
	break;
    case TOK_DEF_FUNC:
	fprintf(out, "	mov rax, rsp\n");
	fprintf(out, "	mov rsp, [ret_stack_rsp]\n");
	fprintf(out, "	ret\n");
	context->cw_func = NULL;
	break;
    case TOK_LOOP:
	fprintf(out, "	jmp addr_%d\n", compiler->tokens[i].operand);
	fprintf(out, "addr_%d:\n", i);
	break;
    case TOK_DEF_VAR:
	size_t var_addr = context->vars[context->var_count - 1].addr;
	fprintf(out, "	pop [addr_%d]\n", var_addr);
	break;
    case TOK_TAKE:
    case TOK_PEEK:
	context->active_binding = false;
	context->binding_count = 0;
	break;
    }
}

void compiler_emit_argc(Compiler* compiler)
{
    FILE* out = compiler->output;
    typestack_push(compiler->typestack, INTEGER);

    fprintf(out, "	mov rax, [argc]\n");
    fprintf(out, "	push rax\n");
}

void compiler_emit_argv(Compiler* compiler)
{
    FILE* out = compiler->output;
    typestack_push(compiler->typestack, POINTER);

    fprintf(out, "	mov rax, [argv_ptr]\n");
    fprintf(out, "	push rax\n");
}

uint64_t compiler_eval_const(Compiler* compiler)
{
    size_t ptr = compiler->tok_ptr;
    size_t eval_stack[20] = {0};
    size_t eval_stack_sz = 0;

    while (compiler->tokens[ptr].type != TOK_END) {
	Token tok = compiler->tokens[ptr];
	if (tok.type == TOK_NUMBER) {
	    eval_stack[eval_stack_sz++] = utils_cstr_as_number(tok.token);
	} else if (tok.type == TOK_BINARYOP) {
	    switch (tok.token[0]) {
	    case '+':
		eval_stack[eval_stack_sz - 2] += eval_stack[eval_stack_sz - 1];
		eval_stack_sz--;
		break;
	    case '-':
		eval_stack[eval_stack_sz - 2] -= eval_stack[eval_stack_sz - 1];
		eval_stack_sz--;
		break;
	    case '*':
		eval_stack[eval_stack_sz - 2] *= eval_stack[eval_stack_sz - 1];
		eval_stack_sz--;
		break;
	    case '/':
		eval_stack[eval_stack_sz - 2] /= eval_stack[eval_stack_sz - 1];
		eval_stack_sz--;
		break;
	    }
	} else if (tok.type == TOK_VAR_REF) {
	    Variable var = context_var_by_name(compiler->context, tok.token);
	    if (var.name == NULL) {
		error_from_parts(compiler->input_name, FATAL, 
				 "Unknown variable in 'const' definition",
				 compiler->tokens[ptr]);
	    }
	    eval_stack[eval_stack_sz++] = var.value;
	}
	ptr++;
    }

    if (eval_stack_sz != 1) {	
	error_from_parts(compiler->input_name, FATAL, "Unused data from 'const'", 
			 compiler->tokens[ptr]);
    }

    compiler->tok_ptr = ptr;

    return eval_stack[0];
}

void compiler_emit_const_def(Compiler* compiler)
{
    Context* context = compiler->context;

    size_t addr = compiler->tok_ptr;
    char* name = compiler_next_tok(compiler);
    compiler->tok_ptr += 2;
    uint64_t val = compiler_eval_const(compiler);

    context->vars[context->var_count++] = (Variable) {
	.name = name,
	.type = INTEGER,
	.value = val,
	.addr = addr,
	.is_const = true
    };
}

void compiler_emit_mem_def(Compiler* compiler)
{
    Context* context = compiler->context;

    size_t addr = compiler->tok_ptr;
    char* name = compiler_next_tok(compiler);
    compiler->tok_ptr += 2;
    uint64_t val = compiler_eval_const(compiler);

    context->memories[context->memory_count++] = (Memory) {
	.name = name,
	.addr = addr,
	.offset = compiler->used_mem
    };
    compiler->used_mem += val;
}

void compiler_emit(Compiler* compiler)
{
    FILE* out = compiler->output;
    Context* context = compiler->context;
    TypeStack* typestack = compiler->typestack;
    
    compiler_emit_base(out, context->main_addr);

    for (size_t i = 0; i < compiler->tok_sz; i++) {
	Token tok = compiler->tokens[i];

	// Binding
	bool binding_res = false;
	if (context->active_binding) {
	    for (size_t j = 0; j < context->binding_count; j++) {
		Binding binding = context->bindings[j];
		if (strcmp(tok.token, binding.name) == 0) {
		    typestack_push(compiler->typestack, binding.type);

		    size_t addr = (context->binding_count - j - 1) * 8;
		    fprintf(out, "	mov rax, [r15 + %d]\n", addr);
		    fprintf(out, "	push rax\n");
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
	    
	    compiler_eval_end(compiler);

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
	    context->current_loop = compiler->tok_ptr;
	    context_push(context, TOK_LOOP);
	    context->temp_addr = compiler->tokens[i].operand;
	    compiler_emit_loop(compiler);
	    break;
	case TOK_CONTINUE:
	    compiler_emit_continue(compiler);
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
	    compiler_emit_number(compiler);
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
	case TOK_PTR_SET8:
	case TOK_PTR_SET32:
	case TOK_PTR_SET64:
	    compiler_emit_ptr_set(compiler, tok.type);
	    break;
	case TOK_PTR_GET8:
	case TOK_PTR_GET32:
	case TOK_PTR_GET64:
	    compiler_emit_ptr_get(compiler, tok.type);
	    break;
	case TOK_PRINT:
	    compiler_emit_print(compiler);
	    break;
	case TOK_CHAR:
	    compiler_emit_char(compiler);
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
	case TOK_ROT:
	    compiler_emit_rot(compiler);
	    break;
	case TOK_DROP:
	    compiler_emit_drop(compiler);
	    break;
	case TOK_DEF_MEM:
	    compiler_emit_mem_def(compiler);
	    break;
	case TOK_SYSCALL:
	    compiler_emit_syscall(compiler);
	    break;
	case TOK_DEF_CONST:
	    compiler_emit_const_def(compiler);
	    break;
	case TOK_TAKE:
	case TOK_PEEK:
	    context->active_binding = true;
	    context_push(context, tok.type);
	    compiler_emit_bind_def(compiler, tok.type);
	    break;
	case TOK_ARGC:
	    compiler_emit_argc(compiler);
	    break;
	case TOK_ARGV:
	    compiler_emit_argv(compiler);
	    break;
	default:
	    error_throw(compiler, FATAL, "Unknown token!");
	    break;
	}

	i = compiler->tok_ptr;
	compiler->tok_ptr++;
    }

    size_t type_count = typestack->type_count;
    if (type_count > 0) {
	char err_msg[MSG_CAP];
	sprintf(err_msg, "%d unhandled type(s) on the stack", type_count);
	error_throw(compiler, WARNING, err_msg);
    }

    compiler_emit_segments(compiler);
    fflush(compiler->output);

    compiler_assemble(compiler);
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
