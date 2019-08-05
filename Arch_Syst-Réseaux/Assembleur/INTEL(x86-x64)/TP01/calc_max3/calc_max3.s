/*
Question 1.5 : calc_max3.s 
Traduire en assembleur intel le programme max_of_3.c que vous avez fait.

Code :

int max(int a, int b, int c) {
  int tmp=a;
  if(tmp<b){ tmp=b; }
  if(tmp<c){ tmp=c; }
  return tmp;
}

int main(int argc,char ** argv){
  int a,b,c,res;
  x=(int) strtol(argv[1],NULL,0);
  y=(int) strtol(argv[2],NULL,0);
  z=(int) strtol(argv[3],NULL,0);
  res=max(a,b,c);
}
*/

.text
/* Importation dans _start de la fonction max */
.type max, @function
.globl _start

/* Fonciton main, principale */
_start:
  nop
  movq $3,%rbx /* rbx -> a=3 */
  movq $2,%rcx /* rcx -> b=2 */
  movq $5,%rdx /* rdx -> c=5 */
  /* Appel de la fonction max */
  call max

  /* Appel système, avec le registre de sortie rdi, 
  et analyse du contenu des varaibles avant de quitter */
  movq %rax,%rdi
  movq $60,%rax
  syscall
  nop

/* Fonction max */
max:	
  /* Mettre au sommet de la pile pour appeler des varaibles, 
  venant d'un autre programme. */
  pushq %rbp
  movq %rsp,%rbp
  /* mettre le contenu de a dans rax servant de variable tampon */
  movq %rbx,%rax
  /* if(b<tmp) */
  cmpq %rcx,%rax
  
  jg condition
  /* Mettre b dans tmp */
  movq %rcx,%rax

  condition:
    /* if(c<tmp) */
    cmpq %rdx,%rax
    jg sortie /* return tmp */
    /* Mettre c dans tmp */
    movq %rdx,%rax
  
  /* Fin de fonction */
  sortie:
    leave /* Quitter */
    ret /* Analyser le contenu des variables avant de quitter l'étiquette */
