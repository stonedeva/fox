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
	; func
addr_0:
	; var
	; 0
	mov rax, 0
	push rax
	; end
	pop [addr_3]
	; var
	; 0
	mov rax, 0
	push rax
	; end
	pop [addr_7]
	; while
addr_11:
	; index
	mov rax, [addr_3]
	push rax
	; 1000
	mov rax, 1000
	push rax
	; >
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	; do
	pop rax
	cmp rax, 1
	jne addr_38
	; if
	; index
	mov rax, [addr_3]
	push rax
	; 3
	mov rax, 3
	push rax
	; %
	pop rax
	pop rbx
	xchg rax, rbx
	xor rdx, rdx
	div rbx
	mov rax, rdx
        push rax
	; 0
	mov rax, 0
	push rax
	; ==
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	; index
	mov rax, [addr_3]
	push rax
	; 5
	mov rax, 5
	push rax
	; %
	pop rax
	pop rbx
	xchg rax, rbx
	xor rdx, rdx
	div rbx
	mov rax, rdx
        push rax
	; 0
	mov rax, 0
	push rax
	; ==
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	; ||
	pop rax
	pop rbx
	or rax, rbx
	push rax
	; do
	pop rax
	cmp rax, 1
	jne addr_33
	; result
	mov rax, [addr_7]
	push rax
	; index
	mov rax, [addr_3]
	push rax
	; +
	pop rax
	pop rbx
	add rax, rbx
        push rax
	; #result
	pop rax
	mov [addr_7], rax
	; end
addr_33:
	; index
	mov rax, [addr_3]
	push rax
	; 1
	mov rax, 1
	push rax
	; +
	pop rax
	pop rbx
	add rax, rbx
        push rax
	; #index
	pop rax
	mov [addr_3], rax
	; end
	jmp addr_11
addr_38:
	; result
	mov rax, [addr_7]
	push rax
	; print
	pop rdi
	call print
	; end
	mov rax, 0
	ret
segment readable writeable
addr_3 dq 0
addr_7 dq 0
