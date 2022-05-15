        .data
x:      .space	16	@ 4 parole 
y:      .word 1,2,3,4	@ 4 parole

        .text
        .global main

main:   ldr r0, =y	@ base y
        ldr r1, =x	@ base x
        ldr r3, =4	@ n contatore 


loop:   ldr r2, [r0], #4	@ carico y[i]              -- post-index
        str r2, [r1], #4	@ lo memorizzo in x[i]     -- post-index
        subs r3, r3, #1	@ quando arrivo a 0 ho finito (parto da N)
        bne loop		@ risparmio un registro e non serve più lo stack
        
        mov PC, LR		@ main {    return(r0);   }
