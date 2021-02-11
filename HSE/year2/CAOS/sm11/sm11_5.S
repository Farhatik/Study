        .text
        .global writeu32
writeu32:
        push    %ebp
        push    %ebx
        push    %edi
        push    %esi
        movl    %esp, %ebp
 
        movl    %ecx, %edi
        xorl    %esi, %esi
step:
        decl    %esi
        movl    $-858993459, %edx
        movl    %edx, %eax
 
        mull    %edi
        movl    %edx, %ebx
        shrl    $3, %ebx
 
 
        leal    (%ebx,%ebx,4), %eax
        addl    %eax, %eax
 
 
        subl    %eax, %edi
 
        push    %edi
 
        movl    %ebx, %edi
 
        cmpl    $0, %edi
        jnz     step
 
 
wr222_num:
        testl   %esi, %esi
        jz      out
        popl    %ecx
        addl    $'0', %ecx
        movl    stout, %edx
        call    writechar
        incl    %esi
        jnz     wr222_num
 
out:    
        movl    %ebp, %esp
        popl    %esi
        popl    %edi
        popl    %ebx
        popl    %ebp
        ret