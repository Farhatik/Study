// Заготовка кода на консе была

        .data
A:      .int 10
B:      .int 5
C:      .int 0

        .text
        
        .global process
process:
    # prologue
        pushl   %ebp

    # save all registers
        pushl   %ebx
        pushl   %esi
        pushl   %edi
        movl    %esp, %ebp
        
        # your code here
        movl    24(%ebp), %eax
        movl    $3, %ebx
        imull   %ebx
        jo      out_1
        /shr     $8, %eax
        movl    %eax, %ebx
        movl    20(%ebp), %eax
        movzbl  (%eax), %eax
        movl    $2, %ecx
        mull    %ecx
        js      check_1

        test    $0x7FFFFF00, %eax
        jnz     out_2
R1:
        js      check_2
        subl    %eax, %ebx

        test    $0xFFFFFF00, %ebx
        jnz     out_3
R2:

        movl    28(%ebp), %eax
        movzbl  (%eax), %eax
        movl    %ebx, %eax
        movl    $0, %eax
        jmp     out


check_1:
        negl    %eax
        test    $0xFFFFFF00, %eax
        jnz     out_2
        negl    %eax
        jmp     R1

check_2:
        negl    %ebx
        test    $0xFFFFFF00, %ebx
        jnz     out_2
        negl    %ebx
        jmp     R2



out_1:
        movl    $1, %eax
        jmp     out

out_2:
        movl    $2, %eax
        jmp     out


out_3:
        movl    $3, %eax
        jmp     out
        # end of your code
        
out:
        movl    %ebp, %esp
        popl    %edi
        popl    %esi
        popl    %ebx

        popl    %ebp
        ret


        .global main
main:
        push    $C
        push    B
        push    $A
        call    process
        call    writei32
        call    nl
        addl    $12, %esp 
        movl    C, %eax
        call    writei32
        call    nl
        ret