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
puts:
	mov rax, 1
	mov rdi, 1
	syscall
	ret
_start:
	mov byte [call_flag], 1
	call main
addr_0:
	pop rdi
	mov rax, 60
	syscall
main:
	cmp byte [call_flag], 1
	mov byte [call_flag], 0
	jne block_addr_0
addr_2:
	mov rax, str0
	push rax
	mov rax, str0_len
	push rax
addr_3:
	pop rdx
	pop rsi
	call puts
addr_4:
	mov rax, 0
	push rax
addr_5:
	pop rax
	jmp addr_0
block_addr_0:
segment readable writeable
call_flag db 0
str0 db 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x00, 0xA
str0_len = $ - str0
