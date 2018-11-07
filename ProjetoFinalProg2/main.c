#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tableDisci "Tables/Disciplinas.txt"
#define tableAlunos "Tables/Alunos.txt"
#define tablePrereq "Tables/Prerequisitos.txt"
#define tableAlunosDisciplinas "Tables/AlunosDisciplinas.txt"

#define qtdDisciplinas 42
#define qtdPrereqs 47

///////////////////////////////////////////////////
typedef struct Disciplina{
	char sigla[6];
	char nome[100];
	int credito;
}Disciplina;

Disciplina * newDisciplina(char * sigla, char * nome, int credito){
    Disciplina * aux = (Disciplina *)malloc(sizeof(Disciplina));
    strcpy(aux->sigla,sigla);
    strcpy(aux->nome,nome);
    aux->credito = credito;
    return aux;
}

typedef struct Prerequisito{
	char siglaMateria[6];
	char siglaRequisito[6];
}Prerequisito;

Prerequisito * newPrerequisito(char * siglaMateria, char * siglaRequisito){
    Prerequisito * aux = (Prerequisito *)malloc(sizeof(Prerequisito));
    strcpy(aux->siglaMateria,siglaMateria);
    strcpy(aux->siglaRequisito,siglaRequisito);
    
    return aux;
}

typedef struct DiscAndReqs{
	Disciplina * disciplinas[qtdDisciplinas];//conferir quantidade de disciplinas
	Prerequisito * prerequisitos[qtdPrereqs];//conferir a quantidade de prerequisitos
	int totalDisci, totalPrereq;
}DiscAndReqs;

typedef struct AlunoLogado{
	char senha[255], usuario[255];
	int ra;
}AlunoLogado;

AlunoLogado *newAlunoLogado(char *usuario, char *senha, int ra){
	AlunoLogado * aux = (AlunoLogado *)malloc(sizeof(AlunoLogado));
	aux->ra = ra;
    strcpy(aux->usuario,usuario);
    strcpy(aux->senha,senha);
    return aux;
}
typedef struct AlunosDisciplina{
	int ra;
	char sigla[6];
	int semestre;
	int nota;
	int faltas;
}AlunosDisciplina;

AlunosDisciplina *newAlunosDisciplina(int ra, char *sigla, int sem, int nota, int faltas){
    AlunosDisciplina * aux = (AlunosDisciplina *)malloc(sizeof(AlunosDisciplina));
    aux->ra = ra;
    strcpy(aux->sigla, sigla);
    aux->semestre = sem;
    aux->nota = nota;
    aux->faltas = faltas;
    return aux;
}

typedef struct AllAlunosDisc{
	AlunosDisciplina *alunosDisciplinas[100];
	int total;
}AllAlunosDisc;

typedef struct Sigla{
	char sigla[6];
}Sigla;

Sigla *newSigla(char *sigla){
    Sigla * aux = (Sigla *)malloc(sizeof(Sigla));
    strcpy(aux->sigla, sigla);
    return aux;
}

typedef struct Prereqs{
	Sigla *reqs[5];
	int qtdReqs;
}Prereqs;

////////////////////////////////////////////////////

#include "Functions/LeDisciEPreReqsParaMemoria.c"
#include "Functions/LeAlunosParaMemoria.c"
#include "Functions/Alunos.c"
#include "Functions/Prerequisitos.c"
#include "Functions/Disciplinas.c"

void CadastroDeAlunos(Alunos *alunos);
void ConsultarDisciplinas(DiscAndReqs *discAndReqs);
void RealizarMatricula(DiscAndReqs *discAndReqs, AlunoLogado *alunoLogado, AllAlunosDisc *allAlunosDisc);

int main(){
	int q;
	char senha[255], usuario[255]; 
	AlunoLogado *alunoLogado = newAlunoLogado("0", "", 0);
	
    DiscAndReqs *discAndReqs = carregaDiscAndReqs();
    Alunos *alunos = carregaAlunos();
    AllAlunosDisc *allAlunosDisc = carregaAllAlunosDisc();
	
	do{
		printf("Usuario: ");
		fgets(usuario, 250, stdin);
		strtok(usuario, "\n");
		printf("Senha: ");
		fgets(senha, 250, stdin);
		strtok(senha, "\n");
	
		alunoLogado = validaLoginAluno(usuario, senha, alunoLogado);
	}while(strcmp(alunoLogado->usuario, "0")==0);
	
	if(strcmp(alunoLogado->usuario, "0")!=0){	
		do {
			fflush(stdin);
			printf(" Opcao \n");
			printf("1. Cadastro de Alunos \n");
			printf("2. Consulta de Disciplinas \n");
			printf("3. Realizar matricula \n");
			printf("4. Sair \n");
			scanf ("%d",&q);
			
			if (q == 1){ //Cadastro de Alunos
				CadastroDeAlunos(alunos);
			} else if (q==2){ // Consutar Disciplinas
				ConsultarDisciplinas(discAndReqs);
			} else if (q==3){
				RealizarMatricula(discAndReqs, alunoLogado, allAlunosDisc);
			}
		} 
		while (q!=4);
	}
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

void RealizarMatricula(DiscAndReqs *discAndReqs, AlunoLogado *alunoLogado, AllAlunosDisc *allAlunosDisc){
	Disciplina *disciplinaFinal, *disciplinasParaValidar[16], *disciplinasParaSalvar[16], *disciplinasSalvas[16], *disciplinasNaoSalvas[16];
	char discDigitada[6];
	int c = 0, cToSave = 0, cToNoSave = 0, veSeCumpriuReqs = 0, semestreOk = 0, semestreAtual, semestre, somaCreditos = 0;
	
	printf("Para sair, digite XX000\n");
	
	semestreAtual = verificaUltimoSemestreRegistrado(alunoLogado->ra, allAlunosDisc);
	do{
		//printf("Semestre Atual: %d\n", semestreAtual);
		printf("Digite o semestre: ");
		scanf("%d", &semestre);
		if(semestre <= semestreAtual){
			printf("\n\nO SEMESTRE DIGITADO NAO CONDIZ COM O SEMESTRE MAIS ATUAL REGISTRADO NA BASE!\n");
		}else{
			semestreOk = 1;
		}
	}while(semestreOk == 0);
	   
	do{
		disciplinaFinal = newDisciplina("", "", 0); //começa vazia para ser preenchida depois
		printf("Digite a disciplina: ");
		scanf("%s", &discDigitada);
		
		if(strcmp(discDigitada, "XX000") != 0){
			//VERIFICA PRIMEIRO SE A DISCIPLINA DIGITADA REALMENTE EXISTE
			disciplinaFinal = BuscaMateriaPelaSigla(discDigitada, discAndReqs, disciplinaFinal);
			if(disciplinaFinal->credito > 0){
				disciplinasParaValidar[c] = newDisciplina(disciplinaFinal->sigla, disciplinaFinal->nome, disciplinaFinal->credito);
				somaCreditos += disciplinaFinal->credito;
				c++;
			}else{
				printf("\n\nA DISCIPLINA DIGITADA NAO EXISTE!\n");
			}	
		}
	}while(strcmp(discDigitada, "XX000") != 0);
	
	if(somaCreditos > 32){
		printf("\n\nA SOMA DOS CREDITOS DAS MATERIAS DIGITADAS E SUPERIOR A 32, NENHUMA MATERIA FOI SALVA!\n");
	}else{
		printf("\n\n");
		for(int t=0;t<c;t++){
			//APROVEITA O LOOP PARA JA VERIFICAR OS REQUISITOS DAS MATERIAS
			//printf("parou aqui, quantidade de reqs: \n");
			Prereqs *requisitos = buscaPrerequisitosPorSigla(disciplinasParaValidar[t]->sigla, discAndReqs);
			//valida se a materia ja foi cursada anteriormente
			int validaJaFeita = buscaSeJaCursouDisciplina(disciplinasParaValidar[t]->sigla, allAlunosDisc, alunoLogado->ra);
			
			if(validaJaFeita == 0){
				if(requisitos->qtdReqs == 0){
					disciplinasParaSalvar[cToSave] = newDisciplina(disciplinasParaValidar[t]->sigla, disciplinasParaValidar[t]->nome, disciplinasParaValidar[t]->credito);
					printf("* Salvando Matricula na Disciplina %s.\n", disciplinasParaSalvar[cToSave]->sigla);
					cToSave++;
				}else if(requisitos->qtdReqs > 0){
					veSeCumpriuReqs = verificaSeAlunoCumpriuRequisitosPorSigla(alunoLogado ,requisitos, allAlunosDisc); 
					//printf("\n-Cumpriu: %d\n", veSeCumpriuReqs);
					
					if(veSeCumpriuReqs == 1){
						disciplinasParaSalvar[cToSave] = newDisciplina(disciplinasParaValidar[t]->sigla, disciplinasParaValidar[t]->nome, disciplinasParaValidar[t]->credito);
						printf("* Salvando Matricula na Disciplina %s.\n", disciplinasParaSalvar[cToSave]->sigla);
						cToSave++;
					}else{
						disciplinasNaoSalvas[cToNoSave] = newDisciplina(disciplinasParaValidar[t]->sigla, disciplinasParaValidar[t]->nome, disciplinasParaValidar[t]->credito);
						printf("* Erro -> Voce nao possui 1 ou mais do requisitos da %s concluidos.\n", disciplinasNaoSalvas[cToNoSave]->sigla);
						cToNoSave++;
					}
				}
			}else{
				disciplinasNaoSalvas[cToNoSave] = newDisciplina(disciplinasParaValidar[t]->sigla, disciplinasParaValidar[t]->nome, disciplinasParaValidar[t]->credito);
				printf("* Erro -> Voce ja cursou essa Disciplina.\n", disciplinasNaoSalvas[cToNoSave]->sigla);
				cToNoSave++;
			}
		}
	}
	
	for(int h=0;h<cToSave;h++){
		allAlunosDisc->alunosDisciplinas[allAlunosDisc->total] = newAlunosDisciplina(alunoLogado->ra, disciplinasParaSalvar[h]->sigla, semestre, 0, 0);
		allAlunosDisc->total++;
	}
	/*
	for(int u=0;u<allAlunosDisc->total;u++){
		printf("[%s]", allAlunosDisc->alunosDisciplinas[u]->sigla);
	}*/
	
	
	if(cToSave >= 1){
		efetuaMatricula(allAlunosDisc);
	}else{
		printf("\n\nNENHUMA MATERIA FOI SALVA.\n");
	}
	
}








