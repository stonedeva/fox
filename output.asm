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
	call addr_0
	mov rdi, rax
	mov rax, 60
	syscall
addr_0:
	mov rax, 0
	push rax
	pop [addr_3]
	mov rax, 0
	push rax
	pop [addr_7]
addr_11:
	mov rax, [addr_3]
	push rax
	mov rax, 1000
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	pop rax
	cmp rax, 1
	jne addr_38
	mov rax, [addr_3]
	push rax
	mov rax, 3
	push rax
	pop rax
	pop rbx
	xchg rax, rbx
	xor rdx, rdx
	div rbx
	mov rax, rdx
        push rax
	mov rax, 0
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	mov rax, [addr_3]
	push rax
	mov rax, 5
	push rax
	pop rax
	pop rbx
	xchg rax, rbx
	xor rdx, rdx
	div rbx
	mov rax, rdx
        push rax
	mov rax, 0
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	pop rbx
	or rax, rbx
	push rax
	pop rax
	cmp rax, 1
	jne addr_33
	mov rax, [addr_7]
	push rax
	mov rax, [addr_3]
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	mov [addr_7], rax
addr_33:
	mov rax, [addr_3]
	push rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	mov [addr_3], rax
	jmp addr_11
addr_38:
	mov rax, [addr_7]
	push rax
	pop rdi
	call print
	mov rax, 0
	ret
segment readable writeable
addr_3 dq 0
addr_7 dq 0
