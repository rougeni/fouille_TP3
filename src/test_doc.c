#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "document.h"

int main (int argc, char **argv){
	printf("\n test \n");
	struct document * ensemble_doc = NULL;
	creer_document(ensemble_doc,1);
	creer_document(ensemble_doc,2);
	creer_document(ensemble_doc,1);
	int * tableau = nombre_doc_par_classe(ensemble_doc);
	for(int i = 0; i< 29; i ++){
		printf("tableau[%i]:%i\n",i,tableau[i]);
	}
	printf("\n fin du test \n");
	return 0;
}