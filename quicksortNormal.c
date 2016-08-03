#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//VARIÁVEIS GLOBAIS PARA AS OPERAÇÕES DO QUICKSORT
int *lista, tamanho = 100000;

//VARIÁVEIS GLOBAIS PARA OPERAÇÕES DE ANÁLISE DE DESEMPENHO
unsigned int tt;
time_t ti, tf;

void quicksortNormal(int vtr[]){
  int pivo = vtr[0], i = 0, j = 0, aux = 0;
  int inicio = vtr[0], fim = vtr[1];

  for(i=(inicio+1); i<=fim; i++){
      j = i;

      if(lista[pivo] > lista[j]){
       aux = lista[j];

       while(pivo < j){
          lista[j] = lista[j-1];
          j--;
       }
       lista[j] = aux;
       pivo++;
      }
  }
  // ORDENAÇÃO DOS ITENS DO VETOR À ESQUERDA DO PIVÔ
  aux = fim;
  if((pivo-1) >= inicio){
      vtr[1] = (pivo-1);
      quicksortNormal(vtr);
  }
  // ORDENAÇÃO DOS ITENS DO VETOR À DIREITA DO PIVÔ
  if((pivo+1) <= fim){
      vtr[0] = (pivo+1);
      vtr[1] = aux;
      quicksortNormal(vtr);
  }
 }


int main(){
  int i = 0, vtr[2] = {0, (tamanho-1)};

  // ALOCANDO TAMANHO DO VETOR E ATRIBUINDO VALORES ALEATÓRIOS A ELE
  lista = malloc( (tamanho*sizeof(int)) );
  srand( (unsigned)time(NULL) );
  for(i=0; i<tamanho; i++){
      lista[i] = (rand() % 100);
  }

  ti = clock();
  quicksortNormal(vtr);
  tf = clock();
  tt = tf - ti;

  printf("Quicksort Normal:\n");
  printf("Clocks gastos: %u\n", tt);
  printf("Tempo gastto:  %.2fs\n", tt / (float)(CLOCKS_PER_SEC));

  // LIBERANDO ESPAÇO DA MEMÓRIA E FINALIZANDO PROGRAMA
  free(lista);
  return 0;
}
