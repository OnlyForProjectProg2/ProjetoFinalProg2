typedef struct Sigla{
	char sigla[6];
}Sigla;

typedef struct Prereqs{
	Sigla *reqs[5];
	int qtdReqs;
}Prereqs;

Prereqs *buscaPrerequisitosPorMatricula(char *discDigitada, DiscAndReqs *discAndReqs){
	//printf("%s\n", discDigitada);
	Prereqs *prereqs;
	prereqs->qtdReqs = 0;
	int c = 0;
	
	for(int a=0; a<discAndReqs->totalPrereq; a++){
		//printf("%d\n",a);
		//printf("%s\n", discAndReqs->prerequisitos[a]->siglaMateria);
		if(strcmp(discDigitada, discAndReqs->prerequisitos[a]->siglaMateria) == 0){
			//printf("%s\n", discAndReqs->prerequisitos[a]->siglaRequisito);
			strcpy(prereqs->reqs[c]->sigla, discAndReqs->prerequisitos[a]->siglaRequisito);
			//printf("%s\n", prereqs->reqs[c]->sigla);
			prereqs->qtdReqs++;
			c++;
		}
	}
	
	return prereqs;
}
