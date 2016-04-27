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
  //tableau de la distribution des classes
  double* tabProbaClasse;
  //tableau des probabilites d'occurence des termes pour chaque classe
  struct probaOccurence** tabProbaOccurence;
};

//Reporter les occurences des termes dans doc au sein de listeProba, liste des
//probas d'occurence des termes dans les docs d'une meme classe
void  remplirListeProbaOcurence(struct probaOccurence* listeProba, struct document* doc);

//Calculer la probabilite empirique de la classe et construire listeProba avec les probabilites 
//d'occurence des termes pour un doc de classe
double determinerParametreClasse(int classe, struct probaOccurence* listeProba, struct document* ensemble_documents, int nbDocuments);

//Calculer les parametres du modele de Bernoulli à partir des données d'entrée
struct modeleBernoulli* determinerParametreModeleBernoulli(int nbClasses, struct document* ensemble_documents, int nbDocuments); 


#endif
