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
	char senha[255], usuario[255], nome[255];
	int ra;
}AlunoLogado;

AlunoLogado *newAlunoLogado(char *usuario, char *senha, int ra, char *nome){
	AlunoLogado * aux = (AlunoLogado *)malloc(sizeof(AlunoLogado));
	aux->ra = ra;
    strcpy(aux->usuario,usuario);
    strcpy(aux->senha,senha);
    strcpy(aux->nome,nome);
    return aux;
}
typedef struct AlunosDisciplina{
	int ra;
	char sigla[6];
	int semestre;
	float nota;
	float faltas;
}AlunosDisciplina;

AlunosDisciplina *newAlunosDisciplina(int ra, char *sigla, int sem, float nota, float faltas){
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

typedef struct CrAluno{
	int ra;
	float cr;
}CrAluno;

CrAluno *newCrAluno(int ra, float cr){
    CrAluno * aux = (CrAluno *)malloc(sizeof(CrAluno));
    aux->ra = ra;
    aux->cr = cr;
    return aux;
}

typedef struct AllCrAlunos{
	CrAluno *crAlunos[100];
	int total;
}AllCrAlunos;

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
#include "Functions/Disciplinas.c"
#include "Functions/Alunos.c"
#include "Functions/Prerequisitos.c"

void CadastroDeAlunos(Alunos *alunos);
void ConsultarDisciplinas(DiscAndReqs *discAndReqs);
void RealizarMatricula(DiscAndReqs *discAndReqs, AlunoLogado *alunoLogado, AllAlunosDisc *allAlunosDisc);
void AtualizaNotaFalta(AlunoLogado *alunoLogado, AllAlunosDisc *allAlunosDisc, DiscAndReqs *discAndReqs);
void GeraHistorico(AlunoLogado *alunoLogado, AllAlunosDisc *allAlunosDisc, DiscAndReqs *discAndReqs, Alunos *alunos);

int main(){
	int q;
	char senha[255], usuario[255]; 
	AlunoLogado *alunoLogado = newAlunoLogado("0", "", 0, "");
	
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
			printf("4. Atualizar Nota e Falta \n");
			printf("5. Consultar Historico do Aluno \n");
			printf("6. Sair \n");
			scanf ("%d",&q);
			
			if (q == 1){ //Cadastro de Alunos
				CadastroDeAlunos(alunos);
			} else if (q==2){ // Consutar Disciplinas
				ConsultarDisciplinas(discAndReqs);
			} else if (q==3){
				RealizarMatricula(discAndReqs, alunoLogado, allAlunosDisc);
			}else if (q==4){
				AtualizaNotaFalta(alunoLogado, allAlunosDisc, discAndReqs);
			}else if (q==5){
				GeraHistorico(alunoLogado, allAlunosDisc, discAndReqs, alunos);
			}
		} 
		while (q!=6);
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
	printf("DIGITE A DISCIPLINA: ");
	scanf("%s", &disciplina);
	
	Disciplina *disciplinaFinal = newDisciplina("", "", 0);//come�a vazia para ser preenchida depois
	
	disciplinaFinal = BuscaMateriaPelaSigla(disciplina, discAndReqs, disciplinaFinal);
	
	if(disciplinaFinal->credito > 0){
		printf("\n\nNOME: %s\n", disciplinaFinal->nome);
		printf("QUANTIDADE DE CREDITOS: %d\n", disciplinaFinal->credito);
		printf("PRE-REQUISITOS:\n");
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
		if(avaliador == 0){ printf("\t ESSA MATERIA NAO POSSUI PRE-REQUISITOS.");	}
		printf("\n\n");	
	}else{
		printf("\n\nDISCIPLINA DIGITADA INVALIDA.\n\n");
	}
}

void RealizarMatricula(DiscAndReqs *discAndReqs, AlunoLogado *alunoLogado, AllAlunosDisc *allAlunosDisc){
	Disciplina *disciplinaFinal, *disciplinasParaValidar[16], *disciplinasParaSalvar[16], *disciplinasSalvas[16], *disciplinasNaoSalvas[16];
	char discDigitada[6];
	int c = 0, cToSave = 0, cToNoSave = 0, veSeCumpriuReqs = 0, semestreOk = 0, semestreAtual, semestre, somaCreditos = 0;
	
	printf("PARA SAIR, DIGITE XX000\n\n\n");
	
	semestreAtual = verificaUltimoSemestreRegistrado(alunoLogado->ra, allAlunosDisc);
	do{
		//printf("Semestre Atual: %d\n", semestreAtual);
		printf("DIGITE O SEMESTRE: ");
		scanf("%d", &semestre);
		
		if(semestre <= semestreAtual){
			printf("\n\nO SEMESTRE DIGITADO NAO CONDIZ COM O SEMESTRE MAIS ATUAL REGISTRADO NA BASE!\n\n");
		}else{
			semestreOk = 1;
		}
	}while(semestreOk == 0);
	   
	do{
		disciplinaFinal = newDisciplina("", "", 0); //come�a vazia para ser preenchida depois
		printf("DIGITE A DISCIPLINA: ");
		scanf("%s", &discDigitada);
		
		if(strcmp(discDigitada, "XX000") != 0){
			//VERIFICA PRIMEIRO SE A DISCIPLINA DIGITADA REALMENTE EXISTE
			disciplinaFinal = BuscaMateriaPelaSigla(discDigitada, discAndReqs, disciplinaFinal);
			if(disciplinaFinal->credito > 0){
				disciplinasParaValidar[c] = newDisciplina(disciplinaFinal->sigla, disciplinaFinal->nome, disciplinaFinal->credito);
				somaCreditos += disciplinaFinal->credito;
				c++;
			}else{
				printf("\n\nA DISCIPLINA DIGITADA NAO EXISTE!\n\n");
			}	
		}
	}while(strcmp(discDigitada, "XX000") != 0);
	
	if(somaCreditos > 32){
		printf("\n\nA SOMA DOS CREDITOS DAS MATERIAS DIGITADAS E SUPERIOR A 32, NENHUMA MATERIA FOI SALVA!\n\n");
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
					printf("* Salvando Matricula na Disciplina %s.\n\n", disciplinasParaSalvar[cToSave]->sigla);
					cToSave++;
				}else if(requisitos->qtdReqs > 0){
					veSeCumpriuReqs = verificaSeAlunoCumpriuRequisitosPorSigla(alunoLogado ,requisitos, allAlunosDisc); 
					//printf("\n-Cumpriu: %d\n", veSeCumpriuReqs);
					
					if(veSeCumpriuReqs == 1){
						disciplinasParaSalvar[cToSave] = newDisciplina(disciplinasParaValidar[t]->sigla, disciplinasParaValidar[t]->nome, disciplinasParaValidar[t]->credito);
						printf("* Salvando Matricula na Disciplina %s.\n\n", disciplinasParaSalvar[cToSave]->sigla);
						cToSave++;
					}else{
						disciplinasNaoSalvas[cToNoSave] = newDisciplina(disciplinasParaValidar[t]->sigla, disciplinasParaValidar[t]->nome, disciplinasParaValidar[t]->credito);
						printf("* Erro -> VOCE NAO POSSUI 1 OU MAIS REQUISITOS DA %s CONCLUIDOS, \n\tVERIFIQUE SUA NOTA E FALTA E TENTE NOVAMENTE.\n\n", disciplinasNaoSalvas[cToNoSave]->sigla);
						cToNoSave++;
					}
				}
			}else{
				disciplinasNaoSalvas[cToNoSave] = newDisciplina(disciplinasParaValidar[t]->sigla, disciplinasParaValidar[t]->nome, disciplinasParaValidar[t]->credito);
				printf("* Erro -> VOCE JA CURSOU ESSA DISCIPLINA.\n\n", disciplinasNaoSalvas[cToNoSave]->sigla);
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
		efetuaMatriculaOuAlteracao(allAlunosDisc);
	}else{
		printf("\n\nNENHUMA MATERIA FOI SALVA.\n\n");
	}
	
}

void AtualizaNotaFalta(AlunoLogado *alunoLogado, AllAlunosDisc *allAlunosDisc, DiscAndReqs *discAndReqs){
	int semestre;
	float nota, falta;
	char discDigitada[5];
	
	printf("DIGITE O SEMESTRE: ");
	scanf("%d", &semestre);
	
	int c = printaSituacaoNotasAluno(semestre, alunoLogado->ra, allAlunosDisc, discAndReqs);
	
	if(c > 0){
		do{
			printf("\nDIGITE O CODIGO DA DISCIPLINA PARA REALIZAR A ALTERACAO: ");
			scanf("%s", discDigitada);
			if(strcmp(discDigitada, "XX000") != 0){
				if((verificaDisciplinaExisteNoSemestre(semestre, discDigitada, allAlunosDisc)) == 1){
					printf("Nota: ");
					scanf("%f", &nota);
					printf("Falta (%): ");
					scanf("%f", &falta);
					
					if((nota >10 || nota <0) || (falta >100 || falta <0)){
						printf("\nNOTA E FALTA DEVEM SER DE 0 A 10 E 0 A 100, RESPECTIVAMENTE\n\n");
					}else{
						efetuaAlteracaoESalvaArquivo(semestre, discDigitada, allAlunosDisc, nota, falta, alunoLogado->ra);
						printaSituacaoNotasAluno(semestre, alunoLogado->ra, allAlunosDisc, discAndReqs);
							
					}	
				}else{
					printf("\nMATRICULA NAO ENCONTRADA NO SEMESTRE DIGITADO.\n\n");
				}
			}
		}while(strcmp(discDigitada, "XX000") != 0);
	}else{
		printf("NENHUMA MATRICULA ENCONTRADA NO SEMESTRE\n\n");
	}
}

void GeraHistorico(AlunoLogado *alunoLogado, AllAlunosDisc *allAlunosDisc, DiscAndReqs *discAndReqs, Alunos *alunos){
	float cr;
	int posTurma, maiorSem = 0, c;
	char discDigitada[5], motivo[40], nameFile[10];
	
	AllCrAlunos *allCrAlunos = (AllCrAlunos *)malloc(sizeof(AllCrAlunos));  
	Disciplina *disciplinaFinal = newDisciplina("", "", 0);;
	
	allCrAlunos->total = 0;
	for(int n=0;n<alunos->totalAlunos; n++){
		allCrAlunos->crAlunos[n] = newCrAluno(0, 0);
		allCrAlunos->total++;
		//printf("%d,\n",allCrAlunos->total);
	}
	
	cr = obtemCrAluno(alunoLogado, allAlunosDisc, discAndReqs);
	posTurma = obtemPosTurma(alunoLogado, allAlunosDisc, discAndReqs, alunos, allCrAlunos, disciplinaFinal);
	
	
	snprintf(nameFile, 10, "%d%s", alunoLogado->ra, ".txt");
	
	FILE *fp = fopen(nameFile, "w");
	fprintf(fp, "%s", "Faculdade de Tecnologia - UNICAMP\n\n");
	fprintf(fp, "%s", "Relatorio de Matricula\n\n");
	
	fprintf(fp, "%s: %s\n", "Nome Completo", alunoLogado->nome);
	fprintf(fp, "%s: %d\n", "RA", alunoLogado->ra);
	fprintf(fp, "%s: %.2f\n", "Coeficiente de Rendimento", cr);
	fprintf(fp, "%s: %d\n\n", "Classificacao do aluno na turma ", posTurma);
	
	for(c=0; c<allAlunosDisc->total; c++){
		if(alunoLogado->ra == allAlunosDisc->alunosDisciplinas[c]->ra){
			if(allAlunosDisc->alunosDisciplinas[c]->semestre > maiorSem){
				maiorSem = allAlunosDisc->alunosDisciplinas[c]->semestre;
			}
		}
	}
	
	fprintf(fp, "%s\n\n", "Disciplina\tNota\tFaltas\tSituacao");
	for(c=1; c<=maiorSem; c++){
		for(int h=0; h<allAlunosDisc->total; h++){
			if(alunoLogado->ra == allAlunosDisc->alunosDisciplinas[h]->ra && allAlunosDisc->alunosDisciplinas[h]->semestre == c){
				if(allAlunosDisc->alunosDisciplinas[h]->faltas<=25 && allAlunosDisc->alunosDisciplinas[h]->nota>5){
					strcpy(motivo, "Aprovado por Nota e Frequencia");
				}else if(allAlunosDisc->alunosDisciplinas[h]->faltas>25){
					strcpy(motivo, "Reprovado por Falta");
				}else if(allAlunosDisc->alunosDisciplinas[h]->nota<5){
					strcpy(motivo, "Reprovado por Nota");
				}
				
				fprintf(fp, "%s\t\t%.2f\t%.2f\t%s\n", allAlunosDisc->alunosDisciplinas[h]->sigla, allAlunosDisc->alunosDisciplinas[h]->nota, allAlunosDisc->alunosDisciplinas[h]->faltas, motivo);
			}
		}
	}
	
	printf("\n\n%s - FOI GERADO COM SUCESSO!\n\n", nameFile);
	fclose(fp);
}





