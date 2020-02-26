section .text
global _start

strlen:
	push ebp
	mov ebp, esp
	push esi
	xor eax, eax
	mov esi, [ebp+8]
.lp:	cmp byte [esi], 0
	jz .quit
	inc esi
	inc eax
	jmp short .lp
.quit: pop esi
	pop ebp
	ret

newline:
	pushad
%ifdef OS_FREEBSD
	push dword 1
	push dword .nwl
	push dword 1; stdout
	mov eax, 4 ; write
	push eax
	int 80h
	add esp, 16
%elifdef OS_LINUX
	mov edx, 1
	mov ecx, .nwl
	mov ebx, 1
	mov eax, 4
	int 80h
%else
%error please define either OS_FREEBSD ot OS_LINUX
%endif
	popad
	ret
.nwl	db 10

_start:
	mov ecx, [esp]
	mov esi, esp
	add esi, 4
again: push dword [esi]
	call strlen
	add esp, 4
	push esi
	push ecx
%ifdef OS_FREEBSD
%else
	mov edx, eax
	mov ecx, [esi]
	mov ebx, 1
	mov eax, 4
	int 80h
%endif
	call newline
	pop ecx
	pop esi
	add esi, 4
	loop again
%ifdef OS_FREEBSD
	push dword 0
	mov eax, 1 ; _exit
	push eax
	int 80h
%else
	mov ebx, 0
	mov eax, 1
	int 80h
%endif
