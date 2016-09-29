#include <stdio.h>
#include <unistd.h>
#include <syscall.h>

int main(void){
		
	// USANDO FUNÇÃO DO ESPAÇO DO USUÁRIO
	printf("No espaço do usuário:\n%i\n", getpid());
	
	// USANDO FUNÇÃO DO SISTEMA (KERNEL). 39 REFERENCIA A CHAMADA DO GETPID NO KERNEL
	printf("No espaço do usuário:\n%li\n", syscall(39));

	return 0;
}
