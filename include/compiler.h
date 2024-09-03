#ifndef _LLVM_COMPILER_H_
#define _LLVM_COMPILER_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "parser.h"
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/Transforms/PassManagerBuilder.h>
#include <llvm-c/Core.h>
#include <llvm-c/DebugInfo.h>
#include <stdio.h>

typedef struct {
    LLVMTargetRef target;
    LLVMTargetMachineRef target_machine;
    LLVMExecutionEngineRef engine;
} llvm_target_t;

typedef struct {
    char* module_path;
    char* output_path;
    LLVMContextRef context;
    LLVMModuleRef mod;
    LLVMBuilderRef builder;
    parser_t* parser;
    llvm_target_t* target;
} compiler_t;

void compiler_init(parser_t* parser, char* module_path, char* output_path);
void compiler_delete(compiler_t* compiler);
void compiler_init_target(compiler_t* compiler);
static void _compiler_throw_error(char* error);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LLVM_COMPILER_H_ */

