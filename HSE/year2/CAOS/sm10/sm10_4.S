        .data
        .align  16
vFar:   .float  0.0, 0.0, 0.0, 0.0


        .text
        .global dot_product
dot_product:
        push    %ebp
        push    %ebx
        push    %edi
        push    %esi
        movl    %esp, %ebp
        movl    20(%ebp), %eax
        movl    24(%ebp), %ecx
        movl    28(%ebp), %edx
        movaps  vFar, %xmm0
        movaps  vFar, %xmm3
        movaps  vFar, %xmm4
repeat:
        cmpl    $4, %eax
        jl      step_2
        subl    $4, %eax
        movups  (%ecx), %xmm1
        movups  (%edx), %xmm2
        mulps   %xmm1, %xmm2
        addps   %xmm2, %xmm3
        addl    $16, %ecx
        addl    $16, %edx
        jmp     repeat
step_2:
        haddps  %xmm0, %xmm3
        haddps  %xmm0, %xmm3
step_3:
        cmpl    $0, %eax
        jle     out
        movss   (%ecx), %xmm0
        movss   (%edx), %xmm4
        mulss   %xmm0, %xmm4
        addss   %xmm4, %xmm3
        decl    %eax
        addl    $4, %ecx
        addl    $4, %edx
        jmp     step_3
out:
        sub     $4, %esp        // резервируем память
        movss   %xmm3, (%esp)   // копируем значение double из %xmm0 в стек
        flds    (%esp)          // загружаем из стека на %st(0)
        add     $4, %esp        // очищаем стек
        movl    %ebp, %esp
        popl    %esi
        popl    %edi
        popl    %ebx
        popl    %ebp
        ret