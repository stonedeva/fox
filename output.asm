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
addr_0:
	mov rax, 0
	push rax
	pop [SYS_read]
addr_1:
	mov rax, 1
	push rax
	pop [SYS_write]
addr_2:
	mov rax, 2
	push rax
	pop [SYS_open]
addr_3:
	mov rax, 3
	push rax
	pop [SYS_close]
addr_4:
	mov rax, 60
	push rax
	pop [SYS_exit]
addr_5:
	mov rax, 0
	push rax
	pop [stdin]
addr_6:
	mov rax, 1
	push rax
	pop [stdout]
addr_7:
	mov rax, 2
	push rax
	pop [stderr]
print:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_0
addr_9:
	mov rax, 1
	push rax
addr_10:
	mov rax, 1
	push rax
addr_11:
	mov rax, [cstr]
	push rax
addr_12:
	mov rax, [len]
	push rax
addr_13:
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
addr_14:
	mov rax, 0
	push rax
addr_15:
	pop rax
	ret
block_addr_0:
main:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_1
addr_17:
	mov rax, 95
	push rax
addr_18:
	mov rax, [rsp]
	push rax
addr_19:
	pop rdi
	call dump
addr_20:
	pop rdi
	call dump
addr_21:
	mov rax, str0
	push rax
	mov rax, str0_len
	push rax
addr_22:
	mov byte [call_flag], 1
	pop [len]
	pop [cstr]
	call print
block_addr_1:
addr_23:
	mov rdi, rax
	mov rax, 60
	syscall
segment readable writeable
SYS_read dq 0
SYS_write dq 0
SYS_open dq 0
SYS_close dq 0
SYS_exit dq 0
stdin dq 0
stdout dq 0
stderr dq 0
len dq 0
cstr dq 0
call_flag db 0
cond_flag db 0
str0 db 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x0a, 0x00
str0_len = 15
