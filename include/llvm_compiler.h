#ifndef _LLVM_COMPILER_H_
#define _LLVM_COMPILER_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "parser.h"
#include <llvm-c-18/llvm-c/Core.h>
#include <llvm-c-18/llvm-c/ExecutionEngine.h>
#include <llvm-c-18/llvm-c/Target.h>
#include <llvm-c-18/llvm-c/TargetMachine.h>
#include <llvm-c-18/llvm-c/Transforms/PassManagerBuilder.h>

typedef struct {
    LLVMContextRef llvm_context;
    LLVMModuleRef llvm_module;
    LLVMBuilderRef llvm_builder;
    parser_t* parser;
} compiler_t;

void compiler_init(parser_t* parser);

static void _compile_variable(compiler_t* compiler, variable_expr_t* variable);
static void _compile_function(compiler_t* compiler, function_expr_t* function);
static void _compile_write(compiler_t* compiler, write_expr_t* write);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LLVM_COMPILER_H_ */

