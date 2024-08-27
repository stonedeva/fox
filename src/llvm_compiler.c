#include "llvm_compiler.h"
#include "expressions.h"

void compiler_init(parser_t* parser) {
    compiler_t compiler;
    compiler.parser = parser;
    compiler.llvm_context = LLVMContextCreate();
    compiler.llvm_module = LLVMModuleCreateWithNameInContext("fox", compiler.contextcontext);
    compiler.llvm_builder = LLVMCreateBuilderInContext(compiler.context);
}

static void _compile_variable(compiler_t* compiler, variable_expr_t* variable) {
    LLVMValueRef var = LLVMAddGlobal(compiler->module, LLVMInt32TypeInContext(compiler->context), variable->name);
    LLVMSetInitializer(var, create_int32(context, variable->value));
}

static void _compile_function(compiler_t* compiler, function_expr_t* function) {
    LLVMTypeRef type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
    LLVMValueRef func = LLVMAddFunction(compiler->module, function->name, type);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(compiler->context, func, "entry");
    LLVMPositionBuilderAtEnd(compiler->builder, entry);

    for (size_t i = 0; i < function->tokens->size; i++) {
	char* current_tok = function->tokens->data[i];

	if (strcmp(current_tok, "write")) {
	    write_expr_t* write = {
		.content = function->tokens->data[i + 1];
	    }
	    compile_write(compiler->context, compiler->module, compiler->builder, &write);
	}
    }
}
