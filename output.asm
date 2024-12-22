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
	call addr_17
	mov rdi, rax
	mov rax, 60
	syscall
	; func
addr_0:
	pop rbp
	; peek
	mov r15, rsp
	push QWORD [r15 + 8]
	push QWORD [r15 + 0]
	; +
	pop rax
	pop rbx
	add rax, rbx
        push rax
	; print
	pop rdi
	call print
	; end
	; drop
	add rsp, 8
	; drop
	add rsp, 8
	; end
	mov rax, 0
	push rbp
	ret
	; func
addr_17:
	; 205
	mov rax, 205
	push rax
	; 95
	mov rax, 95
	push rax
	; @sum
	call addr_0
	; end
	mov rax, 0
	ret
segment readable writeable
