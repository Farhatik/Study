#include <asm/unistd_32.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
__asm__(
        ".data\n\t"
"c:      .byte   0\n\t"
"        .text\n\t"
"        .global _start\n\t"
"_start:\n\t"
        "movl    $3, %eax\n\t"
        "movl    $0, %ebx\n\t"
        "movl    $c, %ecx\n\t"
        "movl    $1, %edx\n\t"
        "int     $0x80\n\t"
        "cmpl    $1, %eax\n\t"
        "jne     out\n\t"
"step_cmp:\n\t"
        "cmpb    $97, c\n\t"
        "jb     step_write\n\t"
        "cmpb    $122, c\n\t"
        "ja      step_write\n\t"
        "subl    $32, c\n\t"
"step_write:\n\t"
        "movl    $4, %eax\n\t"
        "movl    $1, %ebx\n\t"
        "movl    $c, %ecx\n\t"
        "movl    $1, %edx\n\t"
        "int     $0x80\n\t"
        "jmp     _start\n\t"
"out:\n\t"
        "movl    $1, %eax\n\t"
        "xorl    %ebx, %ebx\n\t"
        "int     $0x80\n\t"
);