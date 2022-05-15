
.data
s: .string "ciaorosso" 

.text

.global main
@ uso r0 e r1 come valore dei parametri

main:

    ldr r0,=s
    mov r1, #2
    
    push {lr}
    
    bl cambia



cambia: @r0 contiene il puntatore alla strigna, r1 l intere I , r8
    mov r2,#0
loop:
    push {r0}
    ldrb r0,[r0]  @ prendo il primo carattere
    mov r3,r0 
    cmp r0,#0
    beq endc
    push {lr} @salvo il link register per la catena dinamica
    bl cifra @ r0 registro risultato 
    pop {lr}
    cmp r3,r0 
    pop {r3}
    strneb r0,[r3]
    mov r0,r3
    addne r2,r2,#1 
    b loop
endc:
    mov r0,r2
    mov pc, lr @return

cifra:
    cmp r0,#0x61 @a
    cmpge r0,#0x7a@z
    addle r0,r0,r2
    cmp r0,#0x7a@z
    subgt r0,r0,#0x1a
    mov pc, lr

    











