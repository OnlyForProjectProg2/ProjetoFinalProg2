typedef struct AlunosDisciplina{
	int ra;
	char sigla[6];
	int semestre;
	int nota;
	int faltas;
}AlunosDisciplina;

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
	
	return disciplinaFinal;
}
