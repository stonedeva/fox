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
	pop [var_argc]
	pop [var_argv]
	mov byte [call_flag], 1
	call main
main:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_0
addr_1:
	mov rax, 0
	push rax
	pop [var_count]
addr_2:
	mov rax, 0
	push rax
	pop [var_res1]
addr_3:
	mov rax, 0
	push rax
	pop [var_res2]
loopaddr_0:
addr_4:
	mov rax, [var_count]
	push rax
addr_5:
	mov rax, 100
	push rax
addr_6:
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
addr_7:
	pop rax
	mov [cond_flag], al
	cmp rax, 1
	je addr_8
	jne endloop_addr_0
addr_8:
	mov rax, [var_count]
	push rax
addr_9:
	mov rax, 1
	push rax
addr_10:
	pop rax
	pop rbx
	add rax, rbx
        push rax
addr_11:
	pop rax
	mov [var_count], rax
addr_12:
	mov rax, [var_res1]
	push rax
addr_13:
	mov rax, [var_count]
	push rax
addr_14:
	mov rax, [var_count]
	push rax
addr_15:
	pop rax
	pop rbx
	mul rax
        push rax
addr_16:
	pop rax
	pop rbx
	add rax, rbx
        push rax
addr_17:
	pop rax
	mov [var_res1], rax
	jmp loopaddr_0
endloop_addr_0:
loopaddr_1:
addr_18:
	mov rax, 0
	push rax
addr_19:
	mov rax, [var_count]
	push rax
addr_20:
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
addr_21:
	pop rax
	mov [cond_flag], al
	cmp rax, 1
	je addr_22
	jne endloop_addr_1
addr_22:
	mov rax, [var_res2]
	push rax
addr_23:
	mov rax, [var_count]
	push rax
addr_24:
	pop rax
	pop rbx
	add rax, rbx
        push rax
addr_25:
	pop rax
	mov [var_res2], rax
addr_26:
	mov rax, [var_count]
	push rax
addr_27:
	mov rax, 1
	push rax
addr_28:
	pop rax
	pop rbx
	sub rbx, rax
	mov rax, rbx
        push rax
addr_29:
	pop rax
	mov [var_count], rax
	jmp loopaddr_1
endloop_addr_1:
addr_30:
	mov rax, [var_res2]
	push rax
addr_31:
	mov rax, [var_res2]
	push rax
addr_32:
	pop rax
	pop rbx
	mul rax
        push rax
addr_33:
	pop rax
	mov [var_res2], rax
addr_34:
	mov rax, [var_res2]
	push rax
addr_35:
	mov rax, [var_res1]
	push rax
addr_36:
	pop rax
	pop rbx
	sub rbx, rax
	mov rax, rbx
        push rax
addr_37:
	pop rdi
	call print
addr_38:
	mov rax, 0
	ret
block_addr_0:
addr_39:
	mov rdi, rax
	mov rax, 60
	syscall
segment readable writeable
var_count dq 0
var_res1 dq 0
var_res2 dq 0
var_argc dq 0
var_argv dq 0
call_flag db 0
cond_flag db 0
