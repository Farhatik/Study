        .text
        .global main
main:
        xor     %ebx, %ebx
        xor     %esi, %esi
again:
        call    readi32
        jc      out
        test    $0x01, %al
        jnz     odd
even:   
        add     %eax, %ebx
        jmp     again
odd:
        add     %eax, %esi
        jmp     again
out:
        mov     %ebx, %eax
        call    writei32
        call    nl
        mov     %esi, %eax
        call    writei32
        call    nl
        xor     %ecx, %ecx
        xor     %edx, %edx
        xor     %eax, %eax
        ret