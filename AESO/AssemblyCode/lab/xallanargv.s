	.text 
	.global main

			@ scegliamo di mettere i parametri in r1 r2
			@ in modo da non sporcare r0
			@ primo argomento base e secondo esponente
main:   
	ldr r0, [r1, #8]@ prendi in r0 l'esponente dalla riga di comando
	push {r0}
        ldr r0, [r1, #4]@base
        push {r0}
        pop {r0}@atoi sulla base
	bl atoi
	mov r1, r0	@ e mettilo in r1
	pop {r0}@atoi sull'esponente
	bl atoi
	mov r2, r0	@ in r1, x
	bl  xan		@ chiamata della funzione ricorsiva
	mov r7, #1	@ il risultato lo restituisco come codice di ritorno
	svc 0 		@ exit(r0)

			@ funzione ricorsiva: if(n==0) return(1) else return(x*(chiamataricorsiva(x, n-1))
xan:	cmp r2, #0	@ controlla se siamo al caso base
	beq fine		@ in caso, restituiamo 1
ricor:	push {lr}	@ altrimenti salvo indirizzo di ritorno (x rimane invariato)
	sub r2, r2, #1  @ calcolo n-1
	bl xan		@ chiamata ricorsiva
	pop {lr}	@ mi riprendo indirizzo di ritorno
	mul r0, r0, r1	@ calcolo risultato
	mov PC, LR	@ e torno

fine: 	mov r0, #1	@ il risultato è 1, quello del caso base
	mov PC, LR	@ ritorno
