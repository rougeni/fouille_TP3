#ifndef DEF_MULTINOMIAL
#define DEF_MULTINOMIAL
#include "document.h"
#include "modele.h"

//Calculer les parametres du modele de Bernoulli à partir des données d'entrée
struct modeleMultinomial* determinerParametreModeleMultinomial(int nbClasses, struct document* ensemble_documents, int nbDocuments);

#endif
