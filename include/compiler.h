#ifndef _COMPILER_H_
#define _COMPILER_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <elf.h>
#include <unistd.h>
#include <stdlib.h>
#include "parser.h"

#define MAX_BINARY_OPCODES 255

typedef struct {
    FILE* output;
    parser_t* parser;

    /* ELF Executable */
    Elf64_Ehdr header;
    Elf64_Phdr phdr;
    vector_t* objcode;
} compiler_t;

/*
 * Public
*/
void compiler_proc(parser_t* parser);

/*
 * Private
*/
static void _compiler_proc_elf(compiler_t* compiler);
static void _compiler_proc_exe(compiler_t* compiler);
static void _compiler_proc_nasm(compiler_t* compiler);
static void _compiler_write(compiler_t* compiler, char objcode[], size_t objcode_size);
static void _compiler_set_elfheader(compiler_t* compiler, size_t objcode_size);
static void _compiler_print_objcode(char objcode[]);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _COMPILER_H_ */
