/* Question 2.5 : calc_part_sum.s
Traduire en assembleur INTEL le programme en C part_sum.c que vous avez fait :

Code :

int Simpair(unsigned int a,unsigned int b){
  unsigned int tmp,res=0;
  tmp=((a>>1)<<1)+1;
  while(tmp<=b){
    res+=tmp;
    tmp+=2;
  }
  return res;
}

int main(int argc,char ** argv){
  int a,b;
  a=(unsigned int) strtoul(argv[1],NULL,0);
  b=(unsigned int) strtoul(argv[2],NULL,0);
  if(a>b){ return 1; }
  S = Simpair(a,b);
  return 0; 
}
*/

.text
/* Importe la fonction Simpair */
.type Simpair, @function
.globl _start

_start:
   nop
   movq $1,%rbx /* rbx -> a=1 */
   movq $10,%rcx /* rcx -> b=10 */
   movq $0,%rax /* rax -> res=0 */
   /* Appel de la fonction Simpair dans _start */
   call Simpair
   /* Appel système, analyse du contenu des registres et sortie */
   movq %rax,%rdi
   movq $60,%rax
   syscall
   nop

Simpair:
  /* Mettre les registres à réutiliser au sommet de la pile */	
  pushq %rbp
  movq %rsp,%rbp
  /* Décalage logique à droite de a par 1, soit a>>1 */ 
  shrq $1,%rbx
  /* Décalage logique à gauche du tampon par 1, soit (a>>1)<<1 */
  shlq $1,%rbx
  /* Addition simple du tampon par 1, ((a>>1)<<1) + 1 */
  addq $1,%rbx
  /* while(...) */
  boucle:
    /* rbx -> x */
    addq %rbx,%rax /* res = res + tmp */
    addq $2,%rbx /* tmp = tmp + 2 */
    cmpq %rcx,%rbx /* if(a<b) */
  /* Aller à "boucle" si tmp <= b */      
  jle boucle
  leave /* Quitter */
  /* Analyse des registres avant de quitter */
  ret
