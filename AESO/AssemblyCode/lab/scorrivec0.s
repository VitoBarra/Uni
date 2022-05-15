        .data
x:      .space	16	@ 4 parole init a zero - simile a .fill 
y:      .word 1,2,3,4	@ 4 parole

        .text
        .global main

main:   ldr r0, =y	@ base y
        ldr r1, =x	@ base x
        mov r2, #0	@ indice i
        ldr r3, =4	@ n, carica il valore 4 in r3
        
        push {r4,r5}	       @ salvo registro non temporaneo ma utilizzato

loop:   lsl r5, r2, #2	       @ moltiplico i per 4 (ogni posizione dell'array contiene 4 byte)
        ldr r4, [r0, r5]	   @ carico y[i]
        str r4, [r1, r5]	   @ lo memorizzo in x[i] - per vedere x: x/4dw addr r1
        add r2, r2, #1         @ incremento i di 1
        cmp r2, r3 
        bne loop
        
        pop {r4,r5}
        
        mov PC, LR
        