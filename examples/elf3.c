#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

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
        .e_entry = 0x400078, // Entry point must match p_vaddr
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

    // Updated objcode to read from stdin and write to stdout
    char objcode[] = {
        // Read syscall: read(0, buffer, 128)
        0x48, 0x89, 0xd6,               // mov rsi, rdx (buffer address)
        0x48, 0x31, 0xff,               // xor rdi, rdi (file descriptor 0 for stdin)
        0x48, 0xba, 0x80, 0, 0, 0, 0, 0, 0, // mov rdx, 128 (size of input)
        0x0f, 0x05,                     // syscall (read)

        // Write syscall: write(1, buffer, bytes_read)
        0x48, 0x31, 0xff,               // xor rdi, rdi (clear rdi to use as file descriptor)
        0x48, 0xbf, 0x01, 0, 0, 0, 0, 0, 0, // mov rdi, file descriptor 1 (stdout)
        0x48, 0xbe, 0x78, 0, 0x40, 0, 0, 0, 0, // mov rsi, address of buffer
        0x48, 0x89, 0xd3,               // mov rbx, rdx (move bytes read to rbx)
        0x0f, 0x05,                     // syscall (write)

        // Exit syscall: exit(0)
        0xb8, 0x60, 0, 0, 0,           // mov rax, 60 (exit syscall number)
        0x48, 0x31, 0xff,               // xor rdi, rdi (exit code 0)
        0x0f, 0x05                      // syscall (exit)
    };

    size_t objcode_size = sizeof(objcode);

    Elf64_Phdr phdr = {
        .p_type = PT_LOAD,
        .p_offset = 64 + 56, // Offset in file where segment starts
        .p_vaddr = 0x400078,
        .p_paddr = 0x400078,
        .p_filesz = objcode_size,
        .p_memsz = objcode_size,
        .p_flags = PF_X | PF_R,
        .p_align = 0x8
    };

    FILE* f = fopen("bin", "wb"); // 'wb' mode for binary write
    if (!f) {
        perror("fopen");
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

    s = fwrite(objcode, 1, objcode_size, f);
    if (s != objcode_size) {
        perror("fwrite");
        exit(EXIT_FAILURE);
    }

    fclose(f);

    return EXIT_SUCCESS;
}

