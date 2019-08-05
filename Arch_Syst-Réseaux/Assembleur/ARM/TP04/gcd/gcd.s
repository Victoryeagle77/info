/* Question 1 : gcd de 2 entiers */

.equ SYS_EXIT, 1

.arm
.data
  a: .word 40
  b: .word 30

.text
.globl _start

/* int gcd(int a, int b) */
gcd:  
  cmp r1, r2 /* while(a != b) */
  /* if(a > b) { a = a-b; } */
  subgt r1, r1, r2
  /* else { b = b-a; } */
  sublt r2, r2, r1
  /* return a */
  bne gcd
  b sortie
  
/* int main(void) */
_start:
  ldr r3, =a
  ldr r1, [r3]
  ldr r4, =b
  ldr r2, [r4]
  b gcd
    
sortie:
  mov r0, #0
  mov r7, #SYS_EXIT
  swi #0
.end
