#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions/LeDisciEPreReqsParaMemoria.c"
#include "Functions/LeAlunosParaMemoria.c"

int main(){
	int q; 
    DiscAndReqs * discAndReqs;
    Alunos * alunos;
	discAndReqs = carregaDiscAndReqs();
	alunos = carregaAlunos();
	
	do {
		fflush(stdin);
		printf(" Opcao \n");
		printf("1. Cadastro de Alunos \n");
		printf("2. Consulta de Disciplinas \n");
		printf("4. Sair \n");
		scanf ("%d",&q);
		
		if (q == 1){ //Cadastro de Alunos
			return 1;
		} else if (q==2){ // Consutar Disciplinas
			return 2;
		}
	} while (q!=4);

	return 0;
}
