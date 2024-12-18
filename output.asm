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
	call addr_10
	mov rdi, rax
	mov rax, 60
	syscall
addr_10:
	pop rbp
	mov rax, addr_4
	push rax
	pop rdi
	call print
	mov rax, 0
	push rbp
	ret
segment readable writeable
addr_0 = 8
addr_4 = 800
mem rb 2400
