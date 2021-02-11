        .text
        .global myhypot
myhypot:
        push    %ebp
        movl    %esp, %ebp
        movsd   8(%ebp), %xmm0
        movsd   16(%ebp), %xmm1
        mulsd   %xmm0, %xmm0
        mulsd   %xmm1, %xmm1
        addsd   %xmm1, %xmm0
        sqrtsd  %xmm0, %xmm1
        movl    24(%ebp), %eax
        movsd   %xmm1, (%eax)

out:
        movl    %ebp, %esp
        popl    %ebp
        ret
