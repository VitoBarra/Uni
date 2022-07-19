.data

a: .word 0x10372841

.global hash
.text


hash:
push {r4} 
ldr r0,=a
ldr r0,[r0]
and r1,r0,#0x000000F0
and r2,r0,#0x0000F000
and r3,r0,#0x00F00000
and r4,r0,#0xF0000000

lsr r1,r1,#4
lsr r2,r2,#12
lsr r3,r3,#20
lsr r4,r4,#28


add r0 ,r1,r2
add r0,r0,r3
add r0,r0,r4

lsr r1,r0, #4
lsl r1,r1, #4 
sub r0,r0,r1
pop {r4}
mov pc,lr
