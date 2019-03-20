/*
Question 4 : Conversion. 
Voici une façon très étrange d'afficher π :

int main(void) {
  long long int n = 4614256656552045848LL;
  double* p = (double*) &n;
  printf("%f", *p);
  putchar('\n');
  return EXIT_SUCCESS;
}

Le format %f et le type du pointeur p conduisent printf à penser que la valeur qui lui est fournie est un double.
Il interprète donc les bits qui la composent (qui sont pourtant les bits de n) comme s'ils décrivaient un réel. 
Il ne s'agit pas vraiment d'une conversion mais plutôt d'une réinterprétation.

Quelle valeur faut-il donner à n pour que ce programme affiche 2π ? Vous pouvez écrire un autre programme pour vous aider à trouver la réponse.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  long long int n = 4614256656552045848LL;
  // On additionne à n sa valeur en enlevant 848 car cela dépasse les capacité du type
  n += 4614256656552045LL;
  double* p = (double*) &n;
  printf("2pi = %f", *p);
  putchar('\n');
  return EXIT_SUCCESS;
}
