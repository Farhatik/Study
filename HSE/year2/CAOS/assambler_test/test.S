        .text
        .global main
main:
        call    readi32
        mov     %eax, %ebx
        call    readi32
        add     %ebx, %eax
        call    writei32
        call    nl
        call    finish
        xor     %ebx, %ebx
        xor     %eax, %eax
        ret