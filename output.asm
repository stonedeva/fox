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
	mov rax, 250
	push rax
addr_2:
	mov rax, 250
	push rax
addr_3:
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
        push rax
addr_4:
	pop rax
	mov [cond_flag], al
	cmp rax, 1
	je addr_5
	jne endif_addr_0
addr_5:
	mov rax, 250
	push rax
addr_6:
	pop rdi
	call dump
addr_7:
	mov rax, 25
	push rax
addr_8:
	mov rax, 205
	push rax
addr_9:
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
        push rax
addr_10:
	pop rax
	mov [cond_flag], al
	cmp rax, 1
	je addr_11
	jne endif_addr_0
addr_11:
	mov rax, 205
	push rax
addr_12:
	pop rdi
	call dump
endif_addr_0:
	cmp [cond_flag], 1
	je endif_addr_1
addr_13:
	mov rax, 99
	push rax
addr_14:
	pop rdi
	call dump
endif_addr_1:
endif_addr_2:
	cmp [cond_flag], 1
	je endif_addr_3
addr_15:
	mov rax, 95
	push rax
addr_16:
	pop rdi
	call dump
endif_addr_3:
addr_17:
	mov rax, 600
	push rax
addr_18:
	pop rdi
	call dump
addr_19:
	mov rax, 0
	push rax
addr_20:
	pop rax
	ret
addr_21:
	mov rax, 0
	ret
block_addr_0:
addr_22:
	mov rdi, rax
	mov rax, 60
	syscall
segment readable writeable
call_flag db 0
cond_flag db 0
