        .global satsum
satsum: 
        push    %ebp
        mov     %esp, %ebp
        xor     %eax, %eax
        add     8(%ebp), %eax
        add     12(%ebp), %eax
        jnc     out
        mov     $0xffffffff, %eax
out:
        mov     %ebp, %esp
        pop     %ebp
        ret
