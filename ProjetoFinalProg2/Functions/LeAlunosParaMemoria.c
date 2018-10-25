typedef struct Aluno{
	int ra;
	char nome[255];
	char usuario[255];
	char senha[255];
}Aluno;

Aluno * newAluno(int ra, char * nome, char * usuario, char * senha){
    Aluno * aux = (Aluno *)malloc(sizeof(Aluno));
    aux->ra = ra;
    strcpy(aux->nome,nome);
    strcpy(aux->usuario,usuario);
    strcpy(aux->senha,senha);
    return aux;
}
typedef struct Alunos{
	Aluno * alunos[100];
	int totalAlunos;
}Alunos; 

Alunos * carregaAlunos(){
    Alunos * alunos = (Alunos *)malloc(sizeof(Alunos));    
	char usuario[255];
	char nome[255];
	char senha[255];
	int ra, contador = 0;
	
	FILE *fp = fopen(tableAlunos, "r");
	fscanf(fp,"%d\n",&alunos->totalAlunos);
    while(contador<qtdDisciplinas){
		fscanf(fp,"%d\n",&ra);
		fscanf(fp,"%[^\n]",nome);
		fscanf(fp,"%s\n",usuario);
		fscanf(fp,"%s\n",senha);
       	alunos->alunos[contador] = newAluno(ra, nome, usuario, senha);
        contador++;
    }
    fclose(fp); 
    
    return alunos;
}

