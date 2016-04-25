

#ifndef DEF_DOCUMENT
#define DEF_DOCUMENT

struct mot;
struct mot{
	int indice;
	int nombre_occurence;
	struct mot* suivant;
};


struct document;
struct document{
	int categorie;
	struct mot* vecteur;
	struct document* suivant;
};

/**
*	fonction qui créer un nouveau document de catégorie categorie et l'ajoute dans la liste des documents
*/
void creer_document(struct document* ensemble_doc,int categorie);

/**
*	fonction qui ajoute le mot d'indice indice et de nombre d'occurence nombe_occurence
*	dans le document doc
*/
void ajouter_mot(struct document* doc, int  indice, int nombre_occurence);

/**
*	fonction qui supprime le mot mot_a suppprimer de la liste
* 	libère la mémoire occupée
*	et renvoie le mot suivant
*/
struct mot* supprimer_mot(struct mot* mot_a_supprimer);

/**
*	fonction qui supprime le document doc_a_supprimer de la liste
*	libèle l'espace mémoire
*	et renvoie le document suivant
*/
struct document* supprimer_document(struct document* doc_a_supprimer);

#endif