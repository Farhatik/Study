        .text
        .global shrbe
shrbe:
        push    %ebp
        push    %ebx
        push    %edi
        push    %esi
        movl    %esp, %ebp

        movl    %edx, %esi // *p
        movl    %eax, %edi //n

        movl    %ecx, %ebx //cnt

        subl    $16, %esp
        movl    $0, -12(%ebp)

big_step:

        movl    $0, -4(%ebp)
        movl    $0, -8(%ebp)

        movl    $0, %ecx

        cmpl    -12(%ebp), %ebx
        je      prologue

        incl    -12(%ebp)


step:   
        cmpl    %edi, %ecx
        je      big_step
        ja      last_step

        xorl    %eax, %eax
        xorl    %edx, %edx

        movb    (%esi, %ecx, 1), %al
        addl    $1,  %ecx
        shldl   $8, %edx, %eax    

        movb    (%esi, %ecx, 1), %al

        testb   $1, %al
        jz      skip_add_carry
        movl    $1, -4(%ebp)
        jmp     skip_add_carry2

skip_add_carry:
        movl    $0, -4(%ebp)   

skip_add_carry2:
        shrw    %ax
        movl    -8(%ebp), %edx    
        testl   $1, %edx
        jz      skip_add_bit
        addl    $32768, %eax

skip_add_bit:
        movl    -4(%ebp), %edx
        movl    %edx, -8(%ebp)

        movb    %al, (%esi, %ecx, 1) 
    
        subl    $1,  %ecx
        xorl    %edx, %edx
        shrdl   $8, %edx, %eax    
        movb    %al, (%esi, %ecx, 1)

        addl    $2,  %ecx
        jmp     step

last_step:
        subl    $1, %ecx
        movb    (%esi, %ecx, 1), %al
        shrb    %al

        movl    -8(%ebp), %edx    
        testl   $1, %edx
        jz      skip_add_bit2
        addb    $128, %al
skip_add_bit2:
        movb    %al, (%esi, %ecx, 1)
        jmp     big_step
prologue:
        movl    %ebp, %esp
        popl    %esi
        popl    %edi
        popl    %ebx
        popl    %ebp
        ret