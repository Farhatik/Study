        .data
fmt64:  .asciz  "%llx"
fmt64e: .asciz  "%016llx\n"
fmt64n: .asciz  "%llx\n"

        .text
        .global mul64p
mul64p:
        push    %ebp
        push    %ebx
        push    %edi
        push    %esi
        movl    %esp, %ebp
 
        xorl    %esi, %esi    
        xorl    %edi, %edi

        subl    $80, %esp

//x : (ebx)(edx) 
//y : (esi)(edi)        
// (a*2^32 + b)(c*2^32 + d) = ac * 2^64 + (ad + bc) * 2^32 + b*d
        /movl    20(%ebp), %ebx малдший бит числа b
        /movl    24(%ebp), %edx старший бит числа a
        /movl    28(%ebp), %esi младший бит числа d
        /movl    32(%ebp), %edi старший бит числа c
//Младшая часть b*d
        movl    20(%ebp), %eax // b * d
        mull    28(%ebp)
        movl    %eax, -4(%ebp) //положили первые 32 бита итогового результата
        movl    %edx, -8(%ebp)

        // a * d 
        movl    24(%ebp), %eax
        mull    28(%ebp)

        movl    %eax, -32(%ebp) //младший
        movl    %edx, -36(%ebp) //старший

        //b * c
        movl    20(%ebp), %eax
        mull    32(%ebp)

        movl    %eax, -40(%ebp) //младший
        movl    %edx, -44(%ebp) //старший

                
        //a*c

        movl    24(%ebp), %eax
        mull    32(%ebp)
        
        movl    %eax, -48(%ebp) //младший
        movl    %edx, -52(%ebp) //старший
       
       

        // a * d + b * c + старшие значения b * d
        xorl    %ebx, %ebx
        movl    -8(%ebp), %eax

        movl    -36(%ebp), %edx

        movl    -52(%ebp), %esi
        
        addl    -32(%ebp), %eax
        adcl    %ebx, %edx
        adcl    %ebx, %esi
        
        addl    -40(%ebp), %eax
        adcl    %ebx, %edx
        adcl    %ebx, %esi


        addl    -44(%ebp), %edx
        adcl    %ebx, %esi

        addl    -48(%ebp), %edx
        adcl    %ebx, %esi

        movl    %eax, -56(%ebp) 
        movl    %edx, -60(%ebp)
        movl    %esi, -64(%ebp)



        orl     %esi, %edx

        jz      skip_print
        
        push    -64(%ebp)
        push    -60(%ebp)
        
        push    $fmt64
        call    printf
        push    -56(%ebp)
        push    -4(%ebp)
        push    $fmt64e
        call    printf
        jmp     out

skip_print:
        push    -56(%ebp)
        push    -4(%ebp)
        push    $fmt64n
        call    printf

out:
        movl    %ebp, %esp
        popl    %esi
        popl    %edi
        popl    %ebx
        popl    %ebp
        ret