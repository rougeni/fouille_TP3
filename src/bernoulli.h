#ifndef DEF_BERNOULLI
#define DEF_BERNOULLI
#include "document.h"
#include "modele.h"

//Calculer la probabilite empirique de la classe et construire listeProba avec les probabilites 
//d'occurence des termes pour un doc de classe
void determinerParametresBernoulli(double* tabPi,double** tabPC, struct document* ensemble_documents, int nbDocuments, int V);

//Calculer les parametres du modele de Bernoulli à partir des données d'entrée
struct modele* apprentissageBernoulli(int nbClasses, struct document* ensemble_documents, int nbDocuments, int V);

int testBernoulli(struct mot* doc, int V, int nbClasses, struct modele* modeleApprentissage, double** log1);


#endif
