// a (eax, edx) (в eax - младшие 32 бита, в edx - старшие 32 бита)
// b (esi, edi) (в esi - младшие 32 бита, в edi - старшие 32 бита)

// 
//        .data
//       .global A, B
//A:      .quad   10
//B:      .quad   15
//C:      .quad   0
        .data
        .global fmt64
fmt64:  .asciz  "%llu\n"
/A:      .quad   10
/B:      .quad   15
//fmt32:  .asciz  "%d\n"
//fmtu32: .asciz  "%u\n"

        .text
        .global process
process:
//epilog:
        push    %ebp
        push    %edi
        push    %esi
        push    %ebx
        movl    %esp, %ebp

        movl    $A, %ebx
        movl    (%ebx), %eax
        addl    $4, %ebx     
        movl    (%ebx), %edx
        
        movl    $B, %ebx
        movl    (%ebx), %esi
        addl    $4, %ebx
        movl    (%ebx), %edi

        addl    %eax, %eax
        adcl    %edx, %edx

        shr     $1, %esi

        test    $1, %edi
        jz      c_fl
        addl    $0x80000000, %esi 
c_fl:
        shr     $1, %edi
        subl    %esi, %eax
        sbbl    %edi, %edx

        push    %edx
        push    %eax
        push    $fmt64
        call    printf

out:
        movl    %ebp, %esp
        popl    %ebx
        popl    %esi
        popl    %edi
        popl    %ebp
        ret

     
/        .global main
/main:
/        call process
/        ret