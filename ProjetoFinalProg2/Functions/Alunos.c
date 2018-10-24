void gravaAlunosArquivo(Alunos *alunos){
    FILE *fp = fopen("Tables/Alunos.txt", "w");
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
