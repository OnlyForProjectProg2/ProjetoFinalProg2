#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Functions/LeDisciEPreReqsParaMemoria.c"
#include "Functions/LeAlunosParaMemoria.c"
#include "Functions/OperacoesAlunosEmArquivo.c"

void CadastroDeAlunos();

int main(){
	int q; 
    DiscAndReqs *discAndReqs;
    Alunos *alunos;
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
			CadastroDeAlunos(alunos);
		} else if (q==2){ // Consutar Disciplinas
			return 2;
		}
	} while (q!=4);

	return 0;
}

void CadastroDeAlunos(Alunos *alunos){
	int ra;
	char nome[255], usuario[255], senha[255];
	printf("Cadastro de Alunos.\n");
	printf("\nDigite o RA do aluno: ");
	scanf("%d",&ra);getchar();
	printf("\nDigite o Nome do aluno: ");
	fgets(nome, 250, stdin);
	strtok(nome, "\n");
	printf("\nDigite o Login: ");
	fgets(usuario, 250, stdin);
	strtok(usuario, "\n");
	printf("\nDigite a Senha: ");
	fgets(senha, 250, stdin);
	strtok(senha, "\n");
	
   	alunos->alunos[alunos->totalAlunos] = newAluno(ra, nome, usuario, senha);
    alunos->totalAlunos++;
	
	//gravaAlunosArquivo(alunos); Implementar no arquivo de funções de alunos
}













