segment .text
global _start

main:
	ret
calculate:
	ret

_start:
	mov rax, 60
	mov rdi, 0
	syscall
