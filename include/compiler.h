#ifndef _COMPILER_H_
#define _COMPILER_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <elf.h>
#include <unistd.h>
#include <stdlib.h>
#include "lexer.h"

#define MAX_OBJCODE 255

typedef struct {
    FILE* output;
    lexer_t* lexer;

    /* ELF Executable */
    Elf64_Ehdr header;
    Elf64_Phdr phdr;
    char objcode[];
} compiler_t;

/*
 * Public
*/
void compiler_proc(lexer_t* lexer);

/*
 * Private
*/
static void _compiler_proc_elf(compiler_t* compiler);
static void _compiler_proc_exe(compiler_t* compiler);
static void _compiler_write(compiler_t* compiler, char objcode[]);
static void _compiler_set_elfheader(compiler_t* compiler);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _COMPILER_H_ */
