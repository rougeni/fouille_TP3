#include "parsing.h"
#include <stdlib.h>
#include <string.h>


//TO BE REMOVED
#include <stdio.h>

void parseMot(struct document* doc,const char word[]) {
	char* wrd = strdup(word);
	int i = 0;
	int indice;
	int nbr_occur;
	while (wrd[i] != ':') {
		i++;
	}
	wrd[i] = '\0';
	indice = atoi(wrd);
	nbr_occur = atoi(wrd+i+1);
	free(wrd);
	ajouter_mot(doc,indice,nbr_occur);
}

void parseLine(struct document* ens_doc, char line[]) {
	char *buf = NULL;
	char **bp = NULL;
	char *tok = NULL;
	int cat = -1;

	buf = strdup(line);
	bp = &buf;
	
	tok = strsep(bp, " ");
	cat = atoi(tok);
	
	ens_doc = creer_document(ens_doc,cat);
	
	while((tok = strsep(bp, " ")) != NULL){
		parseMot(ens_doc,tok);
	}
     
	free(buf);
}
