.arm
.data
a: .word 95
b: .word 25

.text
.global _start

gcd:
push {lr}
cmp r4,r5
blt L
M:
cmp r4,r5
subgt r4,r5
bgt L
L:
pop {pc}
_start:
ldr r0,=a
ldr r4,[r0]
ldr r0,=b
ldr r5,[r0]
bl gcd
mov r0,r4
mov r7,#1
swi 0x0
.end
