    .data
arr:.word 5,1,8,3
nl: .word 4
s: .string "%d "


    .text
    .global main

main: 
    push {lr}
    ldr r0, =arr
    ldr r1, =nl
    ldr r1, [r1]
    push {r1}
    bl bublesort
    pop {r1}
    mov r3,r0 @arr
    mov r2 ,#0 @i=0
    ldr r0, =s 
print:
    cmp r2, r1
    bge con
    push {r0-r3}
    ldr r1 , [r3,r2,lsl #2]
    bl printf
    pop {r0-r3}
    add r2,r2,#1
    b print
con:
    pop {pc}



bublesort: @r0 =array ind, r1=lenght array
push {r4-r7}
mov r2 ,#1 @scambio=true

while:
cmp r2,#0
beq fi @ se non uguale 
mov r2,#0 @scambio=false
sub r1 ,#1 @la=la-1

mov r3, #0 @i=0
mov r4, #1 @j=i+1
for:  
cmp r3 , r1
bge while @ controllo condizio for i < la

ldr r5,[r0,r3, lsl #2]  
ldr r6,[r0,r4, lsl #2] @ carico i due elementi del array

cmp r5,r6 @ comapro a[i] e a[i+1]

strgt r5,[r0,r4, lsl #2]  
strgt r6,[r0,r3, lsl #2] @se magiore faccio swap
movgt r2, #1

add r3,r3,#1 @ incremento i
add r4,r3,#1 @ incremento i+1
b for
fi:
    pop {r4-r7}
    mov pc,lr


