#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//VARIÁVEIS GLOBAIS PARA AS OPERAÇÕES DO QUICKSORT
int *lista, tamanho = 100000;

//VARIÁVEIS GLOBAIS PARA OPERAÇÕES DE ANÁLISE DE DESEMPENHO
time_t ti, tf;
unsigned int tt;

void *quicksortThread(void *arg){
  //CONVERSÃO DO ARGUMENTO
  int *vtr = (int *)(arg);

  //THREADS
  pthread_t t1, t2;
  pthread_attr_t att1, att2;

  //VARIÁVEIS DA FUNÇÃO
  int pivo = vtr[0], i = 0, j = 0, aux = 0;
  int inicio = vtr[0], fim = vtr[1];

  // ORDENAÇÃO DOS MAIORES E MENORES QUE O PIVÔ
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
      pthread_attr_init(&att1);
      pthread_create(&t1, &att1, quicksortThread, (void *)(vtr));
      quicksortThread((void *)(vtr));
  }
  // ORDENAÇÃO DOS ITENS DO VETOR À DIREITA DO PIVÔ
  if((pivo+1) <= fim){
      vtr[0] = (pivo+1);
      vtr[1] = aux;
      pthread_attr_init(&att2);
      pthread_create(&t2, &att2, quicksortThread, (void *)(vtr));
      quicksortThread((void *)(vtr));
  }
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_exit(0);
 }

int main(){
  int i = 0, vtr[2] = {0, (tamanho-1)};

  //THREAD
  pthread_t t1;
  pthread_attr_t attr;

  // ALOCANDO TAMANHO DO VETOR E ATRIBUINDO VALORES ALEATÓRIOS A ELE
  lista = malloc( (tamanho*sizeof(int)) );
  srand( (unsigned)time(NULL) );
  for(i=0; i<tamanho; i++){
      lista[i] = (rand() % 100);
  }

  ti = clock();
  pthread_attr_init(&attr);
  pthread_create(&t1, &attr, quicksortThread, (void *)(vtr));
  pthread_join(t1, NULL);
  tf = clock();

  tt = (tf - ti);

  printf("Quicksort com Threads.\n");
  printf("Clocks gastos: %u\n", tt);
  printf("Tempo gastto:  %.2fs\n", tt / (float)(CLOCKS_PER_SEC));

  // LIBERANDO ESPAÇO DA MEMÓRIA E FINALIZANDO PROGRAMA
  free(lista);
  return 0;
}
