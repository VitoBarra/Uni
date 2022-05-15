        .data
x:      .space	16	@ 4 parole 
y:      .string "tre"	@ stringa

f:      .string "%s \n"

        .text
        .global main

main:   ldr r0, =y	@ base y
        ldr r1, =x	@ base x
        ldr r3, =4	@ n contatore - y ha 0 alla fine 


loop:   ldrb r2, [r0], #4	@ carico y[i]              -- post-index
        strb r2, [r1], #4	@ lo memorizzo in x[i]     -- post-index
        subs r3, r3, #1		@ quando arrivo a 0 ho finito (parto da N)
        bne loop		  	@ risparmio un registro e non serve più lo stack

stampa: push {LR}
        ldr r0, =f
        bl printf
        
        mov r0, #0
        pop {PC}			@ main {    return(0);   }
