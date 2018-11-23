Prereqs *buscaPrerequisitosPorSigla(char *discDigitada, DiscAndReqs *discAndReqs){
	//printf("%s\n", discDigitada);
	Prereqs *prereqs;
	prereqs->qtdReqs = 0;
	int c = 0;
	
	for(int a=0; a<discAndReqs->totalPrereq; a++){
		//printf("%d\n",a);
		//printf("%s\n", discAndReqs->prerequisitos[a]->siglaMateria);
		if(strcmp(discDigitada, discAndReqs->prerequisitos[a]->siglaMateria) == 0){
			if(strcmp(discAndReqs->prerequisitos[a]->siglaRequisito, "Livre") != 0){
				//printf("%s\n", discAndReqs->prerequisitos[a]->siglaRequisito);
				//printf("%s\n", discAndReqs->prerequisitos[a]->siglaRequisito);
				prereqs->reqs[c] = newSigla(discAndReqs->prerequisitos[a]->siglaRequisito);
				//printf("%s\n", prereqs->reqs[c]->sigla);
				prereqs->qtdReqs++;
				c++;
			}
		}
	}
	
	return prereqs;
}

int buscaSeJaCursouDisciplina(char *discDigitada, AllAlunosDisc *allAlunosDisc, int ra){
	int c = 0;
	
	for(int a=0; a<allAlunosDisc->total; a++){
		//printf("%d\n",a);
		//printf("%s\n", discAndReqs->prerequisitos[a]->siglaMateria);
		if(strcmp(discDigitada, allAlunosDisc->alunosDisciplinas[a]->sigla) == 0 && (allAlunosDisc->alunosDisciplinas[a]->ra == ra)){
			c = 1;
		}
	}
	
	if(c == 1){
		return 1;
	}else{
		return 0;	
	}
}
