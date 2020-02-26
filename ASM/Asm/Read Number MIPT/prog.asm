section .bss
    buffer resb 20

section .text
global _start
_start:
    call scan_int   ; читать int  из stdin в регистр eax
    push eax        ; поместить eax в стек — это будет 
                    ; аргументом для следующей функции

    call print_int  ; напечатать int, который находится в вершине стека
                    ; в стандартный поток вывода
                    ; "call func" эквивалентно 
                    ;    push <адрес_следующей_инструкции>;
                    ;    jmp func

    mov eax, 1      ; Эти три строчки эквиваленты exit(0)
    mov ebx, 0      ;
    int 0x80        ;

scan_int:           ; эта функция должна читать int из stdin,
    mov eax, 133    ; но пока она не реализована и просто 
    ret             ; возвращает число 133

print_int:          ; функция печати целого числа в stdout
                    ; аргумент (4-байтовое целое число)
                    ; находится в вершине стека
    ; ebp содержит адрес начала stack frame
    ; esp содержит адрес вершины стека
    ; esp < ebp, то есть вершина имеет меньший адрес
    ; в начале по адресам (ebp-4, ebp-3, ebp -2, ebp -1) лежат
    ; четыре байта целого числа, которое нам передали 
    ; в качестве аргумента

    push ebp        ; поместим в стек адрес начала стека 
                    ; этот push автоматически делает esp -= 4 
    mov ebp, esp    ; теперь ebp равно esp 
                   
                     ; аргумеенты находятся по адресу ebp + 8
    mov ecx, [ebp+8] ; значение переданного нам целого числа поместим в ecx

    xor edx, edx     ; обнулим edx
    mov esi, 10      ; на 10 мы будем делить.

    mov edi, 18      ; символы-цифры нашего числа мы будем помещать
                     ; по адресам buffer + 17, buffer+16, buffer+15, ...

    mov byte [buffer + 18], 0xA ; 19-й и 20-й символы — это перенос строчки
    mov byte [buffer + 19], 0   ; и символ конца строки

.loop:
    mov eax, ecx   ;
    xor edx, edx   ; данные четыре строки дают
    div esi        ;   ecx = ecx / 10 
    mov ecx, eax   ;


    add edx, '0'  ; '0' ассемблером интерпретируется как ASCII код символа '0'
    dec edi
    mov byte [buffer+edi], dl
    cmp ecx, 0
   ; jne .loop

    mov eax, 4        ; эквивалентно write( 1, buffer + edi, 19 - edi )
    mov ebx, 1
    mov ecx, buffer   ; можно короче — lea ecx, [buffer+edi]
    add ecx, edi
    mov edx, 19
    sub edx, edi
    int 0x80

    leave       ; эквивалентно  mov esp, ebp
                ;               pop ebp 
    ret         ; эквивалентно  pop IP 
                ;               
