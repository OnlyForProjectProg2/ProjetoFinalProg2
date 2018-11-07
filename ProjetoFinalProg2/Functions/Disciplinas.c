Disciplina *BuscaMateriaPelaSigla(char disciplina[5], DiscAndReqs *discAndReqs, Disciplina *disciplinaFinal){
	char sigla[5], nome[100];
	int credito;
	int contador = 0;
	FILE *fp = fopen(tableDisci, "r");
	
    while(contador<discAndReqs->totalDisci){
		fscanf(fp,"%s\n",sigla);
		fscanf(fp,"%[^\n]",nome);
		fscanf(fp,"%d\n",&credito);
		if(strcmp(disciplina, sigla) == 0){
			strcpy(disciplinaFinal->sigla,sigla);
			strcpy(disciplinaFinal->nome,nome);
			disciplinaFinal->credito = credito;
			
			return disciplinaFinal;
			break;
		}
		
        contador++;
    }
	
	fclose(fp);
	return disciplinaFinal;
}

AllAlunosDisc *buscaMatriculasRegistradas(int ra, char *discDigitada, int semestre){
    AllAlunosDisc * all = (AllAlunosDisc *)malloc(sizeof(AllAlunosDisc));
	int raF, semestreF, notaF, faltasF;
	char siglaF[6];
	int top;
	
	FILE *fp = fopen(tableAlunosDisciplinas, "r");
	fscanf(fp, "%d\n", &all->total);
	
	for(int tmp=0;tmp<all->total;tmp++){
		fscanf(fp, "%d[^,]", &raF);
		fscanf(fp, ",%[^,]", siglaF);
		fscanf(fp, ",%d", &semestreF);
		fscanf(fp, ",%d", &notaF);
		fscanf(fp, ",%d\n", &faltasF);
		
		all->alunosDisciplinas[tmp] = newAlunosDisciplina(raF, siglaF, semestreF, notaF, faltasF);
	}
	
	all->alunosDisciplinas[all->total] = newAlunosDisciplina(ra, discDigitada, semestre, 0, 0);
	
	fclose(fp);
	return all;
}

void registraMatriculasAtualizadas(AllAlunosDisc *alll){
    FILE *fp = fopen(tableAlunosDisciplinas, "w");
    fprintf(fp,"%d\n",alll->total+1);
    
    for(int c=0;c<=alll->total;c++){
    	//printf("%d\n%s\n%d\n%d\n%d\n",alll->alunosDisciplinas[c]->ra, alll->alunosDisciplinas[c]->sigla, alll->alunosDisciplinas[c]->semestre, alll->alunosDisciplinas[c]->nota, alll->alunosDisciplinas[c]->faltas);
    	fprintf(fp,"%d,%s,%d,%d,%d\n",alll->alunosDisciplinas[c]->ra, alll->alunosDisciplinas[c]->sigla, alll->alunosDisciplinas[c]->semestre, alll->alunosDisciplinas[c]->nota, alll->alunosDisciplinas[c]->faltas);
	}
	fclose(fp);
	printf("\n\nSalvo com sucesso!\n\n");
}

AllAlunosDisc * carregaAllAlunosDisc(){
    AllAlunosDisc * allAlunosDisc = (AllAlunosDisc *)malloc(sizeof(AllAlunosDisc));    
    int ra, semestre, nota, faltas, contador=0;
	char sigla[6];
	
	FILE *fp = fopen(tableAlunosDisciplinas, "r");
	fscanf(fp,"%d\n",&allAlunosDisc->total);
	//printf("Total: %d\n", allAlunosDisc->total);
    while(contador<allAlunosDisc->total){
		fscanf(fp,"%d,%[^,],%d,%d,%d\n", &ra, sigla, &semestre, &nota, &faltas);
       	allAlunosDisc->alunosDisciplinas[contador] = newAlunosDisciplina(ra, sigla, semestre, nota, faltas);
        
        //printf("[%d, %s, %d, %d, %d]\n", ra, sigla, semestre, nota, faltas);
        contador++;
    }
    fclose(fp); 
    
    return allAlunosDisc;
}

int verificaUltimoSemestreRegistrado(int raAluno, AllAlunosDisc *allAlunosDisc){
	int semestreAtual = 0;
	
	for(int c=0;c<allAlunosDisc->total;c++){
		if(allAlunosDisc->alunosDisciplinas[c]->ra == raAluno){
			//printf("RA da memoria atual: %d, RA do aluno: %d\n", allAlunosDisc->alunosDisciplinas[c]->ra, raAluno);
			if(allAlunosDisc->alunosDisciplinas[c]->semestre > semestreAtual){
				//printf("Semestre memoria atual: %d, semestreAtualLocal: %d\n", allAlunosDisc->alunosDisciplinas[c]->semestre, semestreAtual);
				semestreAtual = allAlunosDisc->alunosDisciplinas[c]->semestre;
			}
		}
	}
	
	return semestreAtual;	
}

int verificaSeAlunoCumpriuRequisitosPorSigla(AlunoLogado *alunoLogado, Prereqs *requisitos, AllAlunosDisc *allAlunosDisc){
    int validador=0;
	
	for(int csemp=0;csemp<requisitos->qtdReqs;csemp++){
		//printf("Requisito[%d] = %s\n", csemp, requisitos->reqs[csemp]->sigla);
		for(int c=0;c<allAlunosDisc->total;c++){
			//printf("%d\n",c);
			if(allAlunosDisc->alunosDisciplinas[c]->ra == alunoLogado->ra && strcmp(allAlunosDisc->alunosDisciplinas[c]->sigla, requisitos->reqs[csemp]->sigla) == 0){
				//printf("Req[%d] = Nota: %d, Falta: %d\n", csemp, allAlunosDisc->alunosDisciplinas[c]->nota, allAlunosDisc->alunosDisciplinas[c]->faltas);
				if(allAlunosDisc->alunosDisciplinas[c]->nota >= 5 && allAlunosDisc->alunosDisciplinas[c]->faltas < 25){
					validador++;
					//printf("SIM\n");
				}//else{
					//printf("NAO\n");
				//}
			}
		}
	}
	
	if(validador == requisitos->qtdReqs){
		return 1;
	}else{
		return 0;
	}
}

void efetuaMatricula(AllAlunosDisc *allAlunosDisc){
    FILE *fp = fopen(tableAlunosDisciplinas, "w");
    fprintf(fp,"%d\n", allAlunosDisc->total);
    
	for(int u=0;u<allAlunosDisc->total;u++){
		fprintf(fp,"%d,%s,%d,%d,%d\n", allAlunosDisc->alunosDisciplinas[u]->ra, allAlunosDisc->alunosDisciplinas[u]->sigla, allAlunosDisc->alunosDisciplinas[u]->semestre, 0, 0);
	}
	fclose(fp);
	printf("\n\nMATRICULA REALIZADA COM SUCESSO\n");
	
}
