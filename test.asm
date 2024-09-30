format ELF64 executable 0
entry main
segment readable executable

main:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, len
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall

segment readable writeable

msg db "Hello World!", 10
len = $ - msg 
