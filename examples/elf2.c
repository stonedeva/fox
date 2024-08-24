#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
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
        .e_entry = 0x400078,
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
        .p_offset = 0x78, // Align with the entry point
        .p_vaddr = 0x400078,
        .p_paddr = 0x400078,
        .p_filesz = 48,
        .p_memsz = 48,
        .p_flags = PF_X | PF_R | PF_W, // Executable, readable, and writable
        .p_align = 0x200000
    };

    char objcode[] = {
        0xb8, 0x00, 0x00, 0x00, 0x00, // mov rax, 0 (syscall number for read)
        0xbf, 0x00, 0x00, 0x00, 0x00, // mov rdi, 0 (stdin)
        0x48, 0xbe, 0x88, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rsi, 0x400088 (buffer address)
        0xba, 0x01, 0x00, 0x00, 0x00, // mov rdx, 1 (number of bytes to read)
        0x0f, 0x05,                   // syscall
        0xb8, 0x3c, 0x00, 0x00, 0x00, // mov rax, 60 (syscall number for exit)
        0x48, 0x31, 0xff,             // xor rdi, rdi (exit status 0)
        0x0f, 0x05,                   // syscall
        0x00                          // Buffer to store input, initialized to 0
    };

    FILE* f = fopen("bin", "w");
    if (!f) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    size_t s = fwrite(&header, 1, sizeof(header), f);
    if (s != sizeof(header)) {
        perror("fwrite");
        exit(EXIT_FAILURE);
    }

    s = fwrite(&phdr, 1, sizeof(phdr), f);
    if (s != sizeof(phdr)) {
        perror("fwrite");
        exit(EXIT_FAILURE);
    }

    s = fwrite(objcode, 1, sizeof(objcode), f);
    if (s != sizeof(objcode)) {
        perror("fwrite");
        exit(EXIT_FAILURE);
    }

    fclose(f);

    return EXIT_SUCCESS;
}

