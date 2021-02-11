//#include <asm/unistd_32.h>

        .data
c:      .byte   0
        .text
        .global _start
_start:
        movl    $3, %eax
        movl    $0, %ebx
        movl    $c, %ecx
        movl    $1, %edx
        int     $0x80
        cmpl    $1, %eax
        jne     out
step_cmp:
        cmpb    $48, c
        jbe     step_write
        cmpb    $57, c
        ja      step_write
        movl    $48, c
step_write:
        movl    $4, %eax
        movl    $1, %ebx
        movl    $c, %ecx
        movl    $1, %edx
        int     $0x80
        jmp     _start
out:
        movl    $1, %eax
        xorl    %ebx, %ebx
        int     $0x80