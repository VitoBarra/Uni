.data
s: .string "az"
n: .word 3,0,1
ns: .word 3
.text
.global main
main:
    ldr r2, =ns

    ldr r2,[r2]
    mov r3,#0 @indice del for
for:
    ldr r0,=s
    ldr r1,=n 
    ldr r1 ,[r1,r3,lsl #2] @moltiplico l indice r3 per 4 (logica shift di 2 posizioni)
    push {r1-r3}
    push {lr}
    bl cambia
    pop {lr}
    pop {r1-r3}
    add r3,#1
    cmp r3 ,r2 @confronta se l indice è arrivato a ns
    blt for

    ldr r0,=s 
    mov r7,#1
    svc 0



@r0 puntatore strigna r1 valore da cambiare
cambia: 
    mov r2,#0 @contatore 
    cmp r1, #0
    beq exitc @ esco se la modifica risulterebbe nulla dando come risultato ovviamente 0
loopc:
    ldrb r3,[r0]
    cmp r3,#0
    beq exitc @ controla se il carattere in esame è quello di terminazione
    push {r0} @ push indirizzo del carattere corrente
    mov r0,r3 @ preparo il parametro per la funzione cifra (carattere)
    push {lr}
    bl cifra
    pop {lr}
    cmp r0,r3 @nuovo carattere con vecchio carattere
    pop {r3} @ pop indirizzo del carattere corrente
    strneb r0,[r3] @sostituisco il carattere corrente con il nuovo
    addne r2,r2,#1 @incremento il contatore
    add  r0,r3,#1 @ sposto l indirizzo del carattere corrente al prossimo carattere
    b loopc
exitc:
    mov r0,r2
    mov pc, lr


@r0 puntatore carattere r1 valore da aggiungere
cifra:
    cmp r0,#0x61 @a
    cmpge r0,#0x7a@z
    addle r0,r0,r1
    cmp r0,#0x7a@z
    subgt r0,r0,#0x1a
    mov pc, lr
