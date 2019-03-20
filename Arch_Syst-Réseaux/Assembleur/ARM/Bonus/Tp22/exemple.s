.arm
.text
.globl _start
_start:
mov r7,#1
mov r1,#2
mov r2,#3
subs r0,r1,r2
sublt r0,r2,r1
swi 0x0
.end
