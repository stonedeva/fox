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
sum:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_0
addr_1:
	mov rax, [var_x]
	push rax
addr_2:
	mov rax, [var_y]
	push rax
addr_3:
	pop rax
	pop rbx
	add rax, rbx
        push rax
addr_4:
	pop rax
	ret
addr_5:
	mov rax, 0
	ret
block_addr_0:
main:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_1
addr_7:
	mov rax, 95
	push rax
addr_8:
	mov rax, 95
	push rax
addr_9:
	mov byte [call_flag], 1
	pop [var_x]
	pop [var_y]
	call sum
	push rax
addr_10:
	pop rdi
	call dump
addr_11:
	mov rax, 0
	push rax
addr_12:
	pop rax
	ret
addr_13:
	mov rax, 0
	ret
block_addr_1:
addr_14:
	mov rdi, rax
	mov rax, 60
	syscall
segment readable writeable
var_x dq 0
var_y dq 0
call_flag db 0
cond_flag db 0
