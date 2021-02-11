        .data
        .global p_format
p_format:
        .asciz  "%d %d %d\n"

        .global print_fib
print_fib:
        xor     %eax, %eax
        addl    A, %eax
        addl    B, %eax
        addl    B, %eax
        addl    A, %eax
        addl    B, %eax
        pushl   %eax
        subl    B, %eax
        subl    A, %eax
        pushl   %eax
        subl    B, %eax
        pushl   %eax
        pushl   $p_format
        call    printf
        addl    $16, %esp
        ret
