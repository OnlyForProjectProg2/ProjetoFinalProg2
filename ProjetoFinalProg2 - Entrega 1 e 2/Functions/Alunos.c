void gravaAlunosArquivo(Alunos *alunos){
    FILE *fp = fopen(tableAlunos, "w");
    fprintf(fp,"%d\n",alunos->totalAlunos);
    
    for(int c=0;c<alunos->totalAlunos;c++){
    	fprintf(fp,"%d\n",alunos->alunos[c]->ra);
    	fprintf(fp,"%s\n",alunos->alunos[c]->nome);
    	fprintf(fp,"%s\n",alunos->alunos[c]->usuario);
    	fprintf(fp,"%s\n",alunos->alunos[c]->senha);
	}
	fclose(fp);
	printf("\n\nSALVO COM SUCESSO!\n\n");
}

AlunoLogado *validaLoginAluno(char *usuario, char *senha, AlunoLogado *alunoLogado){
    FILE *fp = fopen(tableAlunos, "r");
    int top, raBD;
    char nomeBD[255], usuarioBD[255], senhaBD[255];
	fscanf(fp,"%d\n",&top);
	
	for(int v=0;v<top;v++){
    	fscanf(fp,"%d\n",&raBD);
    	fscanf(fp,"%[^\n]",nomeBD);
    	fscanf(fp,"%s\n",usuarioBD);
    	fscanf(fp,"%s\n",senhaBD);
    	
    	if(strcmp(usuario, usuarioBD) == 0 && strcmp(senha, senhaBD) == 0){
    		alunoLogado->ra = raBD;
			strcpy(alunoLogado->usuario, usuarioBD);
			strcpy(alunoLogado->senha, senhaBD);
			strcpy(alunoLogado->nome, nomeBD);
		}
    	//printf("[%d, %s, %s, %s]\n", raBD, nomeBD, usuarioBD, senhaBD);
	}
	
	if(strcmp(alunoLogado->usuario, "0")!=0){
		printf("\n\nLOGIN EFETUADO\n\n");
	}else{
		printf("\n\nUSUARIO OU SENHA INCORRETOS\n\n");
	}
	
	fclose(fp);
	return alunoLogado;	
}

float obtemCrAluno(AlunoLogado *alunoLogado, AllAlunosDisc *allAlunosDisc, DiscAndReqs *discAndReqs){
	float somaNotaECred = 0, somaCred = 0;
	Disciplina *disciplinaFinal = newDisciplina("", "", 0);
	
	for(int j=0; j<allAlunosDisc->total; j++){
		if(alunoLogado->ra == allAlunosDisc->alunosDisciplinas[j]->ra){
			//printf("%s\n", allAlunosDisc->alunosDisciplinas[j]->sigla);
			disciplinaFinal = BuscaMateriaPelaSigla(allAlunosDisc->alunosDisciplinas[j]->sigla, discAndReqs, disciplinaFinal);
			somaNotaECred = (disciplinaFinal->credito * allAlunosDisc->alunosDisciplinas[j]->nota) + somaNotaECred;
			somaCred += disciplinaFinal->credito;
		}
	}
	
	float cr = somaNotaECred/somaCred;
	
	//printf("passou cr\n");
	return cr/10;
}

int obtemPosTurma(AlunoLogado *alunoLogado, AllAlunosDisc *allAlunosDisc, DiscAndReqs *discAndReqs, Alunos *alunos, AllCrAlunos * allCrAlunos, Disciplina * disciplinaFinal){
	//printf("inicia pos\n");
	float somaNotaECred = 0, somaCred = 0;
	int g, j;
	
	//printf("inicia loops\n");
	for(g=0; g<alunos->totalAlunos; g++){
		for(j=0; j<allAlunosDisc->total; j++){
			//printf("%d, %d\n", alunos->alunos[g]->ra, allAlunosDisc->alunosDisciplinas[j]->ra);
			if(alunos->alunos[g]->ra == allAlunosDisc->alunosDisciplinas[j]->ra){
				disciplinaFinal = BuscaMateriaPelaSigla(allAlunosDisc->alunosDisciplinas[j]->sigla, discAndReqs, disciplinaFinal);
				somaNotaECred = (disciplinaFinal->credito * allAlunosDisc->alunosDisciplinas[j]->nota) + somaNotaECred;
				somaCred += disciplinaFinal->credito;
				//printf("ok");
			}
		}
		allCrAlunos->crAlunos[g]->ra = alunos->alunos[g]->ra;
		if((somaNotaECred/somaCred) > 0){
			allCrAlunos->crAlunos[g]->cr = somaNotaECred/somaCred;
			somaNotaECred = 0;
			somaCred = 0;
		}
		//printf("[%f, %d]\n", allCrAlunos->crAlunos[g]->cr, allCrAlunos->crAlunos[g]->ra);
	}

  	int  l, p; 
	CrAluno *aux; 
	  for( l = 0; l < allCrAlunos->total; l++ ){
	    for( p = l + 1; p < allCrAlunos->total; p++ ){
	      if ( allCrAlunos->crAlunos[p]->cr > allCrAlunos->crAlunos[l]->cr ){
	         aux = allCrAlunos->crAlunos[p];
	         allCrAlunos->crAlunos[p] = allCrAlunos->crAlunos[l];
	         allCrAlunos->crAlunos[l] = aux;
	      }
	    }
	  }
  	
	int pos = 1;
	for(int t=0; t<allCrAlunos->total; t++){
		//printf("[%d, %.2f]\n", allCrAlunos->crAlunos[t]->ra, allCrAlunos->crAlunos[t]->cr);
		if(allCrAlunos->crAlunos[t]->ra != alunoLogado->ra){
			pos++;
		}else if(allCrAlunos->crAlunos[t]->ra == alunoLogado->ra){
			break;
		}
	}
	
	return pos;
}

