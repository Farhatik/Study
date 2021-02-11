// Заготовка кода на консе была

    .data


    .text
    
    .global f
f:
  # prologue
    pushl   %ebp

  # save all registers
    pushl   %ebx
    pushl   %esi
    pushl   %edi
    movl    %esp, %ebp
    # your code here






    # end of your code
    
    # restore registers
    movl    %ebp, %esp
    popl    %edi
    popl    %esi
    popl    %ebx

  # epilogue
    popl    %ebp
    ret


    .global main
main:
        call f
        ret