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
	mov rax, ret_stack_end
	mov [ret_stack_rsp], rax
	call addr_993
	mov rax, 60
	mov rdi, 0
	syscall
addr_68:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_77:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	jne addr_98
	add rsp, 32
	mov rax, 0
	push rax
	push rbp
	ret
addr_98:
	mov rax, 0
	push rax
addr_100:
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
	jne addr_122
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
	jne addr_119
	add rsp, 40
	mov rax, 0
	push rax
	push rbp
	ret
addr_119:
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_100
addr_122:
	add rsp, 8
	add rsp, 32
	mov rax, 1
	push rax
	push rbp
	ret
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_128:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov r15, rsp
	mov rax, 0
	push rax
addr_136:
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
	jne addr_146
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_136
addr_146:
	pop rax
	pop rbx
	push rax
	push rbx
	add rsp, 8
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_151:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	push QWORD [rsp]
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_128
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	pop rax
	pop rbx
	push rax
	push rbx
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_159:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov r15, rsp
	mov rax, 0
	push rax
addr_171:
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
	jne addr_186
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
	jmp addr_171
addr_186:
	add rsp, 8
	add rsp, 24
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_190:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_207:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	pop rax
	pop rbx
	push rax
	push rbx
	mov rax, 0
	push rax
addr_214:
	push QWORD [rsp+8]
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
	jne addr_243
	mov r15, rsp
	mov rax, addr_52
	push rax
	mov rax, addr_48
	push rax
	push QWORD [r15 + 0]
	pop rax
	pop rbx
	sub rbx, rax
	mov rax, rbx
        push rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	sub rbx, rax
	mov rax, rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	push QWORD [r15 + 8]
	mov rax, 10
	push rax
	pop rax
	pop rbx
	xchg rax, rbx
	xor rdx, rdx
	div rbx
	mov rax, rdx
        push rax
	mov rax, 48
	push rax
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
	pop rax
	pop rbx
	push rax
	push rbx
	mov rax, 10
	push rax
	pop rax
	pop rbx
	xchg rax, rbx
	xor rdx, rdx
	div rbx
        push rax
	pop rax
	pop rbx
	push rax
	push rbx
	jmp addr_214
addr_243:
	pop rax
	pop rbx
	push rax
	push rbx
	add rsp, 8
	mov r15, rsp
	mov rax, addr_4
	push rax
	push QWORD [r15 + 0]
	mov rax, addr_52
	push rax
	mov rax, addr_48
	push rax
	push QWORD [r15 + 8]
	pop rax
	pop rbx
	sub rbx, rax
	mov rax, rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	push QWORD [r15 + 8]
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 16
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_262:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 0
	push rax
addr_267:
	push QWORD [rsp+8]
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
	jne addr_296
	mov r15, rsp
	mov rax, addr_52
	push rax
	mov rax, addr_48
	push rax
	push QWORD [r15 + 0]
	pop rax
	pop rbx
	sub rbx, rax
	mov rax, rbx
        push rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	sub rbx, rax
	mov rax, rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	push QWORD [r15 + 8]
	mov rax, 10
	push rax
	pop rax
	pop rbx
	xchg rax, rbx
	xor rdx, rdx
	div rbx
	mov rax, rdx
        push rax
	mov rax, 48
	push rax
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
	pop rax
	pop rbx
	push rax
	push rbx
	mov rax, 10
	push rax
	pop rax
	pop rbx
	xchg rax, rbx
	xor rdx, rdx
	div rbx
        push rax
	pop rax
	pop rbx
	push rax
	push rbx
	jmp addr_267
addr_296:
	add rsp, 16
	mov rax, addr_4
	push rax
	mov rax, addr_28
	push rax
	mov rax, addr_52
	push rax
	mov rax, addr_48
	push rax
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_305:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov r15, rsp
	mov rax, addr_4
	push rax
	mov rax, addr_28
	push rax
	push QWORD [r15 + 0]
	push QWORD [r15 + 0]
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_128
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	pop rdx
	pop rsi
	pop rdi
	pop rax
	syscall
	push rax
	add rsp, 8
	add rsp, 8
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_321:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_342:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_357:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_378:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_395:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_412:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_431:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_446:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
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
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
	mov rax, 0
	push rax
	pop [addr_531]
addr_535:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str0_len
	push rax
	mov rax, str0
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str1_len
	push rax
	mov rax, str1
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str2_len
	push rax
	mov rax, str2
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str3_len
	push rax
	mov rax, str3
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str4_len
	push rax
	mov rax, str4
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str5_len
	push rax
	mov rax, str5
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_551:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, addr_513
	push rax
	mov rax, [addr_531]
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_565
	mov rax, str6_len
	push rax
	mov rax, str6
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_378
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_431
	mov [ret_stack_rsp], rsp
	mov rsp, rax
addr_565:
	mov r15, rsp
	mov rax, addr_525
	push rax
	mov rax, [addr_531]
	push rax
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	push QWORD [r15 + 8]
	pop rbx
	pop rax
	mov [rax], rbx
	mov rax, addr_525
	push rax
	mov rax, [addr_531]
	push rax
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	mov rax, addr_517
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	push QWORD [r15 + 0]
	pop rbx
	pop rax
	mov [rax], rbx
	add rsp, 16
	mov rax, [addr_531]
	push rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	mov [addr_531], rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_592:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 0
	push rax
addr_596:
	push QWORD [rsp]
	mov rax, [addr_531]
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	pop rax
	cmp rax, 1
	jne addr_625
	mov rax, str7_len
	push rax
	mov rax, str7
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str8_len
	push rax
	mov rax, str8
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	pop rdi
	call print
	mov rax, str9_len
	push rax
	mov rax, str9
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	mov rax, addr_517
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	pop rdi
	call print
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_596
addr_625:
	add rsp, 8
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_628:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str10_len
	push rax
	mov rax, str10
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str11_len
	push rax
	mov rax, str11
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str12_len
	push rax
	mov rax, str12
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str13_len
	push rax
	mov rax, str13
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str14_len
	push rax
	mov rax, str14
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str15_len
	push rax
	mov rax, str15
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str16_len
	push rax
	mov rax, str16
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str17_len
	push rax
	mov rax, str17
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str18_len
	push rax
	mov rax, str18
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str19_len
	push rax
	mov rax, str19
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str20_len
	push rax
	mov rax, str20
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str21_len
	push rax
	mov rax, str21
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str22_len
	push rax
	mov rax, str22
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str23_len
	push rax
	mov rax, str23
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str24_len
	push rax
	mov rax, str24
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str25_len
	push rax
	mov rax, str25
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str26_len
	push rax
	mov rax, str26
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str27_len
	push rax
	mov rax, str27
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str28_len
	push rax
	mov rax, str28
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str29_len
	push rax
	mov rax, str29
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str30_len
	push rax
	mov rax, str30
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str31_len
	push rax
	mov rax, str31
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str32_len
	push rax
	mov rax, str32
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str33_len
	push rax
	mov rax, str33
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str34_len
	push rax
	mov rax, str34
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str35_len
	push rax
	mov rax, str35
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str36_len
	push rax
	mov rax, str36
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str37_len
	push rax
	mov rax, str37
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str38_len
	push rax
	mov rax, str38
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str39_len
	push rax
	mov rax, str39
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str40_len
	push rax
	mov rax, str40
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str41_len
	push rax
	mov rax, str41
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 0
	push rax
addr_696:
	push QWORD [rsp]
	mov rax, [addr_531]
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	setg al
	movzx rax, al
        push rax
	pop rax
	cmp rax, 1
	jne addr_982
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_465
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_731
	mov rax, str42_len
	push rax
	mov rax, str42
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str43_len
	push rax
	mov rax, str43
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	mov rax, addr_517
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_262
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str44_len
	push rax
	mov rax, str44
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str45_len
	push rax
	mov rax, str45
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_731:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_469
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_755
	mov rax, str46_len
	push rax
	mov rax, str46
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str47_len
	push rax
	mov rax, str47
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str48_len
	push rax
	mov rax, str48
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str49_len
	push rax
	mov rax, str49
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str50_len
	push rax
	mov rax, str50
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_755:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_473
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_779
	mov rax, str51_len
	push rax
	mov rax, str51
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str52_len
	push rax
	mov rax, str52
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str53_len
	push rax
	mov rax, str53
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str54_len
	push rax
	mov rax, str54
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str55_len
	push rax
	mov rax, str55
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_779:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_477
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_803
	mov rax, str56_len
	push rax
	mov rax, str56
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str57_len
	push rax
	mov rax, str57
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str58_len
	push rax
	mov rax, str58
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str59_len
	push rax
	mov rax, str59
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str60_len
	push rax
	mov rax, str60
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_803:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_481
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_829
	mov rax, str61_len
	push rax
	mov rax, str61
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str62_len
	push rax
	mov rax, str62
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str63_len
	push rax
	mov rax, str63
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str64_len
	push rax
	mov rax, str64
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str65_len
	push rax
	mov rax, str65
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str66_len
	push rax
	mov rax, str66
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_829:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_485
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_849
	mov rax, str67_len
	push rax
	mov rax, str67
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str68_len
	push rax
	mov rax, str68
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str69_len
	push rax
	mov rax, str69
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_849:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_489
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_867
	mov rax, str70_len
	push rax
	mov rax, str70
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str71_len
	push rax
	mov rax, str71
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_867:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_493
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_885
	mov rax, str72_len
	push rax
	mov rax, str72
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str73_len
	push rax
	mov rax, str73
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_885:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_497
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_909
	mov rax, str74_len
	push rax
	mov rax, str74
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str75_len
	push rax
	mov rax, str75
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str76_len
	push rax
	mov rax, str76
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str77_len
	push rax
	mov rax, str77
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str78_len
	push rax
	mov rax, str78
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_909:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_501
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_927
	mov rax, str79_len
	push rax
	mov rax, str79
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str80_len
	push rax
	mov rax, str80
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_927:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_505
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_957
	mov rax, str81_len
	push rax
	mov rax, str81
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str82_len
	push rax
	mov rax, str82
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str83_len
	push rax
	mov rax, str83
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str84_len
	push rax
	mov rax, str84
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str85_len
	push rax
	mov rax, str85
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str86_len
	push rax
	mov rax, str86
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str87_len
	push rax
	mov rax, str87
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str88_len
	push rax
	mov rax, str88
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_957:
	mov rax, addr_525
	push rax
	push QWORD [rsp+8]
	mov rax, addr_521
	push rax
	pop rax
	pop rbx
	mul rbx
        push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	pop rax
	xor rbx, rbx
	mov rbx, [rax]
	push rbx
	mov rax, addr_509
	push rax
	pop rax
	pop rbx
	cmp rax, rbx
	sete al
	movzx rax, al
	push rax
	pop rax
	cmp rax, 1
	jne addr_979
	mov rax, str89_len
	push rax
	mov rax, str89
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str90_len
	push rax
	mov rax, str90
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str91_len
	push rax
	mov rax, str91
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str92_len
	push rax
	mov rax, str92
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_979:
	mov rax, 1
	push rax
	pop rax
	pop rbx
	add rax, rbx
        push rax
	jmp addr_696
addr_982:
	add rsp, 8
	mov rax, str93_len
	push rax
	mov rax, str93
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str94_len
	push rax
	mov rax, str94
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str95_len
	push rax
	mov rax, str95
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, str96_len
	push rax
	mov rax, str96
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_190
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
addr_993:
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, addr_465
	push rax
	mov rax, 95
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_551
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, addr_465
	push rax
	mov rax, 10
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_551
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, addr_489
	push rax
	mov rax, 0
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_551
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, addr_469
	push rax
	mov rax, 0
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_551
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, addr_469
	push rax
	mov rax, 0
	push rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_551
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	call addr_628
	mov [ret_stack_rsp], rsp
	mov rsp, rax
	mov rax, rsp
	mov rsp, [ret_stack_rsp]
	ret
segment readable writeable
ret_stack_rsp rq 1
ret_stack rb 65534
ret_stack_end:
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
addr_48 = 32
addr_52 rb 32
addr_56 = 577
addr_60 = 0
addr_64 = 438
addr_465 = 0
addr_469 = 1
addr_473 = 2
addr_477 = 3
addr_481 = 4
addr_485 = 5
addr_489 = 6
addr_493 = 7
addr_497 = 8
addr_501 = 9
addr_505 = 10
addr_509 = 11
addr_513 = 500
addr_517 = 8
addr_521 = 16
addr_525 rb 8000
addr_531 dq 0
argc rq 1
argv_ptr rq 1
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
str6 db 0x45, 0x52, 0x52, 0x4f, 0x52, 0x3a, 0x20, 0x4f, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x6c, 0x69, 0x6d, 0x69, 0x74, 0x20, 0x68, 0x61, 0x73, 0x20, 0x62, 0x65, 0x65, 0x6e, 0x20, 0x72, 0x65, 0x61, 0x63, 0x68, 0x65, 0x64, 0x21, 0x0a, 0x00
str6_len = 42
str7 db 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x0a, 0x00
str7_len = 14
str8 db 0x54, 0x79, 0x70, 0x65, 0x3a, 0x20, 0x00
str8_len = 6
str9 db 0x4f, 0x70, 0x65, 0x72, 0x61, 0x6e, 0x64, 0x3a, 0x20, 0x00
str9_len = 9
str10 db 0x66, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x20, 0x45, 0x4c, 0x46, 0x36, 0x34, 0x20, 0x65, 0x78, 0x65, 0x63, 0x75, 0x74, 0x61, 0x62, 0x6c, 0x65, 0x20, 0x30, 0x0a, 0x00
str10_len = 27
str11 db 0x65, 0x6e, 0x74, 0x72, 0x79, 0x20, 0x5f, 0x73, 0x74, 0x61, 0x72, 0x74, 0x0a, 0x00
str11_len = 14
str12 db 0x73, 0x65, 0x67, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x72, 0x65, 0x61, 0x64, 0x61, 0x62, 0x6c, 0x65, 0x20, 0x65, 0x78, 0x65, 0x63, 0x75, 0x74, 0x61, 0x62, 0x6c, 0x65, 0x0a, 0x00
str12_len = 29
str13 db 0x70, 0x72, 0x69, 0x6e, 0x74, 0x3a, 0x0a, 0x00
str13_len = 8
str14 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x38, 0x2c, 0x20, 0x2d, 0x33, 0x36, 0x38, 0x39, 0x33, 0x34, 0x38, 0x38, 0x31, 0x34, 0x37, 0x34, 0x31, 0x39, 0x31, 0x30, 0x33, 0x32, 0x33, 0x0a, 0x00
str14_len = 34
str15 db 0x20, 0x20, 0x20, 0x20, 0x73, 0x75, 0x62, 0x20, 0x72, 0x73, 0x70, 0x2c, 0x20, 0x34, 0x30, 0x0a, 0x00
str15_len = 17
str16 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x42, 0x59, 0x54, 0x45, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x2b, 0x33, 0x31, 0x5d, 0x2c, 0x20, 0x31, 0x30, 0x0a, 0x00
str16_len = 27
str17 db 0x20, 0x20, 0x20, 0x20, 0x6c, 0x65, 0x61, 0x20, 0x72, 0x63, 0x78, 0x2c, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x2b, 0x33, 0x30, 0x5d, 0x0a, 0x00
str17_len = 23
str18 db 0x2e, 0x4c, 0x32, 0x3a, 0x0a, 0x00
str18_len = 6
str19 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x72, 0x64, 0x69, 0x0a, 0x00
str19_len = 18
str20 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x75, 0x6c, 0x20, 0x72, 0x38, 0x0a, 0x00
str20_len = 12
str21 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x72, 0x64, 0x69, 0x0a, 0x00
str21_len = 18
str22 db 0x20, 0x20, 0x20, 0x20, 0x73, 0x68, 0x72, 0x20, 0x72, 0x64, 0x78, 0x2c, 0x20, 0x33, 0x0a, 0x00
str22_len = 16
str23 db 0x20, 0x20, 0x20, 0x20, 0x6c, 0x65, 0x61, 0x20, 0x72, 0x73, 0x69, 0x2c, 0x20, 0x5b, 0x72, 0x64, 0x78, 0x2b, 0x72, 0x64, 0x78, 0x2a, 0x34, 0x5d, 0x0a, 0x00
str23_len = 26
str24 db 0x20, 0x20, 0x20, 0x20, 0x61, 0x64, 0x64, 0x20, 0x72, 0x73, 0x69, 0x2c, 0x20, 0x72, 0x73, 0x69, 0x0a, 0x00
str24_len = 18
str25 db 0x20, 0x20, 0x20, 0x20, 0x73, 0x75, 0x62, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x72, 0x73, 0x69, 0x0a, 0x00
str25_len = 18
str26 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x73, 0x69, 0x2c, 0x20, 0x72, 0x63, 0x78, 0x0a, 0x00
str26_len = 18
str27 db 0x20, 0x20, 0x20, 0x20, 0x73, 0x75, 0x62, 0x20, 0x72, 0x63, 0x78, 0x2c, 0x20, 0x31, 0x0a, 0x00
str27_len = 16
str28 db 0x20, 0x20, 0x20, 0x20, 0x61, 0x64, 0x64, 0x20, 0x65, 0x61, 0x78, 0x2c, 0x20, 0x34, 0x38, 0x0a, 0x00
str28_len = 17
str29 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x42, 0x59, 0x54, 0x45, 0x20, 0x5b, 0x72, 0x63, 0x78, 0x2b, 0x31, 0x5d, 0x2c, 0x20, 0x61, 0x6c, 0x0a, 0x00
str29_len = 26
str30 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x72, 0x64, 0x69, 0x0a, 0x00
str30_len = 18
str31 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x64, 0x69, 0x2c, 0x20, 0x72, 0x64, 0x78, 0x0a, 0x00
str31_len = 18
str32 db 0x20, 0x20, 0x20, 0x20, 0x63, 0x6d, 0x70, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x39, 0x0a, 0x00
str32_len = 16
str33 db 0x20, 0x20, 0x20, 0x20, 0x6a, 0x61, 0x20, 0x2e, 0x4c, 0x32, 0x0a, 0x00
str33_len = 12
str34 db 0x20, 0x20, 0x20, 0x20, 0x6c, 0x65, 0x61, 0x20, 0x72, 0x64, 0x78, 0x2c, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x2b, 0x33, 0x32, 0x5d, 0x0a, 0x00
str34_len = 23
str35 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x65, 0x64, 0x69, 0x2c, 0x20, 0x31, 0x0a, 0x00
str35_len = 16
str36 db 0x20, 0x20, 0x20, 0x20, 0x73, 0x75, 0x62, 0x20, 0x72, 0x64, 0x78, 0x2c, 0x20, 0x72, 0x73, 0x69, 0x0a, 0x00
str36_len = 18
str37 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x31, 0x0a, 0x00
str37_len = 16
str38 db 0x20, 0x20, 0x20, 0x20, 0x73, 0x79, 0x73, 0x63, 0x61, 0x6c, 0x6c, 0x0a, 0x00
str38_len = 13
str39 db 0x20, 0x20, 0x20, 0x20, 0x61, 0x64, 0x64, 0x20, 0x72, 0x73, 0x70, 0x2c, 0x20, 0x34, 0x30, 0x0a, 0x00
str39_len = 17
str40 db 0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x74, 0x0a, 0x00
str40_len = 9
str41 db 0x5f, 0x73, 0x74, 0x61, 0x72, 0x74, 0x3a, 0x0a, 0x00
str41_len = 9
str42 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x69, 0x6e, 0x74, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str42_len = 25
str43 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x00
str43_len = 13
str44 db 0x0a, 0x00
str44_len = 2
str45 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str45_len = 14
str46 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x70, 0x6c, 0x75, 0x73, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str46_len = 21
str47 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str47_len = 13
str48 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str48_len = 13
str49 db 0x20, 0x20, 0x20, 0x20, 0x61, 0x64, 0x64, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str49_len = 18
str50 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str50_len = 14
str51 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x6d, 0x69, 0x6e, 0x75, 0x73, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str51_len = 22
str52 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str52_len = 13
str53 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str53_len = 13
str54 db 0x20, 0x20, 0x20, 0x20, 0x73, 0x75, 0x62, 0x20, 0x72, 0x62, 0x78, 0x2c, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str54_len = 18
str55 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str55_len = 14
str56 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x6d, 0x75, 0x6c, 0x74, 0x69, 0x70, 0x6c, 0x79, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str56_len = 25
str57 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str57_len = 13
str58 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str58_len = 13
str59 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x75, 0x6c, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str59_len = 13
str60 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str60_len = 14
str61 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x64, 0x69, 0x76, 0x69, 0x64, 0x65, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str61_len = 23
str62 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str62_len = 13
str63 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str63_len = 13
str64 db 0x09, 0x20, 0x78, 0x6f, 0x72, 0x20, 0x72, 0x64, 0x78, 0x2c, 0x20, 0x72, 0x64, 0x78, 0x0a, 0x00
str64_len = 16
str65 db 0x20, 0x20, 0x20, 0x20, 0x64, 0x69, 0x76, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str65_len = 13
str66 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str66_len = 14
str67 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x70, 0x72, 0x69, 0x6e, 0x74, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str67_len = 22
str68 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x64, 0x69, 0x0a, 0x00
str68_len = 13
str69 db 0x20, 0x20, 0x20, 0x20, 0x63, 0x61, 0x6c, 0x6c, 0x20, 0x70, 0x72, 0x69, 0x6e, 0x74, 0x0a, 0x00
str69_len = 16
str70 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x64, 0x75, 0x70, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str70_len = 20
str71 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x5d, 0x0a, 0x00
str71_len = 16
str72 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x6f, 0x76, 0x65, 0x72, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str72_len = 21
str73 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x2b, 0x38, 0x5d, 0x0a, 0x00
str73_len = 18
str74 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x73, 0x77, 0x61, 0x70, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str74_len = 21
str75 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str75_len = 13
str76 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x6f, 0x70, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str76_len = 13
str77 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str77_len = 14
str78 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str78_len = 14
str79 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x64, 0x72, 0x6f, 0x70, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str79_len = 21
str80 db 0x20, 0x20, 0x20, 0x20, 0x61, 0x64, 0x64, 0x20, 0x72, 0x73, 0x70, 0x2c, 0x20, 0x38, 0x0a, 0x00
str80_len = 16
str81 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x72, 0x6f, 0x74, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str81_len = 20
str82 db 0x20, 0x20, 0x20, 0x20, 0x61, 0x64, 0x64, 0x20, 0x72, 0x73, 0x70, 0x2c, 0x20, 0x38, 0x0a, 0x00
str82_len = 16
str83 db 0x09, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x20, 0x2b, 0x20, 0x31, 0x36, 0x5d, 0x0a, 0x00
str83_len = 23
str84 db 0x09, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x62, 0x78, 0x2c, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x20, 0x2b, 0x20, 0x38, 0x5d, 0x0a, 0x00
str84_len = 22
str85 db 0x09, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x63, 0x78, 0x2c, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x5d, 0x0a, 0x00
str85_len = 18
str86 db 0x09, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x20, 0x2b, 0x20, 0x31, 0x36, 0x5d, 0x2c, 0x20, 0x72, 0x62, 0x78, 0x0a, 0x00
str86_len = 23
str87 db 0x09, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x20, 0x2b, 0x20, 0x38, 0x5d, 0x2c, 0x20, 0x72, 0x63, 0x78, 0x0a, 0x00
str87_len = 22
str88 db 0x09, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x5d, 0x2c, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str88_len = 18
str89 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x6e, 0x69, 0x70, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str89_len = 20
str90 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x5b, 0x72, 0x73, 0x70, 0x5d, 0x0a, 0x00
str90_len = 20
str91 db 0x20, 0x20, 0x20, 0x20, 0x61, 0x64, 0x64, 0x20, 0x72, 0x73, 0x70, 0x2c, 0x20, 0x31, 0x36, 0x0a, 0x00
str91_len = 17
str92 db 0x20, 0x20, 0x20, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x72, 0x61, 0x78, 0x0a, 0x00
str92_len = 14
str93 db 0x20, 0x20, 0x20, 0x20, 0x3b, 0x3b, 0x20, 0x2d, 0x2d, 0x2d, 0x20, 0x65, 0x78, 0x69, 0x74, 0x20, 0x2d, 0x2d, 0x2d, 0x0a, 0x00
str93_len = 21
str94 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x61, 0x78, 0x2c, 0x20, 0x36, 0x30, 0x0a, 0x00
str94_len = 17
str95 db 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x76, 0x20, 0x72, 0x64, 0x69, 0x2c, 0x20, 0x30, 0x0a, 0x00
str95_len = 16
str96 db 0x20, 0x20, 0x20, 0x20, 0x73, 0x79, 0x73, 0x63, 0x61, 0x6c, 0x6c, 0x0a, 0x00
str96_len = 13
