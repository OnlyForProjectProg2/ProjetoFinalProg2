#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tableDisci "Tables/Disciplinas.txt"
#define tableAlunos "Tables/Alunos.txt"
#define tablePrereq "Tables/Prerequisitos.txt"

#include "Functions/LeDisciEPreReqsParaMemoria.c"
#include "Functions/LeAlunosParaMemoria.c"
#include "Functions/Alunos.c"
#include "Functions/Disciplinas.c"

void CadastroDeAlunos(Alunos *alunos);
void ConsultarDisciplinas();

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
			ConsultarDisciplinas(discAndReqs);
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
	printf("Digite o Nome do aluno: ");
	fgets(nome, 250, stdin);
	strtok(nome, "\n");
	printf("Digite o Login: ");
	fgets(usuario, 250, stdin);
	strtok(usuario, "\n");
	printf("Digite a Senha: ");
	fgets(senha, 250, stdin);
	strtok(senha, "\n");
	
   	alunos->alunos[alunos->totalAlunos] = newAluno(ra, nome, usuario, senha);
    alunos->totalAlunos++;
	
	gravaAlunosArquivo(alunos);
}

void ConsultarDisciplinas(DiscAndReqs *discAndReqs){
	int c = 0, avaliador=0;
	char disciplina[5];
	printf("Digite a disciplina: ");
	scanf("%s", &disciplina);
	
	Disciplina *disciplinaFinal = newDisciplina("", "", 0);//começa vazia para ser preenchida depois
	
	disciplinaFinal = BuscaMateriaPelaSigla(disciplina, discAndReqs, disciplinaFinal);
	
	if(disciplinaFinal->credito > 0){
		printf("\n\nNome: %s\n", disciplinaFinal->nome);
		printf("Quantidade de Creditos: %d\n", disciplinaFinal->credito);
		printf("Pre-requisitos:\n");
		while(c<qtdPrereqs){
			if(strcmp(disciplina, discAndReqs->prerequisitos[c]->siglaMateria) == 0){
				for(int a=0;a<discAndReqs->totalDisci;a++){
					if(strcmp(discAndReqs->prerequisitos[c]->siglaRequisito, discAndReqs->disciplinas[a]->sigla) == 0){
						printf("\t%s - %s\n", discAndReqs->prerequisitos[c]->siglaRequisito, discAndReqs->disciplinas[a]->nome);
						avaliador++;
					}
				}
			}
			c++;
		}
		printf("\n\n");	
	}else{
		printf("\n\nDISCIPLINA DIGITADA INVALIDA.\n\n");
	}
}










