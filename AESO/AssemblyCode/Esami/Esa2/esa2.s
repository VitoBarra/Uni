.data 
a: .string "abcbbaccc" 
.text
.global main

main:
    mov r3,#0 
    ldr r0 , =a
    ldrb r1 ,[r0], #1
    cmp r1 ,#97
    bne no
    add r3,r3,#1
    ldrb r1 ,[r0], #1
    cmp r1,#98
    bne no
    add r3,r3,#1
bloop:
    ldrb r1 ,[r0] ,#1
    cmp r1,#97
    addeq r3,r3,#1
    beq si
    cmp r1,#98
    addeq r3,r3,#1
    beq bloop
no:
    mov r0,#0
    mov pc,lr
si:
    mov r0,r3
    mov pc,lr