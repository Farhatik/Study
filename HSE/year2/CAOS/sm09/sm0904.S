//Задача была разобрана на семинаре  
        .global process
process:
        push    %ebp
        push    %ebx
        push    %edi
        movl    %esp, %ebp
        xorl    %edi, %edi
repeat:
        call    read_numbers
        addl    %ebx, %edi
        jmp     repeat

print_res:
        movl    %ebp, %esp
        popl    %ebp
        push    %edi
        push    $f_out
        call    printf

out:
        movl    %ebp, %esp
        popl    %edi
        popl    %ebx
        popl    %ebp
        xorl    %eax, %eax
        xorl    %ecx, %ecx
        xorl    %edx, %edx
        ret

read_numbers:
        push    %ebp
        movl    %esp, %ebp
        subl    $36, %esp 

        leal    32(%esp), %eax
        leal    28(%esp), %ebx
        leal    24(%esp), %ecx
        leal    20(%esp), %edx

        movl    %eax, 16(%esp)
        movl    %ebx, 12(%esp)
        movl    %ecx, 8(%esp)
        movl    %edx, 4(%esp)
        movl    $f_in, (%esp)
        call    scanf
        cmpl    $4, %eax
        jne     print_res

        movl    32(%esp), %edx
        movl    28(%esp), %ecx
        movl    24(%esp), %ebx
        movl    20(%esp), %eax

        cmpl    %ecx, %ebx
        jge     check_zero
check_true:


        cmpl    %eax, %ecx
        jl      max_l
        movl    %ecx, %eax
max_l:
        cmpl    %ebx, %edx
        jg      min_r
        movl    %edx, %ebx
min_r:
        subl    %eax, %ebx
        jns     out_read
make_zero:
        movl    $0, %ebx

out_read:
        movl    %ebp, %esp
        popl    %ebp
        ret

check_zero:
        cmpl    %edx, %eax
        jl      check_true
        jmp     make_zero

        .data
f_in:   .asciz  "%d %d %d %d"
f_out:  .asciz  "%d\n"
        

/        .global main
/main:
/        call  process
/        xorl    %eax, %eax
/        xorl    %ecx, %ecx
/        xorl    %edx, %edx
/        ret
