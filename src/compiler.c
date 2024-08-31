#include "compiler.h"
#include "expressions.h"

void compiler_init(parser_t* parser, char* module_path) {
    compiler_t compiler;

    LLVMContextRef context = LLVMContextCreate();
    LLVMModuleRef mod = LLVMModuleCreateWithNameInContext(module_path, context);
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

    compiler.module_path = module_path;
    compiler.context = context;
    compiler.mod = mod;
    compiler.builder = builder;
}

void compiler_delete(compiler_t* compiler) {
    compiler = NULL;
    LLVMContextDispose(compiler->context);
    LLVMDisposeModule(compiler->mod);
    LLVMDisposeBuilder(compiler->builder);
}

static void _compiler_emit_function(compiler_t* compiler, function_expr_t* function) {
    LLVMModuleRef mod = compiler->mod;
    char datatype = function->return_type;
    char* name = function->name;
}
