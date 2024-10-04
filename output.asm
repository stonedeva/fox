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
	mov rax, 0
	push rax
	pop [index]
loopaddr_0:
addr_3:
	mov rax, [index]
	push rax
addr_4:
	mov rax, 10
	push rax
addr_5:
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
addr_6:
	pop rax
	cmp rax, 1
	je addr_7
	jne endloop_addr_0
addr_7:
	mov rax, [index]
	push rax
addr_8:
	mov rax, 1
	push rax
addr_9:
	pop rax
	pop rbx
	add rax, rbx
        push rax
addr_10:
	pop rax
	mov [index], rax
addr_11:
	mov rax, 2
	push rax
addr_12:
	mov rax, [index]
	push rax
addr_13:
	pop rax
	pop rbx
	xor rdx, rdx
	div rbx
	mov rax, rdx
        push rax
addr_14:
	pop rax
	cmp rax, 1
	mov byte [cond_flag], al
	je addr_15
	jne endif_addr_0
addr_15:
	mov rax, str0
	push rax
	mov rax, str0_len
	push rax
addr_16:
	pop rdx
	pop rsi
	mov rax, 1
	mov rdi, 1
	syscall
addr_17:
	mov rax, [index]
	push rax
addr_18:
	pop rdi
	call dump
endif_addr_0:
	cmp [cond_flag], 1
	je endif_addr_1
addr_19:
	mov rax, str1
	push rax
	mov rax, str1_len
	push rax
addr_20:
	pop rdx
	pop rsi
	mov rax, 1
	mov rdi, 1
	syscall
addr_21:
	mov rax, [index]
	push rax
addr_22:
	pop rdi
	call dump
endif_addr_1:
	jmp loopaddr_0
endloop_addr_0:
addr_23:
	mov rax, 0
	push rax
addr_24:
	pop rax
	ret
block_addr_0:
addr_25:
	mov rdi, rax
	mov rax, 60
	syscall
segment readable writeable
index dq 0
call_flag db 0
cond_flag db 0
str0 db 0x59, 0x65, 0x73, 0x0a, 0x00
str0_len = 5
str1 db 0x4e, 0x6f, 0x0a, 0x00
str1_len = 4
