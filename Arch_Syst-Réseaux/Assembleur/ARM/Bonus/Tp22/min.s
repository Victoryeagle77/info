.arm
.equ SWI_Exit,0x1
.data
a: .word 7
b: .word 9
res: .word 0
.text
.globl _start
min:
push {lr}
mov r3,r1
cmp r2,r1
movlt r3,r1
pop {pc}
.start:
ldr r0,=a
ldr r1,[r0]
ldr r0,=b
ldr r2,[r0]
bl min
ldr r0,=res
str r3,[r0]
mov r7,#SWI_Exit
mov r0,r3
swi 0x0
.end
