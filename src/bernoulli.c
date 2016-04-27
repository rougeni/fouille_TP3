#include "bernoulli.h"
#include <stdlib.h>


void remplirListeProbaOcurence(struct probaOccurence* listeProba, struct document* doc){

  struct mot* courMot = doc->vecteur;
  struct probaOccurence* courProba = listeProba;

  while( courMot != NULL ){
    
    if (courProba == NULL){
      courProba = malloc(sizeof(struct probaOccurence));
      courProba->indice = courMot->indice;
      courProba->proba = 1;
      courProba->suivante = NULL;
    }
    else{
      if( courProba->indice ==  courMot->indice ) (courProba->proba)++;
      else{
	if ( courProba->indice < courMot->indice ){
	  struct probaOccurence* nouvelleTete = malloc(sizeof(struct probaOccurence));
	  nouvelleTete->indice = courMot->indice;
	  nouvelleTete->proba = 1;
	  nouvelleTete->suivante = listeProba;
	  listeProba = nouvelleTete;
	  courProba = listeProba;
	}
	else{
	  if (courProba->suivante == NULL ){
	    struct probaOccurence* nouvelleQueue = malloc(sizeof(struct probaOccurence));
	    nouvelleQueue->indice = courMot->indice;
	    nouvelleQueue->proba = 1;
	    nouvelleQueue->suivante = NULL;
	    courProba->suivante = nouvelleQueue;
	    courProba = nouvelleQueue;
	  }
	  else{
	    if (courProba->suivante->indice < courMot->indice){
	      struct probaOccurence* nouvelleProba = malloc(sizeof(struct probaOccurence));
	    nouvelleProba->indice = courMot->indice;
	    nouvelleProba->proba = 1;
	    nouvelleProba->suivante = courProba->suivante;
	    courProba->suivante = nouvelleProba;
	    courProba = nouvelleProba;

	    }
	    
	    else{
	      while( (courProba->suivante != NULL) && (courProba->suivante->indice > courMot->indice) ) {courProba = courProba->suivante;}
	      if (courProba->suivante == NULL){
		struct probaOccurence* nouvelleQueue = malloc(sizeof(struct probaOccurence));
		nouvelleQueue->indice = courMot->indice;
		nouvelleQueue->proba = 1;
		nouvelleQueue->suivante = NULL;
		courProba->suivante = nouvelleQueue;
		courProba = nouvelleQueue;
	      }
	      else{
		struct probaOccurence* nouvelleProba = malloc(sizeof(struct probaOccurence));
		nouvelleProba->indice = courMot->indice;
		nouvelleProba->proba = 1;
		nouvelleProba->suivante = courProba->suivante;
		courProba->suivante = nouvelleProba;
		courProba = nouvelleProba;
	      }
	    }
	  }
	}
      }
    }

    courMot = courMot->suivant;
    
  }
  
}


double determinerParametreClasse(int classe, struct probaOccurence* listeProba, struct document* ensemble_documents,int nbDocuments){

  double probaClasse = 0; 

  struct document* cour = ensemble_documents;

  while ( cour != NULL ){

    if(cour->categorie == classe){
      probaClasse++;
      remplirListeProbaOcurence(listeProba, cour);      
    }

    cour = cour->suivant;
    
  }


  struct probaOccurence* courProba = listeProba;
  
  while (courProba != NULL){

    courProba->proba = (courProba->proba + 1)/(probaClasse + 2);
    courProba = courProba->suivante;
    
  }

  probaClasse /= nbDocuments;

  return probaClasse;

}


struct modeleBernoulli* determinerParametreModeleBernoulli(int nbClasses, struct document* ensemble_documents, int nbDocuments){

  double* tabProbaClasses = malloc( nbClasses*sizeof(double) );
  struct probaOccurence** tabProbaOccurences = malloc(nbClasses*sizeof(struct probaOccurence*));
  int i = 0;
  for( i = 0; i < nbClasses; i++ ){
    tabProbaOccurences[i] = NULL;
    tabProbaClasses[i] = determinerParametreClasse(i+1, tabProbaOccurences[i], ensemble_documents, nbDocuments);
  }

  struct modeleBernoulli* modele = malloc( sizeof(struct modeleBernoulli) );
  modele->tabProbaClasse = tabProbaClasses;
  modele->tabProbaOccurence = tabProbaOccurences;

  return modele;

}







