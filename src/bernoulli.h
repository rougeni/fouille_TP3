#include "document.h"
#ifndef DEF_BERNOULLI
#define DEF_BERNOULLI

struct probaOccurence;
struct probaOccurence{
	int indice;
	double proba;
	struct probaOccurence* suivante;
};

struct modeleBernoulli;
struct modeleBernoulli{
  double* tabProbaClasse;
  struct probaOccurence** tabProbaOccurence;
};


void  remplirListeProbaOcurence(struct probaOccurence* listeProba, struct document* doc);

double determinerParametreClasse(int classe, struct probaOccurence* listeProba, struct document* ensemble_documents, int nbDocuments);

struct modeleBernoulli* determinerParametreModeleBernoulli(int nbClasses, struct document* ensemble_documents, int nbDocuments); 


#endif
