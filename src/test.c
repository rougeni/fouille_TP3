#include "parsing.h"
#include "document.h"
#include <stdio.h>


int main (int argc, char **argv){
	struct document test;
	parseMot(&test,"0:0");
	printf("Test 0:0 => %i:%i\n",test.vecteur[0].indice, test.vecteur[0].nombre_occurence);

	struct document *ensemble_doc = NULL;
	ensemble_doc = parseLine(ensemble_doc,"1 1:1 2:2 3:3");
	printf("Cat : %i\n",ensemble_doc->categorie);
	struct mot *ptr = ensemble_doc->vecteur;
	while (ptr != NULL) {
		printf(" %i:%i ",ptr->indice,ptr->nombre_occurence);
		ptr = ptr->suivant;
	}
	printf("\n");
	return 0;
}
