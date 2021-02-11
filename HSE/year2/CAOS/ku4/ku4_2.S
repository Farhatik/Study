        .text
        .global process
process:
        push    %ebp
        push    %ebx
        push    %edi
        push    %esi
        movl    %esp, %ebp
        subl    $16, %esp
        //eax - указатель struc
        movl    $1, %esi
        movl    %eax, %ebx

        movl    (%ebx, %esi, 4), %eax //z[0]
        addl    $3, %esi
        movl    (%ebx, %esi, 4), %edx // y[1]
        imull   %edx // z[0] * y[1]
        movl    %eax, -4(%ebp) 
        movl    %edx, -8(%ebp) 

        movl    $2, %esi
        movl    (%ebx, %esi, 4), %eax //z[1]
        incl    %esi
        movl    (%ebx, %esi, 4), %edx //y[0]
        imull   %edx /// z[1] * y[0]


        movl    -4(%ebp), %esi
        movl    -8(%ebp), %edi

        addl    %eax, %esi
        adcl    %edx, %edi

        testl   $0x10000000, %edi 
        jz      step
        movl    $-1, %eax
        jmp     prologue
step:
        shrdl   $4, %edi, %esi
        shrl    $4, %edi
        testl   %edi, %edi
        jz      step2
        movl    $-1, %eax
        jmp     prologue
step2:
        movl    %esi, %eax

prologue:
        movl    %ebp, %esp
        popl    %esi
        popl    %edi
        popl    %ebx
        popl    %ebp
        ret
