        .text
        .global main
main:
        call    readi32
again:  
        cmp     $0, %eax
        jl      out
        movl    %eax, %ebx
        call    writei32
        call    nl
        movl    %ebx, %eax
        dec     %eax
        jmp     again
out:
        xor     %eax, %eax
        ret