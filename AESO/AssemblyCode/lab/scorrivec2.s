        .data
x:      .space	16	@ 4 parole 
y:      .word 1,2,3,4	@ 4 parole
        
        .text
        .global main

main:   ldr r0, =y	@ base y
        ldr r1, =x	@ base x
        mov r2, #0	@ indice
        ldr r3, =4	@ n
        
        push {r4}	@ salvo registro non temporaneo ma utilizzato

loop:   ldr r4, [r0], #4	@ carico y[i]             -- post-index
        str r4, [r1], #4	@ lo memorizzo in x[i]    -- post-index
        add r2, r2, #1
        cmp r2, r3 
        bne loop

        pop {r4}
	
        mov PC, LR
