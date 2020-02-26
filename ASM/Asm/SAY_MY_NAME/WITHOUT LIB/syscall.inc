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



