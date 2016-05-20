#ifndef DEF_MULTINOMIAL
#define DEF_MULTINOMIAL
#include "document.h"
#include "modele.h"

//Reporter les occurences des termes dans doc au sein de listeProba, liste des
//probas d'occurence des termes dans les docs d'une meme classe
void modifTabPCkMultinomial(double* PCk, struct mot* doc);

//Calculer la probabilite empirique de la classe et construire listeProba avec les probabilites 
//d'occurence des termes pour un doc de classe
void determinerParametresMultinomial(double* tabPi,double** tabPC, struct document* ensemble_documents, int nbDocuments, int V);

//Calculer les parametres du modele de Bernoulli à partir des données d'entrée
struct modele* apprentissageMultinomial(int nbClasses, struct document* ensemble_documents, int nbDocuments, int V); 


#endif

