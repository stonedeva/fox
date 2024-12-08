format ELF64 executable 0
entry _start
segment readable executable
print:
        mov  r8, -3689348814741910323
        sub     rsp, 40
        mov     BYTE [rsp+31], 10
        lea     rcx, [rsp+30]
.L2:
        mov     rax, rdi
        mul     r8
        mov     rax, rdi
        shr     rdx, 3
        lea     rsi, [rdx+rdx*4]
        add     rsi, rsi
        sub     rax, rsi
        mov     rsi, rcx
        sub     rcx, 1
        add     eax, 48
        mov     BYTE [rcx+1], al
        mov     rax, rdi
        mov     rdi, rdx
        cmp     rax, 9
        ja      .L2
        lea     rdx, [rsp+32]
        mov     edi, 1
        sub     rdx, rsi
        mov     rax, 1
        syscall
        add     rsp, 40
        ret
_start:
	pop [argc]
	pop [argv]
	call addr_2
	mov rdi, rax
	mov rax, 60
	syscall
addr_0:
	pop rbp
	pop r9
	pop r10
	mov rax, 1
	push rax
	mov rax, 1
	push rax
	push r9
	push r10
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	mov rax, 0
	push rbp
	ret
addr_17:
	pop rbp
	pop r9
	pop r10
	mov rax, 1
	push rax
	mov rax, 1
	push rax
	push r9
	push r10
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	mov rax, 0
	push rbp
	ret
addr_2:
	mov rax, str0_len
	push rax
	mov rax, str0
	push rax
	pop [msg]
	mov rax, [msg]
	push rax
	call addr_0
	mov rax, 0
	push rax
	pop rax
	ret
	mov rax, 0
	ret
segment readable writeable
msg dq 0
argc dq 0
argv dq 0
str0 db 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x00
str0_len = 13
mem rb 2400
