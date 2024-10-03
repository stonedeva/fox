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
loopaddr_0:
addr_2:
	mov rax, [count]
	push rax
addr_3:
	mov rax, 500
	push rax
addr_4:
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
addr_5:
	pop rax
	cmp rax, 1
	je addr_6
	jne endloop_addr_0
addr_6:
	mov rax, [count]
	push rax
addr_7:
	mov rax, 1
	push rax
addr_8:
	pop rax
	pop rbx
	add rax, rbx
        push rax
addr_9:
	pop rax
	mov [count], rax
addr_10:
	mov rax, [count]
	push rax
addr_11:
	pop rdi
	call dump
	jmp loopaddr_0
endloop_addr_0:
addr_12:
	mov rax, 0
	push rax
addr_13:
	pop rax
	ret
block_addr_0:
addr_14:
	mov rdi, rax
	mov rax, 60
	syscall
segment readable writeable
count dq 0
call_flag db 0
