.section .text
.globl printint

printint:
  pushq %rbp
  movq %rsp,%rbp

  nop
  movq $1234, %rax
  movq $10, %rcx
  movq $0, %rdx

  decq %rsp
  movb $0,(%rsp)
  decq %rsp
  movb $0xa,(%rsp)
  decq %rsp
  movq $2, %rbx

L:	
  addq $1, %rbx
  divq %rcx
  addq $0x30, %rdx
  movb %dl,(%rsp)
  decq %rsp
  movq $0,%rdx

  cmpq $0,%rax
  jne L

  movq $1, %rax
  movq $1, %rdi
  movq %rbx, %rdx

  movq %rsp,%rsi
  syscall

  movq $60,%rax
  syscall
  nop

