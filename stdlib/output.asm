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
