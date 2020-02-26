%macro	syscall 1-*
%rep %0
%rotate -1
	push dword %1
%endrep
%ifdef OS_LINUX
	pop eax
	%if %0 > 1
		pop ebx
		%if %0 > 2
			pop ecx
			%if %0 > 3
				pop edx
				%if %0 > 4
					pop esi
					%if %0 > 5
						pop edi
						%if %0 > 6
							%error "Too many params for Linux syscall"
						%endif
					%endif
				%endif
			%endif
		%endif
	%endif
	int 80h
%endif
%endmacro

%ifdef TEST_HELLO
global _start
section .data
	msg db "Hello world", 10
	msg_len equ $-msg
section .text
	_start: syscall 4, 1, msg, msg_len
		syscall 1, 0
%endif

%ifdef COPY
section .bss
	buffer resb 4096
	bufsize equ $-buffer
	fdsrc resd 1
	fddest resd 1
	argc resd 1
	argvp resd 1

section .data
helpmsg db 'Usage: copy <src> <dest>', 10
helplen equ $-helpmsg
err1msg db "Couldn't open source file for reading", 10
err1len equ $-err1msg
err2msg db "Couldn't open destination file for writing", 10
err2len equ $-err1msg

section .text
global _start
_start:
	pop dword [argc]
	mov [argvp], esp
	cmp dword [argc], 3
	je .args_count_ok
	syscall 4, 2, helpmsg, helplen
	syscall 1, 1
 .args_count_ok:
	mov esi, [argvp]
	mov edi, [esi+4]
	syscall 5, edi, 0 ; 0_RDONLY
	cmp eax, 0
	jge .source_open_ok
	syscall 4, 2, err1msg, err1len
	syscall 1, 2
.source_open_ok:
	mov [fdsrc], eax
	mov esi, [argvp]
	mov edi, [esi+8]
%ifdef OS_LINUX
	syscall 5, edi, 241h, 0666o
%endif
	cmp eax, 0
	jge .dest_open_ok
	syscall 4, 2, err2msg, err2len
	syscall 1, 3
.dest_open_ok
	mov [fddest], eax
	.again:
		 syscall 3, [fdsrc], buffer, bufsize
		cmp eax, 0
		jle .end_of_file
		syscall 4, [fddest], buffer, eax
	jmp .again
.end_of_file:
	syscall 6, [fdsrc]
	syscall 6, [fddest]
	syscall 1, 0
%endif


