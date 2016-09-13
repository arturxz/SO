#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
** CONSELHO: COMPILAR COM O SEGUINTE COMANDO:
** gcc ...
**
*/

#define QUANTIDADE 1000000

int cnt = 0;

// TRAZ PRA LOCAL, ITERA QUANTIDADE vezes E RETORNA PRA GLOBAL
void *contador(void *a){
    int i, tmp;
    for(i = 0; i < QUANTIDADE; i++){
        tmp = cnt;
        tmp = tmp + 1;
        cnt = tmp;
    }
    return a;
}

int main(){
    pthread_t tid1, tid2;

    // CRIANDO THREADS
    if(pthread_create(&tid1, NULL, contador, NULL)){
      perror("ERRO CRIANDO THREAD 1\n");
      exit(1);
    }

    if(pthread_create(&tid2, NULL, contador, NULL)){
      perror("ERRO CRIANDO THREAD 2\n");
      exit(1);
    }

    // EXECUTANDO AS THREADS E ESPERANDO-AS TERMINAR
    if(pthread_join(tid1, NULL)){
      printf("\n ERRO ESPERANDO THREAD 1");
      exit(1);
    }
    if(pthread_join(tid2, NULL)){
      printf("\n ERRO ESPERANDO THREAD 2");
      exit(1);
    }

    printf("CNT: [%d]\n", cnt);

    pthread_exit(NULL);
    return 0;
}
