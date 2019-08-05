.section .text
.type printint, @function
.globl _start

_start:
  nop
  rdtsc

  shlq $32, %rdx
  orq %rdx,%rax
  movq %rax,%r8
	
  nop
  rdtsc

  shlq $32, %rdx
  orq %rdx,%rax
  subq %r8,%rax
	
  call printint
	
  nop
  movq $60,%rax
  syscall
  nop

