#include "compiler.h"
#include "lib/vector.h"
#include <string.h>

void compiler_proc(lexer_t* lexer) {
    compiler_t compiler;
    compiler.lexer = lexer;

    compiler.output = fopen("hello", "wb");
    if (compiler.output == NULL) {
	fprintf(stderr, "ERROR: Unable to open output file!\n");
	exit(1);
    }

    _compiler_proc_elf(&compiler);
}

static void _compiler_proc_elf(compiler_t* compiler) {
    vector_t* tokens = compiler->lexer->tokens;
    _compiler_set_elfheader(compiler);

    char objcode[] = {};

    size_t i;
    while (i < tokens->size) {
	char* tok = vector_get(tokens, i);
	size_t next_code = sizeof(objcode) / sizeof(objcode[0]);

	i++;
    }

    _compiler_write(compiler, objcode);
}

static void _compiler_set_elfheader(compiler_t* compiler) {
    Elf64_Ehdr header = {
        .e_ident = {
            ELFMAG0,
            ELFMAG1,
            ELFMAG2,
            ELFMAG3,
            ELFCLASS64,
            ELFDATA2LSB,
            EV_CURRENT,
            ELFOSABI_SYSV,
            0, 0, 0, 0, 0, 0, 0, 0
        },
        .e_type = ET_EXEC,
        .e_machine = EM_X86_64,
        .e_entry = 0x40007f,
        .e_phoff = 64,
        .e_shoff = 0,
        .e_flags = 0,
        .e_ehsize = 64,
        .e_phentsize = 56,
        .e_phnum = 1,
        .e_shentsize = 64,
        .e_shnum = 0,
        .e_shstrndx = SHN_UNDEF
    };

    Elf64_Phdr phdr = {
        .p_type = PT_LOAD,
        .p_offset = 0x78, // 64 + 56 = 120
        .p_vaddr = 0x400078,
        .p_paddr = 0x400078,
        .p_filesz = 44,
        .p_memsz = 44,
        .p_flags = PF_X | PF_R,
        .p_align = 0x8
    };

    compiler->header = header;
    compiler->phdr = phdr;
}

static void _compiler_write(compiler_t* compiler, char objcode[]) {
    size_t sz = fwrite(&compiler->header, 1, sizeof(compiler->header), compiler->output);
    if (sz != sizeof(compiler->header)) {
	fprintf(stderr, "ERROR: sizeof(header) NOT equals sz\n");
	exit(1);
    }

    sz = fwrite(&compiler->phdr, 1, sizeof(compiler->phdr), compiler->output);
    if (sz != sizeof(compiler->phdr)) {
	fprintf(stderr, "ERROR: sizeof(phdr) NOT equals sz\n");
    }

    sz = fwrite(objcode, 1, sizeof(objcode), compiler->output);
    if (sz != sizeof(objcode)) {
	fprintf(stderr, "ERROR: sizeof(objcode) NOT equals sz\n");
	exit(1);
    }

    fclose(compiler->output);
}
