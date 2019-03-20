.arm
.text
.globl _start
_start:
mov r7, #1
mov r1, #5
mov r2, #4

mov r0,r2
cmp r1,r2
movlt r0,r1
swi 0x0
.end
