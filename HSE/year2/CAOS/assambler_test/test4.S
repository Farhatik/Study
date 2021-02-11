        .text
        .global main
main:   
        movl    $0, %ebx
again:
        call    readi32
        jc      out
        add     %eax, %ebx
        jno     again
pos:
        movl    $2147483647, %ebx
        cmp     $0, %eax
        jg      out
neg:
        movl    $-2147483648, %ebx
out:    
        movl    %ebx, %eax
        call    writei32
        call    nl
        xor     %eax, %eax
        xor     %ebx, %ebx
        ret