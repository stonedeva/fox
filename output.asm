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
	mov rax, str0
	push rax
	mov rax, str0_len
	push rax
addr_2:
	pop rdx
	pop rsi
	mov rax, 1
	mov rdi, 1
	syscall
addr_3:
	mov byte [call_flag], 1
	call make
addr_4:
	mov rax, 0
	push rax
addr_5:
	pop rax
	ret
block_addr_0:
make:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_1
addr_7:
	mov rax, str1
	push rax
	mov rax, str1_len
	push rax
addr_8:
	pop rdx
	pop rsi
	mov rax, 1
	mov rdi, 1
	syscall
addr_9:
	mov rax, 200
	push rax
addr_10:
	mov rax, 200
	push rax
addr_11:
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
        push rax
addr_12:
	pop rax
	cmp rax, 1
	je addr_13
	jne endif_addr_0
addr_13:
	mov rax, str2
	push rax
	mov rax, str2_len
	push rax
addr_14:
	pop rdx
	pop rsi
	mov rax, 1
	mov rdi, 1
	syscall
addr_15:
	mov rax, 300
	push rax
addr_16:
	mov rax, 350
	push rax
addr_17:
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
        push rax
addr_18:
	pop rax
	cmp rax, 1
	je addr_19
	jne endif_addr_0
addr_19:
	mov rax, str3
	push rax
	mov rax, str3_len
	push rax
addr_20:
	pop rdx
	pop rsi
	mov rax, 1
	mov rdi, 1
	syscall
endif_addr_0:
endif_addr_1:
addr_21:
	mov rax, str4
	push rax
	mov rax, str4_len
	push rax
addr_22:
	pop rdx
	pop rsi
	mov rax, 1
	mov rdi, 1
	syscall
addr_23:
	mov rax, 0
	push rax
addr_24:
	pop rax
	ret
block_addr_1:
addr_25:
	mov rdi, rax
	mov rax, 60
	syscall
segment readable writeable
call_flag db 0
str0 db 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x00, 0xA
str0_len = $ - str0
str1 db 0x31, 0x00, 0xA
str1_len = $ - str1
str2 db 0x32, 0x00, 0xA
str2_len = $ - str2
str3 db 0x33, 0x00, 0xA
str3_len = $ - str3
str4 db 0x34, 0x00, 0xA
str4_len = $ - str4
