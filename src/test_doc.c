#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "document.h"

int main (int argc, char **argv){
	printf("\n test \n");

	/** ------------------------------------- Test de la fonction creer_document -----------------------------*/
	struct document * ensemble_doc = NULL;
	ensemble_doc = creer_document(ensemble_doc,1);
	creer_document(ensemble_doc,2);
	creer_document(ensemble_doc,1);

	/** ------------------------------------- Test de la fonction nombre_doc_par_classe -------------------*/
	int * tableau = nombre_doc_par_classe(ensemble_doc);
	for(int i = 0; i< 29; i ++){
		printf("tableau[%i]:%i\n",i,tableau[i]);
	}

	/** ------------------------------------- Test de la fonction ajouter_mot -----------------------------*/
	ajouter_mot(ensemble_doc,1,2);
	ajouter_mot(ensemble_doc,10,5);
	ajouter_mot(ensemble_doc,35,6);

	struct mot* courant = ensemble_doc->vecteur;
	while(courant != NULL){
		printf("%i : %i\n",courant->indice, courant->nombre_occurence);
		courant = courant->suivant;
	}

	ajouter_mot(ensemble_doc->suivant,2,2);
	ajouter_mot(ensemble_doc->suivant,12,5);
	ajouter_mot(ensemble_doc->suivant,124,6);

	ajouter_mot(ensemble_doc->suivant->suivant,6,2);
	ajouter_mot(ensemble_doc->suivant->suivant,345,5);
	ajouter_mot(ensemble_doc->suivant->suivant,522,6);

	/** -------------------------------------- Test de la fonction taille_voc ---------------------------*/
	int taille =  taille_voc(ensemble_doc);
	printf("taille du vocabulaire (522): %i\n",taille);

	/** ------------------------------------- test des focntions de suppressions ------------------------*/
	supprimer_document(ensemble_doc->suivant->suivant);
	taille =  taille_voc(ensemble_doc);
	printf("taille du vocabulaire (124): %i\n",taille);

	printf("\n fin du test \n");
	return 0;
}