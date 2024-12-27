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
	pop [argc]
	mov [argv_ptr], rsp
	call addr_364
	mov rdi, rax
	mov rax, 60
	syscall
addr_60:
	pop rbp
	mov rax, addr_44
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	mov rax, [argv_ptr]
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	mov rax, 0
	push rbp
	ret
addr_69:
	pop rbp
	mov r15, rsp
	push QWORD [r15 + 24]
	push QWORD [r15 + 8]
	pop rax
	pop rbx
	cmp rax, rbx
	setne al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_90
	add rsp, 32
	mov rax, 0
	push rax
	push rbp
	ret
addr_90:
	mov rax, 0
	push rax
addr_92:
	push QWORD [rsp]
	push QWORD [r15 + 24]
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	pop rax
	cmp rax, 1
	jne addr_114
	push QWORD [rsp]
	push QWORD [r15 + 16]
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov bl, [rax]
	push rbx
	push QWORD [rsp+8]
	push QWORD [r15 + 0]
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov bl, [rax]
	push rbx
	pop rax
	pop rbx
	cmp rax, rbx
	setne al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_111
	add rsp, 40
	mov rax, 0
	push rax
	push rbp
	ret
addr_111:
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_92
addr_114:
	add rsp, 8
	add rsp, 32
	mov rax, 1
	push rax
	push rbp
	ret
	mov rax, 0
	push rbp
	ret
addr_120:
	pop rbp
	mov r15, rsp
	mov rax, 0
	push rax
addr_128:
	push QWORD [rsp]
	push QWORD [r15 + 0]
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov bl, [rax]
	push rbx
	mov rax, 0
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	setne al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_138
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_128
addr_138:
	pop rax
	pop rbx
	push rax
	push rbx
	add rsp, 8
	mov rax, 0
	push rbp
	ret
addr_143:
	pop rbp
	push QWORD [rsp]
	call addr_120
	pop rax
	pop rbx
	push rax
	push rbx
	mov rax, 0
	push rbp
	ret
addr_151:
	pop rbp
	mov r15, rsp
	mov rax, 0
	push rax
addr_163:
	push QWORD [rsp]
	push QWORD [r15 + 0]
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	pop rax
	cmp rax, 1
	jne addr_178
	push QWORD [rsp]
	push QWORD [r15 + 8]
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov bl, [rax]
	push rbx
	push QWORD [r15 + 16]
	push QWORD [rsp+8]
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rbx
	pop rax
	mov [rax], bl
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_163
addr_178:
	add rsp, 8
	add rsp, 24
	mov rax, 0
	push rbp
	ret
addr_182:
	pop rbp
	mov r15, rsp
	mov rax, addr_4
	push rax
	mov rax, addr_28
	push rax
	push QWORD [r15 + 0]
	push QWORD [r15 + 8]
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 16
	mov rax, 0
	push rbp
	ret
addr_199:
	pop rbp
	mov r15, rsp
	mov rax, addr_4
	push rax
	mov rax, addr_28
	push rax
	push QWORD [r15 + 0]
	push QWORD [r15 + 0]
	call addr_120
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 8
	mov rax, 0
	push rbp
	ret
addr_215:
	pop rbp
	mov r15, rsp
	mov rax, addr_8
	push rax
	push QWORD [r15 + 16]
	push QWORD [r15 + 8]
	push QWORD [r15 + 0]
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	mov rax, [rsp]
	add rsp, 16
	push rax
	mov rax, [rsp]
	add rsp, 16
	push rax
	mov rax, [rsp]
	add rsp, 16
	push rax
	mov rax, [rsp]
	add rsp, 16
	push rax
	mov rax, 0
	push rbp
	ret
addr_237:
	pop rbp
	mov r15, rsp
	mov rax, addr_12
	push rax
	push QWORD [r15 + 0]
	mov rax, 0
	push rax
	mov rax, 0
	push rax
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 8
	mov rax, 0
	push rbp
	ret
addr_252:
	pop rbp
	mov r15, rsp
	mov rax, addr_4
	push rax
	push QWORD [r15 + 0]
	push QWORD [r15 + 8]
	push QWORD [r15 + 16]
	mov rax, 1
	push rax
	pop rax
	pop rbx
	sub rbx, rax
	mov rax, rbx
        push rax
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 24
	mov rax, 0
	push rbp
	ret
addr_273:
	pop rbp
	mov r15, rsp
	mov rax, addr_4
	push rax
	mov rax, addr_32
	push rax
	push QWORD [r15 + 0]
	push QWORD [r15 + 8]
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 16
	mov rax, 0
	push rbp
	ret
addr_290:
	pop rbp
	mov r15, rsp
	mov rax, addr_0
	push rax
	mov rax, addr_24
	push rax
	push QWORD [r15 + 8]
	push QWORD [r15 + 0]
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 16
	mov rax, 0
	push rbp
	ret
addr_307:
	pop rbp
	mov r15, rsp
	mov rax, addr_0
	push rax
	push QWORD [r15 + 16]
	push QWORD [r15 + 8]
	push QWORD [r15 + 0]
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 24
	mov rax, 0
	push rbp
	ret
addr_326:
	pop rbp
	mov r15, rsp
	mov rax, addr_20
	push rax
	push QWORD [r15 + 0]
	mov rax, 0
	push rax
	mov rax, 0
	push rax
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 8
	mov rax, 0
	push rbp
	ret
addr_341:
	pop rbp
	mov r15, rsp
	mov rax, addr_16
	push rax
	push QWORD [r15 + 16]
	push QWORD [r15 + 8]
	push QWORD [r15 + 0]
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 24
	mov rax, 0
	push rbp
	ret
addr_364:
	mov rax, 2
	push rax
	mov rax, str0
	push rax
	mov rax, addr_52
	push rax
	mov rax, 0
	push rax
	call addr_215
	mov r15, rsp
	push QWORD [r15 + 0]
	mov rax, 0
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	pop rax
	cmp rax, 1
	jne addr_384
	mov rax, str1_len
	push rax
	mov rax, str1
	push rax
	call addr_273
	mov rax, 1
	push rax
	call addr_326
addr_384:
	push QWORD [r15 + 0]
	mov rax, addr_360
	push rax
	mov rax, 1024
	push rax
	call addr_307
	push QWORD [r15 + 0]
	call addr_237
	add rsp, 8
	mov rax, 1024
	push rax
	mov rax, addr_360
	push rax
	call addr_182
	mov rax, 0
	ret
segment readable writeable
addr_0 = 0
addr_4 = 1
addr_8 = 2
addr_12 = 3
addr_16 = 59
addr_20 = 60
addr_24 = 0
addr_28 = 1
addr_32 = 2
addr_36 = 4
addr_40 = 8
addr_44 = 8
addr_48 = 577
addr_52 = 0
addr_56 = 438
addr_360 rb 1024
argc rq 1
argv_ptr rq 1
str0 db 0x2e, 0x2f, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x73, 0x2f, 0x63, 0x61, 0x74, 0x2e, 0x66, 0x6f, 0x78, 0x00
str0_len = 18
str1 db 0x45, 0x52, 0x52, 0x4f, 0x52, 0x3a, 0x20, 0x43, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6e, 0x6f, 0x74, 0x20, 0x6f, 0x70, 0x65, 0x6e, 0x20, 0x66, 0x69, 0x6c, 0x65, 0x21, 0x0a, 0x00
str1_len = 29
