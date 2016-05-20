#ifndef DEF_BERNOULLI
#define DEF_BERNOULLI
#include "document.h"
#include "modele.h"

//Reporter les occurences des termes dans doc au sein de listeProba, liste des
//probas d'occurence des termes dans les docs d'une meme classe
void modifTabPCkBernoulli(struct probaOccurrence* PCk, struct mot* doc);

//Calculer la probabilite empirique de la classe et construire listeProba avec les probabilites 
//d'occurence des termes pour un doc de classe
void determinerParametresBernoulli(double* tabPi,struct probaOccurrence** tabPC, struct document* ensemble_documents, int nbDocuments);

//Calculer les parametres du modele de Bernoulli à partir des données d'entrée
struct modele* apprentissageBernoulli(int nbClasses, struct document* ensemble_documents, int nbDocuments); 


#endif
