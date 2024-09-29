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
	mov rsi, str4
	mov rdx, str4_len
	call puts
block_addr_0:
sum:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_1
addr_3:
	mov rsi, str5
	mov rdx, str5_len
	call puts
block_addr_1:
addr_4:
	mov rax, 60
	mov rdi, 0
	syscall
segment .text
segment .data
call_flag db 0
str0: db This, 0xA
str0_len: equ $ - str0
str1: db is, 0xA
str1_len: equ $ - str1
str2: db a, 0xA
str2_len: equ $ - str2
str3: db comment, 0xA
str3_len: equ $ - str3
str4: db "Hello from the Earth!", 0xA
str4_len: equ $ - str4
str5: db "Sum them!", 0xA
str5_len: equ $ - str5
