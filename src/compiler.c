#include "compiler.h"
#include "lib/vector.h"
#include <string.h>

void compiler_proc(parser_t* parser) {
    compiler_t compiler;
    compiler.parser = parser;
    compiler.objcode = vector_init(MAX_BINARY_OPCODES);

    compiler.output = fopen("hello", "w");
    if (compiler.output == NULL) {
	fprintf(stderr, "ERROR: Unable to open output file!\n");
	exit(1);
    }

    _compiler_proc_elf(&compiler);
}

static void _compiler_proc_elf(compiler_t* compiler) {
    _compiler_set_elfheader(compiler);

    char hello_code[] = {
	0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x21, 0xa, // Hello!\n
        0xb8, // mov rax (32bit)
        1, 0, 0, 0, // write syscall 1
        0xbf, // mov rdi (32 bit)
        1, 0, 0, 0, // stdout
        0x48, 0xbe, // mov rsi, 64 bit pointer
        0x78, 0, 0x40, 0, 0, 0, 0, 0, // Hello strings address in virtual memory
        0xba, // mov rdx (32bit)
        7, 0, 0, 0, // number of bytes in Hello!\n
        0xf, 0x5, // syscall
        0xb8, // mov rax (32 bit)
        0x3c, 0, 0, 0, // 60 = exit syscall
        0x48, 0x31, 0xff, // xor rdi, rdi
        0xf, 0x5 // syscall
    };

    vector_push_array(compiler->objcode, hello_code, sizeof(hello_code));

    char* objcode_array = vector_extract_charray(compiler->objcode);

    for (size_t i = 0; i < sizeof(objcode_array) / sizeof(objcode_array[0]); i++) {
	printf("%x, ", objcode_array[i]);
    }
    printf("\n");

    _compiler_write(compiler, objcode_array, sizeof(hello_code));
    free(objcode_array);
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
        .p_flags = PF_X | PF_R | PF_W,
        .p_align = 0x8
    };

    compiler->header = header;
    compiler->phdr = phdr;
}

static void _compiler_write(compiler_t* compiler, char objcode[], size_t objcode_size) {
    size_t sz = fwrite(&compiler->header, 1, sizeof(compiler->header), compiler->output);
    if (sz != sizeof(compiler->header)) {
	fprintf(stderr, "ERROR: sizeof(header) NOT equals sz\n");
	exit(1);
    }

    sz = fwrite(&compiler->phdr, 1, sizeof(compiler->phdr), compiler->output);
    if (sz != sizeof(compiler->phdr)) {
	fprintf(stderr, "ERROR: sizeof(phdr) NOT equals sz\n");
    }

    sz = fwrite(objcode, 1, objcode_size, compiler->output);
    if (sz != objcode_size) {
	fprintf(stderr, "ERROR: sizeof(objcode) NOT equals sz\n");
	exit(1);
    }

    fclose(compiler->output);
}
