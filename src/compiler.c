#include "compiler.h"
#include "lib/vector.h"
#include "lib/hex.h"
#include <string.h>

void compiler_proc(parser_t* parser) {
    compiler_t compiler;
    compiler.parser = parser;
    compiler.objcode = vector_init(MAX_BINARY_OPCODES);

    compiler.output = fopen("bin", "wb");
    if (compiler.output == NULL) {
	fprintf(stderr, "ERROR: Unable to open output file!\n");
	exit(1);
    }

    _compiler_proc_elf(&compiler);
}

static void _compiler_proc_elf(compiler_t* compiler) {
    _compiler_set_elfheader(compiler);

#ifdef DEBUG
    _compiler_print_objcode(objcode_array, binary_size);
#endif
}

static void _compiler_set_elfheader(compiler_t* compiler) {
    unsigned char code[] = {
	0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x00, // mov rax, 1 (sys_write)
        0x48, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0x00, // mov rdi, 1 (stdout)
        0x48, 0x8d, 0x35, 0x0c, 0x00, 0x00, 0x00, // lea rsi, [rip + 0x0c] (msg)
        0x48, 0xc7, 0xc2, 0x0e, 0x00, 0x00, 0x00, // mov rdx, 14 (length)
        0x0f, 0x05,                               // syscall
        0x48, 0xc7, 0xc0, 0x3c, 0x00, 0x00, 0x00, // mov rax, 60 (sys_exit)
        0x48, 0x31, 0xff,                         // xor rdi, rdi (exiexit0)
        0x0f, 0x05                                // syscall
    };

    unsigned char message[] = "Hello, World!\n";

    Elf64_Ehdr elf_header = {0};
    memcpy(elf_header.e_ident, ELFMAG, SELFMAG);
    elf_header.e_ident[EI_CLASS] = ELFCLASS64;
    elf_header.e_ident[EI_DATA] = ELFDATA2LSB;
    elf_header.e_ident[EI_VERSION] = EV_CURRENT;
    elf_header.e_ident[EI_OSABI] = ELFOSABI_SYSV;
    elf_header.e_type = ET_EXEC;
    elf_header.e_machine = EM_X86_64;
    elf_header.e_version = EV_CURRENT;
    elf_header.e_entry = 0x400078; // Entry point address
    elf_header.e_phoff = sizeof(Elf64_Ehdr);
    elf_header.e_ehsize = sizeof(Elf64_Ehdr);
    elf_header.e_phentsize = sizeof(Elf64_Phdr);
    elf_header.e_phnum = 1;

    // Program Header
    Elf64_Phdr prog_header = {0};
    prog_header.p_type = PT_LOAD;
    prog_header.p_offset = 0;
    prog_header.p_vaddr = 0x400000;
    prog_header.p_paddr = 0x400000;
    prog_header.p_filesz = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + sizeof(code) + sizeof(message);
    prog_header.p_memsz = prog_header.p_filesz;
    prog_header.p_flags = PF_R | PF_X;
    prog_header.p_align = 0x200000;

    // Writing ELF Header
    fwrite(&elf_header, 1, sizeof(elf_header), compiler->output);

    // Writing Program Header
    fwrite(&prog_header, 1, sizeof(prog_header), compiler->output);

    // Writing code and message
    fwrite(code, 1, sizeof(code), compiler->output);
    fwrite(message, 1, sizeof(message), compiler->output);
}

static void _compiler_print_objcode(char* objcode, size_t objcode_size) {
    printf("Object Code\n=======\n");
    for (size_t i = 0; i < objcode_size; i++) {
	printf("%02x, ", (unsigned char)objcode[i]);
	if ((i + 1) % 16 == 0)
	    printf("\n");
    }
    printf("\n");
}
