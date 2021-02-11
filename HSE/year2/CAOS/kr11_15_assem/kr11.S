// Заготовка кода на консе была

        .data
        .global A, B, C
A:      .int    1
B:      .int    2
C:      .int    3
/fmt:    .asciz  "%u\n"


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
        movl    %edx, %eax
        movl    %edx, %esi
        mull    %esi
        mull    A
        movl    %eax, %ebx
        movl    %esi, %eax
        mull    B
        movl    $5, %edi
        mull    %edi
        subl    %eax, %ebx
        movl    %ebx, %edx
        movl    %ebx, %eax
        addl    C, %ebx
        addl    C, %ebx
        movl    %ebx, %edx

        movl    %ebx, %edx



        # end of your code
        
        # restore registers
        movl    %ebp, %esp
        popl    %edi
        popl    %esi
        popl    %ebx

    # epilogue
        popl    %ebp
        ret


        /.global main
/main:
 /       movl    $4, %edx
/        call    process
 /       push    %edx
  /      push    $fmt
   /     call    printf
    /    addl    $8, %esp
     /   ret