%include "syscall.inc"
global getstr

section .text
getstr: push ebp
	mov ebp, esp
	sub esp, 4
	xor eax, eax
	mov [ebp-4], eax
.again:
	mov eax, [ebp+8]
	add eax, [ebp-4]
	syscall 3, 0, eax, 1
	cmp eax, 1
	jne .eol
	mov eax, [ebp+8]
	add eax, [ebp-4]
	mov bl, [eax]
	cmp bl, 10
	jne .noeol
	dec dword [ebp-4]
	jmp .eol
.noeol: mov eax, [ebp-4]
	inc eax
	cmp eax, [ebp+12]
	jae .eol
	inc dword [ebp-4]
	jmp .again
.eol: mov eax, [ebp+8]
	add eax, [ebp-4]
	inc eax
	xor bl, bl
	mov [eax], bl
	mov esp, ebp
	pop ebp
	ret
