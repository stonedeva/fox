BITS 64
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

global _start
_start:
	call main
	mov rax, 60
	mov rdi, 0
	syscall
main:
addr_1:
	mov rax, 200
	push rax
addr_2:
	mov rax, 200
	push rax
addr_3:
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
        push rax
addr_4:
	; IF
	pop rax
	cmp rax, 1
	je addr_5
	jne block_addr_0
addr_5:
	mov rax, 300
	push rax
addr_6:
	pop rdi
	call dump
addr_7:
	mov rax, 25
	push rax
addr_8:
	mov rax, 200
	push rax
addr_9:
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
        push rax
addr_10:
	; IF
	pop rax
	cmp rax, 1
	je addr_11
	jne block_addr_0
addr_11:
	mov rax, 200
	push rax
addr_12:
	pop rdi
	call dump
block_addr_0:
block_addr_1:
addr_13:
	mov rax, 5000
	push rax
addr_14:
	pop rdi
	call dump
block_addr_2:
addr_15:
	mov rax, 60
	mov rdi, 0
	syscall
segment .text
