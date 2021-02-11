        .data
SC:     .asciz  "%d"
PR:     .asciz  "%d\n"

        .text
/        .global main
/main:
        /call    process
        /xor     %eax, %eax
        /ret


        .global processы
process:
        push    %ebps
        push    %ebx
        push    %edi

        movl    %esp, %ebp

        xorl    %ebx, %ebx
        xorl    %edi, %edi
        xorl    %eax, %eax

        subl    $12, %esp
        leal    8(%esp), %eax
        movl    %eax, 4(%esp)
        movl    $SC, (%esp)
        call    scanf


read_num:
        cmpl    -4(%ebp), %ebx
        je      get_print
        incl    %ebx

        subl    $12, %esp
        leal    8(%esp), %ecx
        movl    %ecx, 4(%esp)
        movl    $SC, (%esp)
        call    scanf

        jmp     read_num

get_print:
        xorl    %ebx, %ebx
        movl    $12, %eax
        movl    -4(%ebp), %ecx
        imul    %ecx
        movl    %eax, %ecx
        addl    $4, %ecx
        movl    %ebp, %edi
        subl    %ecx, %edi
print_num:
        cmpl    -4(%ebp), %ebx
        je      out
        incl    %ebx
        push    (%edi)
        push    $PR
        call    printf
        addl    $12, %edi
        jmp     print_num

out:
        movl    %ebp, %esp
        popl    %edi
        popl    %ebx
        popl    %ebp
        xorl    %eax, %eax
        ret