// Заготовка кода на консе была
        .text
        .global процесс
процесс:
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
        movl    %eax, %ebx

        movl    20(%ebp), %eax
        movzbl  (%eax), %eax
        test    $0x80, %eax
        jz      step1
        addl    $0xFFFFFF00, %eax
step1:
        movl    $2, %ecx
        imull   %ecx
        cmpl    $127, %eax 
        jg      out_2
        cmpl    $-128, %eax 
        jl      out_2

        subl    %eax, %ebx

        cmpl    $127, %ebx 
        jg      out_3
        cmpl    $-128, %ebx 
        jl      out_3
        movl    28(%ebp), %eax
        movl    %ebx, (%eax)
        movl    $0, %eax
        jmp     out



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


/        .global main
/main:
/        push    $C
/        push    B
/        push    $A
/        call    process
/        call    writei32
/        call    nl
/        addl    $12, %esp 
/        movl    C, %eax
/       call    writei32
/        call    nl
/        ret