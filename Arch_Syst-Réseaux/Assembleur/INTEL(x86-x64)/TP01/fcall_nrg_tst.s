/* Question 3 : fcall_nrg_tst.s 
Deux fonctions g et f doivent être utilisées ici,
pour vérifier si deux valeurs sont différentes ou égales.
*/

.text
.global _start
.type f.@function
.type g.@function

_start:
  nop
  movq $5,%rdi /* a = 5 */
  movq $6,%rsi /* b = 6 */

  call f /* Appel de f */
  nop
  /* Analyse des registres et sortie */
  movq $60,%rax
  syscall
  nop

f:
  nop
  /* Sommet de la pile */
  push %rbp
  movq %rsp,%rbp

  movq %rsi,%rax
  addq %rax,%rdi

  call g /* Appel de la fonction g */
  incq %rax /* tmp++ */

  nop
  leave
  ret

g:
  nop
  /* Sommet de la pile */
  push %rbp
  movq %rsp,%rbp
	
  movq %rdi,%rax
  /* Multiplication par tmp */
  imulq %rsi,%rax

  nop
  leave
  ret
