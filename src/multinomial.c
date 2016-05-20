#include "bernoulli.h"
#include <stdlib.h>


void modifTabPCkMultinomial(struct probaOccurrence* PCk, struct mot* doc){

  struct mot* courMot = doc;
  struct probaOccurrence* courProba = PCk;

  while( courMot != NULL ){
    
    //Si la liste des probas est vide
    if (courProba == NULL){
      courProba = malloc(sizeof(struct probaOccurrence));
      courProba->indice = courMot->indice;
      courProba->proba = courMot->nombre_occurence;
      courProba->suivante = NULL;
      courProba->precedente = NULL;
    }
    else{
      //Si le terme a déjà été observe dans un document de la classe
      //On incremente l'occurence observée
      if( courProba->indice ==  courMot->indice )  courProba->proba += courMot->nombre_occurence;
      else{
	//Si l'indice du terme est superieur à tous les indices des termes 
	//precedemment relevés, on ajoute en tete sa proba d'occurence
	if ( courProba->indice < courMot->indice ){
	  struct probaOccurrence* nouvelleTete = malloc(sizeof(struct probaOccurrence));
	  nouvelleTete->indice = courMot->indice;
	  nouvelleTete->proba = courMot->nombre_occurence;
	  nouvelleTete->suivante = courProba;
	  nouvelleTete->precedente = courProba->precedente;
          if( courProba->precedente == NULL ){
              PCk = nouvelleTete;
          }
          else{
              courProba->precedente->suivante = nouvelleTete;
          }
          courProba->precedente = nouvelleTete;
	}
	else{
	  //Si le terme n'a pas ete observé et que son indice est inferieur 
	  //à tous les autres observés, on l'insere en queue
	  if (courProba->suivante == NULL ){
	    struct probaOccurrence* nouvelleQueue = malloc(sizeof(struct probaOccurrence));
	    nouvelleQueue->indice = courMot->indice;
	    nouvelleQueue->proba = courMot->nombre_occurence;
	    nouvelleQueue->suivante = NULL;
            nouvelleQueue->precedente = courProba;
	    courProba->suivante = nouvelleQueue;
	    courProba = nouvelleQueue;
	  }
	  else{
	    //Si l'indice du terme est compris entre les indices des termes 
	    //courant et suivant, on l'insere entre les deux
	    if (courProba->suivante->indice < courMot->indice){
	      struct probaOccurrence* nouvelleProba = malloc(sizeof(struct probaOccurrence));
                nouvelleProba->indice = courMot->indice;
                nouvelleProba->proba = courMot->nombre_occurence;
                nouvelleProba->suivante = courProba->suivante;
                nouvelleProba->precedente = courProba;
                courProba->suivante = nouvelleProba;
                courProba = nouvelleProba;
	    }
	    
	    else{
	      //Sinon on va en queue ou jusqu'à se retrouver entre deux indices 
	      //encadrant l'indice actuel
	      while( (courProba->suivante != NULL) && (courProba->suivante->indice > courMot->indice) ) {courProba = courProba->suivante;}
	      if (courProba->suivante == NULL){
		struct probaOccurrence* nouvelleQueue = malloc(sizeof(struct probaOccurrence));
		nouvelleQueue->indice = courMot->indice;
		nouvelleQueue->proba = courMot->nombre_occurence;
		nouvelleQueue->suivante = NULL;
                nouvelleQueue->precedente = courProba;
		courProba->suivante = nouvelleQueue;
		courProba = nouvelleQueue;
	      }
	      else{
		//l'indice suivant est egal à l'indice courant
		//On incremente l'occurence observee
		if (courProba->suivante->indice == courMot->indice){
		  courProba = courProba->suivante;
		  (courProba->proba) += courMot->nombre_occurence;
		}
		else{
		  //sinon, encadrement strict et on insere
		  struct probaOccurrence* nouvelleProba = malloc(sizeof(struct probaOccurrence));
		  nouvelleProba->indice = courMot->indice;
		  nouvelleProba->proba = courMot->nombre_occurence;
		  nouvelleProba->suivante = courProba->suivante;
                  nouvelleProba->precedente = courProba;
		  courProba->suivante = nouvelleProba;
		  courProba = nouvelleProba;
		}
	      }
	    }
	  }
	}
      }
    }

    courMot = courMot->suivant;
    
  }
  
}



int* determinerParametresMultinomial(double* tabPi,struct probaOccurrence** tabPC, struct document* ensemble_documents, int nbDocuments, int V){

    struct document* docCour = ensemble_documents;
    int* denomPC = malloc(29*sizeof(int));
    
    while ( docCour != NULL ){
        
        tabPi[docCour->categorie]++;
        modifTabPCkMultinomial(tabPC[docCour->categorie], docCour->vecteur);
        
        docCour = docCour->suivant;
        
    }
    
    struct probaOccurrence* probaCour = NULL;
    
    for (int k = 0; k < 29 ; k++){
        
        probaCour = tabPC[k];
        denomPC[k] = V;
        while(probaCour != NULL){
            denomPC[k] += probaCour->proba; 
            probaCour = probaCour->suivante;
        }
        
        probaCour = tabPC[k];
        while(probaCour != NULL){
            probaCour->proba = (probaCour->proba + 1)/denomPC[k]; 
            probaCour = probaCour->suivante;
        }
        
        tabPi[k] /= nbDocuments;
          
    } 
    
    return denomPC;

}


struct modeleMultinomial* apprentissageMultinomial(int nbClasses, struct document* ensemble_documents, int nbDocuments, int V){

  //tableau de la distribution des classes
  double* tabPi = malloc( nbClasses*sizeof(double) );
  //tableau des probabilites d'occurence des termes pour chaque classe
  struct probaOccurrence** tabPC = malloc(nbClasses*sizeof(struct probaOccurrence*));

  int* denomPC = determinerParametresMultinomial(tabPi, tabPC, ensemble_documents, nbDocuments, V);

  struct modeleMultinomial* modele = malloc( sizeof(struct modele) );
  modele->modeleM.Pi = tabPi;
  modele->modeleM.PC = tabPC;
  modele->denomPC = denomPC;

  return modele;

}







