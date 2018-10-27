typedef struct AlunoLogado{
	char senha[255], usuario[255];
}AlunoLogado;

AlunoLogado *newAlunoLogado(char *usuario, char *senha){
	AlunoLogado * aux = (AlunoLogado *)malloc(sizeof(AlunoLogado));
    strcpy(aux->usuario,usuario);
    strcpy(aux->senha,senha);
    return aux;
}

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
	printf("\n\nSalvo com sucesso!\n\n");
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
			strcpy(alunoLogado->usuario, usuario);
			strcpy(alunoLogado->senha, senha);
		}
    	//printf("[%d, %s, %s, %s]\n", raBD, nomeBD, usuarioBD, senhaBD);
	}
	
	if(strcmp(alunoLogado->usuario, "0")!=0){
		printf("\n\nLOGIN EFETUADO\n\n");
	}else{
		printf("\n\nUSUARIO OU SENHA INCORRETOS\n\n");
	}
	
	return alunoLogado;	
}
