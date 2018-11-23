DiscAndReqs * carregaDiscAndReqs(){
    DiscAndReqs * discAndReqs = (DiscAndReqs *)malloc(sizeof(DiscAndReqs));
    
    int c1 = 0;
    int c2 = 0; 
    
	char sigla[6];
	char nome[100];
	int credito;
	
	char siglaMateria[6];
	char siglaRequisito[6];

    if(qtdDisciplinas > 0 || qtdPrereqs > 0){
    	FILE *fp = fopen(tableDisci, "r");
        while(c1<qtdDisciplinas){
    		fscanf(fp,"%s\n",sigla);
    		fscanf(fp,"%[^\n]",nome);
   			fscanf(fp,"%d\n",&credito);
           	discAndReqs->disciplinas[c1] = newDisciplina(sigla, nome, credito);
            c1++;
        }
        fclose(fp);
        
    	FILE *fpreq = fopen(tablePrereq, "r");
        while(c2<qtdPrereqs){
    		fscanf(fp,"%[^,],%s\n",siglaMateria,siglaRequisito);
    		
            discAndReqs->prerequisitos[c2] = newPrerequisito(siglaMateria, siglaRequisito);
            c2++;
        }
        fclose(fpreq);
        
        discAndReqs->totalDisci = c1;
        discAndReqs->totalPrereq = c2;
        
    }
    
    return discAndReqs;
}

