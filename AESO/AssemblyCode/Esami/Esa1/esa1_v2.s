.data

a: .word 0x103728b2
.global main
.text


main:
push {r4} 
ldr r0,=a
ldrb r1,[r0],#1
ldrb r2,[r0],#1
ldrb r3,[r0],#1
ldrb r4,[r0],#1

lsr r1,r1,#4
lsr r2,r2,#4
lsr r3,r3,#4
lsr r4,r4,#4

add r0,r1,r2
add r0,r0,r3
add r0,r0,r4

lsr r1,r0, #4
lsl r1,r1, #4 
sub r0,r0,r1
pop {r4}
mov pc,lr