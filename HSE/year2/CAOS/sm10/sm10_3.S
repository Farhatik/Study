        .text
        .global tree_find
tree_find:
        push    %ebp
        push    %ebx
        push    %edi
        push    %esi
        movl    %esp, %ebp
        movl    20(%ebp), %ebx
        movsd   24(%ebp), %xmm0
        movl    32(%ebp), %esi
check:
        testl   %ebx, %ebx
        jz      not_found
        movsd   (%ebx), %xmm1
        comisd  %xmm1, %xmm0
        jz      found
        ja      right_go
left_go:
        movl    8(%ebx), %ebx
        jmp     check
        
right_go:
        movl    12(%ebx), %ebx
        jmp     check

not_found:
        movl    $0, %eax 
        jmp     out


found:
        movl    $1, %eax   
        testl   %esi, %esi 
        jz      out
        movl    16(%ebx), %edx
        movl    %edx, (%esi)
out:
        movl    %ebp, %esp
        popl    %esi
        popl    %edi
        popl    %ebx
        popl    %ebp
        ret