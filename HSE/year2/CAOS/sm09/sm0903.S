        .global mystrcmp
mystrcmp:
        push    %ebp
        push    %ebx
        mov     %esp, %ebp
        xor     %eax, %eax
        xor     %ecx, %ecx
        xor     %edx, %edx
        mov     12(%ebp), %eax
        mov     16(%ebp), %ebx
        

again:
        movb    (%eax), %cl
        movb    (%ebx), %dl
        cmpb    $0x00,  %cl           
        jz      check_same
        cmpb    $0x00,  %dl
        jz      out_pos
        cmpb    %cl, %dl
        ja      out_neg
        jb      out_pos
        inc     %eax
        inc     %ebx
        jmp     again

out_neg:
        mov     $0xFFFFFFFF, %eax
        jmp     out


out_pos:
        mov     $1, %eax
        jmp     out

check_same:
        cmpb    $0,  %dl 
        jz      out_same
        jmp     out_neg
        

out_same:
        xor     %eax, %eax
        jmp     out

out:
        xor     %ecx, %ecxя
        xor     %edx, %edx
        mov     %ebp, %esp
        pop     %ebx
        pop     %ebp
        ret

        /.global main
/main:   
        /push    $str2
        /push    $str1
        /call    mystrcmp
        /add     $8, %esp
        /push    %eax
        /push    $format
        /call    printf
        /add     $8, %esp
        /xor     %eax, %eax
        /ret
        
        /.data
        /.global str1, str2, format
/format:     .asciz "%d\n"
/str1:       .asciz "fabsbd"
/str2:       .asciz "asdasd"
/F:          .asciz "%c %c\n"