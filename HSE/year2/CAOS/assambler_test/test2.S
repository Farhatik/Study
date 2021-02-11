        .data 
        .global A, B, C, D, R
A:      .int    0
B:      .int    0
C:      .int    0
D:      .int    0
R:      .int    0

        .text
        .global process
process:
        movl    C, %eax
        imull   D
        movl    %eax, %ecx
        movl    A, %eax
        imull   B
        sub     %ecx, %eax
        movl    %eax, R
        xor     %eax, %eax
        xor     %ecx, %ecx
        ret

main:
        call readi32
        movl %eax, A
        call readi32
        movl %eax, B
        call readi32
        movl %eax, C
        call readi32
        movl %eax, D
        call process
        movl R, %eax
        call writei32
        call nl
        xor %eax, %eax
        ret
