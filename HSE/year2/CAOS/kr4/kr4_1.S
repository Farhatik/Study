        .text
        .global forward$args
forward$args:
    # prologue
        pushl   %ebp

    # save all registers
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        movl    %esp, %ebp
        movl    20(%ebp),  %edx
        movl    24(%ebp),  %esi

        movl    $0, %ebx
        cmpl    $0, %edx
        jge     step
        movl    $~0, %ebx
step:
        pushl   %esi
        
        pushl   32(%ebp)

        pushl   %ebx
        pushl   %edx
        
        pushl   %ecx

        call    process
        movl    $-1, %edx
        imull   %edx
out:
        movl    %ebp, %esp
        popl    %edi
        popl    %esi
        popl    %ebx

        popl    %ebp
        ret

