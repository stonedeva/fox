format ELF64 executable 0
entry _start
segment readable executable
dump:
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
	mov byte [call_flag], 1
	call main
main:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_0
addr_1:
	mov rax, 1
	push rax
	pop [a]
addr_2:
	mov rax, 2
	push rax
	pop [b]
addr_3:
	mov rax, 0
	push rax
	pop [sum]
addr_4:
	mov rax, 0
	push rax
	pop [next_fib]
loopaddr_0:
addr_6:
	mov rax, [a]
	push rax
addr_7:
	mov rax, 4000000
	push rax
addr_8:
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
        push rax
addr_9:
	mov rax, [a]
	push rax
addr_10:
	mov rax, 4000000
	push rax
addr_11:
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
addr_12:
	pop rax
	pop rbx
	or rax, rbx
        push rax
addr_13:
	pop rax
	mov [cond_flag], al
	cmp rax, 1
	je addr_14
	jne endloop_addr_0
addr_14:
	mov rax, 2
	push rax
addr_15:
	mov rax, [a]
	push rax
addr_16:
	pop rax
	pop rbx
	xor rdx, rdx
	div rbx
	mov rax, rdx
        push rax
addr_17:
	mov rax, 0
	push rax
addr_18:
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
        push rax
addr_19:
	pop rax
	mov [cond_flag], al
	cmp rax, 1
	je addr_20
	jne endif_addr_0
addr_20:
	mov rax, [sum]
	push rax
addr_21:
	mov rax, [a]
	push rax
addr_22:
	pop rax
	pop rbx
	add rax, rbx
        push rax
addr_23:
	pop rax
	mov [sum], rax
endif_addr_0:
addr_24:
	mov rax, [a]
	push rax
addr_25:
	mov rax, [b]
	push rax
addr_26:
	pop rax
	pop rbx
	add rax, rbx
        push rax
addr_27:
	pop rax
	mov [next_fib], rax
addr_28:
	mov rax, [b]
	push rax
addr_29:
	pop rax
	mov [a], rax
addr_30:
	mov rax, [next_fib]
	push rax
addr_31:
	pop rax
	mov [b], rax
	jmp loopaddr_0
endloop_addr_0:
addr_32:
	mov rax, [sum]
	push rax
addr_33:
	pop rdi
	call dump
addr_34:
	mov rax, 0
	ret
block_addr_0:
addr_35:
	mov rdi, rax
	mov rax, 60
	syscall
segment readable writeable
a dq 0
b dq 0
sum dq 0
next_fib dq 0
call_flag db 0
cond_flag db 0
