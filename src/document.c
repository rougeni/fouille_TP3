#include <stdio.h>
#include <stdlib.h>

#include "document.h"

void creer_document(struct document* ensemble_doc,int categorie){
	struct document* doc = malloc(sizeof(struct document));
	doc->categorie = categorie;
	doc->suivant = ensemble_doc->suivant;
	ensemble_doc->suivant = doc;
}

void ajouter_mot(struct document* doc, int  indice, int nombre_occurence){
	struct mot* mot_a_ajouter = malloc(sizeof(struct mot));
	mot_a_ajouter->indice = indice;
	mot_a_ajouter->nombre_occurence = nombre_occurence;
	mot_a_ajouter->suivant = doc->vecteur;
	doc->vecteur = mot_a_ajouter;
}

struct mot* supprimer_mot(struct mot* mot_a_supprimer){
	struct mot * suivant = mot_a_supprimer->suivant;
	free(mot_a_supprimer);
	return suivant;
}

struct document* supprimer_document(struct document* doc_a_supprimer){
	struct document * suivant = doc_a_supprimer->suivant;
	free(doc_a_supprimer);
	return suivant;
}