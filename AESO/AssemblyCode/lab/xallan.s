	.text 
	.global main

			@ scegliamo di mettere i parametri in r1 r2
			@ in modo da non sporcare r0
main:	
    mov r1, #2	@ in r1, x
	mov r2, #3 	@ in r2, n
	
    bl  xan		@ chiamata della funzione ricorsiva
	
    mov r7, #1	@ il risultato lo restituisco come codice di ritorno
	svc 0 		@ exit(r0) - valore da leggere con echo $? [Expands to the exit status of the most recently executed foreground pipeline]

			@ funzione ricorsiva: if(n==0) return(1) else return(x*(xan(x, n-1))
xan:	
    cmp r2, #0	@ controlla se siamo al caso base
	beq fine	@ in caso, restituiamo 1

ricor:	
    push {lr}	@ altrimenti salvo indirizzo di ritorno (x rimane invariato)
	sub r2, r2, #1  @ calcolo n-1
	bl xan		@ chiamata ricorsiva
	pop {lr}	@ mi riprendo indirizzo di ritorno
	mul r0, r0, r1	@ calcolo risultato
	mov PC, LR	@ e torno

fine: 	mov r0, #1	@ il risultato è 1, quello del caso base
	mov PC, LR	@ ritorno
	

