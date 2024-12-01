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
	call addr_0
	mov rdi, rax
	mov rax, 60
	syscall
addr_0:
	mov rax, 0
	push rax
	pop [count]
	mov rax, 0
	push rax
	pop [res1]
	mov rax, 0
	push rax
	pop [res2]
addr_15:
	mov rax, [count]
	push rax
	mov rax, 100
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	pop rax
	cmp rax, 1
	jne addr_30
	mov rax, [count]
	push rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	mov [count], rax
	mov rax, [res1]
	push rax
	mov rax, [count]
	push rax
	mov rax, [count]
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
	mov [res1], rax
	jmp addr_15
addr_30:
addr_31:
	mov rax, 0
	push rax
	mov rax, [count]
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	pop rax
	cmp rax, 1
	jne addr_44
	mov rax, [res2]
	push rax
	mov rax, [count]
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	mov [res2], rax
	mov rax, [count]
	push rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	sub rbx, rax
	mov rax, rbx
        push rax
	pop rax
	mov [count], rax
	jmp addr_31
addr_44:
	mov rax, [res2]
	push rax
	mov rax, [res2]
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	mov [res2], rax
	mov rax, [res2]
	push rax
	mov rax, [res1]
	push rax
	pop rax
	pop rbx
	sub rbx, rax
	mov rax, rbx
        push rax
	pop rdi
	call print
	mov rax, 0
	ret
segment readable writeable
count dq 0
res1 dq 0
res2 dq 0
argc dq 0
argv dq 0
mem rb 2400
