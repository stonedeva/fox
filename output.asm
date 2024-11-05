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
	pop [var_argc]
	pop [var_argv]
	mov byte [call_flag], 1
	call main
print:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_0
addr_1:
	mov rax, 1
	push rax
addr_2:
	mov rax, 1
	push rax
addr_3:
	mov rax, [var_cstr]
	push rax
addr_4:
	mov rax, [var_len]
	push rax
addr_5:
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
addr_6:
	mov rax, 0
	ret
block_addr_0:
eprint:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_1
addr_8:
	mov rax, 1
	push rax
addr_9:
	mov rax, 2
	push rax
addr_10:
	mov rax, [var_ecstr]
	push rax
addr_11:
	mov rax, [var_elen]
	push rax
addr_12:
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
addr_13:
	mov rax, 0
	ret
block_addr_1:
main:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_2
addr_15:
	mov rax, str0_len
	push rax
	mov rax, str0
	push rax
	pop [var_msg]
addr_16:
	mov rax, [var_msg]
	push rax
addr_17:
	mov byte [call_flag], 1
	pop [var_cstr]
	pop [var_len]
	call print
addr_18:
	mov rax, 0
	push rax
addr_19:
	pop rax
	ret
addr_20:
	mov rax, 0
	ret
block_addr_2:
addr_21:
	mov rdi, rax
	mov rax, 60
	syscall
segment readable writeable
var_cstr dq 0
var_len dq 0
var_ecstr dq 0
var_elen dq 0
var_msg dq 0
var_argc dq 0
var_argv dq 0
call_flag db 0
cond_flag db 0
str0 db 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x00
str0_len = 13
