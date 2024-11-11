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
puts:
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
eputs:
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
usage:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_2
addr_15:
	mov rax, str0_len
	push rax
	mov rax, str0
	push rax
addr_16:
	mov byte [call_flag], 1
	pop [var_cstr]
	pop [var_len]
	call puts
addr_17:
	mov rax, str1_len
	push rax
	mov rax, str1
	push rax
addr_18:
	mov byte [call_flag], 1
	pop [var_cstr]
	pop [var_len]
	call puts
addr_19:
	mov rax, str2_len
	push rax
	mov rax, str2
	push rax
addr_20:
	mov byte [call_flag], 1
	pop [var_cstr]
	pop [var_len]
	call puts
addr_21:
	mov rax, str3_len
	push rax
	mov rax, str3
	push rax
addr_22:
	mov byte [call_flag], 1
	pop [var_cstr]
	pop [var_len]
	call puts
addr_23:
	mov rax, str4_len
	push rax
	mov rax, str4
	push rax
addr_24:
	mov byte [call_flag], 1
	pop [var_cstr]
	pop [var_len]
	call puts
addr_25:
	mov rax, str5_len
	push rax
	mov rax, str5
	push rax
addr_26:
	mov byte [call_flag], 1
	pop [var_cstr]
	pop [var_len]
	call puts
addr_27:
	mov rax, 0
	ret
block_addr_2:
main:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_3
addr_29:
	mov rax, [var_argc]
	push rax
addr_30:
	mov rax, 2
	push rax
addr_31:
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
addr_32:
	pop rax
	mov [cond_flag], al
	cmp rax, 1
	je addr_33
	jne endif_addr_0
addr_33:
	mov rax, str6_len
	push rax
	mov rax, str6
	push rax
addr_34:
	mov byte [call_flag], 1
	pop [var_ecstr]
	pop [var_elen]
	call eputs
addr_35:
	mov rax, str7_len
	push rax
	mov rax, str7
	push rax
addr_36:
	mov byte [call_flag], 1
	pop [var_ecstr]
	pop [var_elen]
	call eputs
addr_37:
	mov rax, 1
	push rax
addr_38:
	pop rax
	ret
endif_addr_0:
addr_39:
	mov rax, 0
	push rax
addr_40:
	pop rax
	ret
addr_41:
	mov rax, 0
	ret
block_addr_3:
addr_42:
	mov rdi, rax
	mov rax, 60
	syscall
segment readable writeable
var_cstr dq 0
var_len dq 0
var_ecstr dq 0
var_elen dq 0
var_argc dq 0
var_argv dq 0
call_flag db 0
cond_flag db 0
str0 db 0x4f, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x3a, 0x0a, 0x00
str0_len = 10
str1 db 0x09, 0x2d, 0x76, 0x09, 0x53, 0x68, 0x6f, 0x77, 0x20, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6e, 0x74, 0x20, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x0a, 0x00
str1_len = 26
str2 db 0x09, 0x2d, 0x6f, 0x09, 0x53, 0x65, 0x74, 0x20, 0x6f, 0x75, 0x74, 0x70, 0x75, 0x74, 0x20, 0x70, 0x61, 0x74, 0x68, 0x0a, 0x00
str2_len = 21
str3 db 0x09, 0x2d, 0x6c, 0x09, 0x44, 0x75, 0x6d, 0x70, 0x20, 0x6c, 0x65, 0x78, 0x69, 0x63, 0x61, 0x6c, 0x20, 0x61, 0x6e, 0x61, 0x6c, 0x79, 0x73, 0x69, 0x73, 0x0a, 0x00
str3_len = 27
str4 db 0x09, 0x2d, 0x74, 0x09, 0x44, 0x75, 0x6d, 0x70, 0x20, 0x74, 0x79, 0x70, 0x65, 0x20, 0x73, 0x74, 0x61, 0x63, 0x6b, 0x0a, 0x00
str4_len = 21
str5 db 0x09, 0x2d, 0x68, 0x09, 0x53, 0x68, 0x6f, 0x77, 0x20, 0x68, 0x65, 0x6c, 0x70, 0x20, 0x6d, 0x61, 0x70, 0x0a, 0x00
str5_len = 19
str6 db 0x55, 0x73, 0x61, 0x67, 0x65, 0x3a, 0x20, 0x2e, 0x2f, 0x66, 0x6f, 0x78, 0x63, 0x20, 0x5b, 0x6f, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x2e, 0x2e, 0x2e, 0x5d, 0x20, 0x3c, 0x66, 0x69, 0x6c, 0x65, 0x3e, 0x0a, 0x00
str6_len = 35
str7 db 0x4e, 0x6f, 0x20, 0x69, 0x6e, 0x70, 0x75, 0x74, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x20, 0x70, 0x72, 0x6f, 0x76, 0x69, 0x64, 0x65, 0x64, 0x21, 0x0a, 0x00
str7_len = 25
