#ifndef _LLVM_COMPILER_H_
#define _LLVM_COMPILER_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "parser.h"
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/Transforms/PassManagerBuilder.h>
#include <llvm-c/Analysis.h>
#include <stdio.h>

typedef struct {
    char* module_path;
    LLVMContextRef context;
    LLVMModuleRef mod;
    LLVMBuilderRef builder;
    parser_t* parser;
} compiler_t;

void compiler_init(parser_t* parser, char* module_path);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LLVM_COMPILER_H_ */

