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
	mov [argv_ptr], rsp
	call addr_10
	mov rdi, rax
	mov rax, 60
	syscall
addr_10:
	mov rax, addr_4
	push rax
	mov rax, 20
	push rax
	pop rbx
	pop rax
	mov [rax], rbx
	mov rax, addr_4
	push rax
	mov rax, 8
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	mov rax, 30
	push rax
	pop rbx
	pop rax
	mov [rax], rbx
	mov rax, addr_4
	push rax
	mov rax, 16
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	mov rax, 225
	push rax
	pop rbx
	pop rax
	mov [rax], rbx
	mov rax, addr_4
	push rax
	mov rax, 24
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	mov rax, 95
	push rax
	pop rbx
	pop rax
	mov [rax], rbx
	mov rax, 0
	push rax
	pop [addr_31]
	mov rax, 0
	push rax
addr_36:
	push QWORD [rsp]
	mov rax, 4
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	pop rax
	cmp rax, 1
	jne addr_61
	mov rax, addr_4
	push rax
	push QWORD [rsp+8]
	mov rax, addr_0
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov r15, rsp
	mov rax, [addr_31]
	push rax
	push QWORD [r15 + 0]
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	pop rax
	cmp rax, 1
	jne addr_57
	push QWORD [r15 + 0]
	pop rax
	mov [addr_31], rax
addr_57:
	add rsp, 8
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_36
addr_61:
	add rsp, 8
	mov rax, [addr_31]
	push rax
	pop rdi
	call print
	mov rax, 0
	ret
segment readable writeable
addr_0 = 8
addr_4 rb 32
addr_31 dq 0
argc rq 1
argv_ptr rq 1
