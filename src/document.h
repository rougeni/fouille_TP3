

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

void creer_document(struct document* ensemble_doc,int categorie);

void ajouter_mot(struct document* doc, int  indice, int nombre_occurence);

void supprimer_mot(struct mot* mot_a_supprimer);

void supprimer_document(struct document* doc_a_supprimer);

#endif