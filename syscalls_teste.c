#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>

int main(){
  int r, i, a[] = {1, -12, 34, 54, 99, 43, 12, 55, 78, -99};

  printf("Iniciando SysCall\n");
  r = syscall(329, a, 0, 10);

  if(){
    printf("Deu Bom! :D\n");
  } else{
    printf("Deu Ruim! :(\n");
  }

  printf("Visualizando vetor a nível de usuário\n");
  for(i=0; i<10; i++)
    printf("%i", a[i]);
  printf("\n");
  printf("dmesg para ver o log do Kernel\n");

  return 0;  
}
