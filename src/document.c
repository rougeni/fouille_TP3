#include <stdio.h>
#include <stdlib.h>

#include "document.h"

void ajouter_mot(struct document* doc, int  indice, int nombre_occurence){
	struct mot* mot_a_ajouter = malloc(sizeof(struct mot));
	mot_a_ajouter->indice = indice;
	mot_a_ajouter->nombre_occurence = nombre_occurence;
	mot_a_ajouter->suivant = doc->vecteur;
	doc->vecteur = mot_a_ajouter;
}

void supprimer_mot(struct mot* mot_a_supprimer){
	free(mot_a_supprimer);
}