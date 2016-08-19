#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	/*INICIANDO CONTROLADORES DE PROCESSO E PIPE*/
	int fd1[2], fd2[2];
	pid_t pid, ret;
		
	/* INICIALIZANDO PRIMEIRO PIPE, PARA INTRODUÇÃO DE DADOS NO PROCESSO FILHO*/
	if( pipe(fd1) < 0 ){
		perror("PIPE 1");
		return -1;
	}

	/* INICIALIZANDO SEGUNDO PIPE, PARA RETORNO DO RESULTADO NO PROCESSO PAI*/
		if( pipe(fd2) < 0){
			perror("PIPE 2");
			return -1;
		}
	
	/*CRIANDO PROCESSO FILHO*/
	if( (pid = fork()) < 0 ){
		perror("FORK");
		return -1;
	}
	
	/* CODIGO QUE SERÁ EXECUTADO EXCLUSIVAMENTE NO PROCESSO PAI */
	if(pid > 0){
		close(fd1[0]);
		int arg[1] = {5};
		
		printf("PID Pai: %d\n", (int )getpid());
		printf("Numero a calcular: %d\n", arg[0]);

		write(fd1[1], arg, sizeof(int *));

		/*ESPERANDO QUE O PROCESSO FILHO FINALIZE COM SUCESSO*/
		ret = waitpid(pid, NULL, 0);
		if(ret == pid){
			/*FECHANDO CANAL DE ESCRITA DO PIPE E LENDO OS RESULTADOS DO PROCESSAMENTO REALIZADO NO FILHO*/
			int ret[1] = {0};

			close(fd2[1]);
			read(fd2[0], ret, sizeof(int *));

			printf("Resultado: %d\n", ret[0]);
		} else{
			printf("Erro na espera do processo filho.\n");
		}

	} else if (pid == 0){
		/*CODIGO QUE SERÁ EXECUTADO SOMENTE NO PROCESSO FILHO*/
		printf("PID Filho: %d\n", (int )getpid());

		/*FECHANDO CANAL DE ESCRITA E LENDO CONTEÚDO NO PIPE*/
		int op[1], fat[1] = {1};
		close(fd1[1]);
		read(fd1[0], op, sizeof(int *));

		for(int i=1; i <= op[0]; i++){
			fat[0] = fat[0] * i;
		}

		/*FECHANDO CANAL DE LEITURA DO PIPE E ESCREVENDO NELE*/
		close(fd2[0]);
		write(fd2[1], fat, sizeof(int *));
		exit(0);
	}

	return 0;
}
