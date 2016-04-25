

#ifndef
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

#endif