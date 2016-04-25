#include <stdio.h>
#include <stdlib.h>

#include "document.h"

struct document* creer_document(struct document* ensemble_doc,int categorie){
	struct document* doc = malloc(sizeof(struct document));
	doc->categorie = categorie;
	if(ensemble_doc == NULL){
		// ajout du premier document
		doc->suivant = NULL;
	} else {
		doc->suivant = ensemble_doc;
	}
	return doc;
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
	// il faut supprimer tous les mots de ce document
	struct mot * courant = doc_a_supprimer->vecteur;
	while (courant != NULL){
		courant = supprimer_mot(courant);
	}
	free(doc_a_supprimer);
	return suivant;
}

int* nombre_doc_par_classe(struct document * ensemble_doc){
	int *tableau = malloc(29*sizeof(int));
	// on parcours l'ensemble des documents et on note la catégorie de chacun
	struct document * courant = ensemble_doc;
	int categorie;
	while(courant != NULL){
		categorie = courant->categorie;
		tableau[categorie-1]++;
		courant = courant->suivant;
	}
	return tableau;
}

int taille_voc(struct document* ensemble_doc){
	struct document * courant = ensemble_doc;
	int voc = 0;
	while(courant != NULL){
		// pour chaque document, on regarde l'indice du premier mot de la liste qui est le dernier mot du fichier
		if (courant-> vecteur != NULL){
			int indice = courant->vecteur->indice;
			if (indice > voc){
				voc = indice;
			}
		}
		courant = courant->suivant;
	}
	return voc;
}