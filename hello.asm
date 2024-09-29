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
puts:
	mov rax, 1
	mov rdi, 1
	syscall
	ret

global _start
_start:
	mov byte [call_flag], 1
	call main
main:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_0
addr_1:
	mov rsi, str0
	mov rdx, str0_len
	call puts
	mov byte [call_flag], 1
	call sum
block_addr_0:
sum:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_1
addr_3:
	mov rsi, str1
	mov rdx, str1_len
	call puts
block_addr_1:
addr_4:
	mov rax, 60
	mov rdi, 0
	syscall
segment .text
segment .data
call_flag db 0
str0: db "Hello from the Earth!", 0xA
str0_len: equ $ - str0
str1: db "Sum them!", 0xA
str1_len: equ $ - str1
