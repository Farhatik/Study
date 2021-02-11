 
        .text
        .global exchange
exchange:
        push    %ebp
        push    %ebx
        push    %edi
        push    %esi
        movl    %esp, %ebp


        xorl    %ecx, %ecx //счетчик в начале
        xorl    %esi, %esi
        subl    $1, %edx
        jmp     miss_step

step:

        decl    %edx
        incl    %ecx
miss_step:
        cmpl    %ecx, %edx
        jbe     prologue
        
        movl    (%eax, %ecx, 4), %ebx
        movl    (%eax, %edx, 4), %edi 

        cmpl    %edi, %ebx
        jbe     step

        movl    %ebx, (%eax, %edx, 4)
        movl    %edi, (%eax, %ecx, 4)
        incl    %esi

        jmp     step




prologue:
        movl    %esi, %ecx
        movl    %ebp, %esp
        popl    %esi
        popl    %edi
        popl    %ebx
        popl    %ebp
        ret
