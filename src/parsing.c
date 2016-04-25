#include "parsing.h"
#include <stdlib.h>
#include <string.h>

void parseMot(struct document* doc,const char word[]) {
	char* wrd = malloc(sizeof(char)*strlen(word));
	int i = 0;
	int indice;
	int nbr_occur;
	strcpy(wrd,word);
	while (wrd[i] != ':') {
		i++;
	}
	wrd[i] = '\0';
	indice = atoi(wrd);
	nbr_occur = atoi(wrd+i+1);
	free(wrd);
	ajouter_mot(doc,indice,nbr_occur);
}
