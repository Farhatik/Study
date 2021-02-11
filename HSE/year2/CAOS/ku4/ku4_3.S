        .data
        .align  16
var1:   .double 1.0
var0:   .double 0.0
var_m:  .double -1.0
var_x:  .double 0.7
        
        .text
        .global mysin
mysin:
        push    %ebp
        push    %ebx
        push    %edi
        push    %esi
        movl    %esp, %ebp

        movsd   %xmm7, %xmm0 // temp_x^k
        movsd   var1,  %xmm1 // константа деления
        movsd   var0, %xmm3 //пред сумма
        movsd   %xmm0, %xmm4 // сумма

        movsd   var1, %xmm6 

step:
        comisd  %xmm3, %xmm4
        jz      prologue

        mulsd   %xmm7, %xmm0
        mulsd   %xmm7, %xmm0

        addsd   var1, %xmm1
        mulsd   %xmm1, %xmm6

        addsd   var1, %xmm1
        mulsd   %xmm1, %xmm6

        mulsd   var_m, %xmm6

        movsd   %xmm0, %xmm5
        divsd   %xmm6, %xmm5


        movsd   %xmm4, %xmm3
        addsd   %xmm5, %xmm4
        jmp     step


prologue:
        movsd   %xmm4, %xmm7
        movl    %ebp, %esp
        popl    %esi
        popl    %edi
        popl    %ebx
        popl    %ebp
        ret


/        .global main
/main:
/        movsd var_x, %xmm7
/        call mysin
/        ret