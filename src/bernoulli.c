#include "bernoulli.h"
#include <stdlib.h>
#include <math.h>


void modifTabPCkBernoulli(struct probaOccurrence* PCk, struct mot* doc){

  struct mot* courMot = doc;
  struct probaOccurrence* courProba = PCk;

  while( courMot != NULL ){
    
    //Si la liste des probas est vide
    if (courProba == NULL){
      courProba = malloc(sizeof(struct probaOccurrence));
      courProba->indice = courMot->indice;
      courProba->proba = 1;
      courProba->suivante = NULL;
      courProba->precedente = NULL;
      PCk = courProba;
    }
    else{
      //Si le terme a déjà été observe dans un document de la classe
      //On incremente l'occurence observée
      if( courProba->indice ==  courMot->indice ) (courProba->proba)++;
      else{
	//Si l'indice du terme est superieur à tous les indices des termes 
	//precedemment relevés, on ajoute en tete sa proba d'occurence
	if ( courProba->indice < courMot->indice ){
	  struct probaOccurrence* nouvelleTete = malloc(sizeof(struct probaOccurrence));
	  nouvelleTete->indice = courMot->indice;
	  nouvelleTete->proba = 1;
	  nouvelleTete->suivante = courProba;
	  nouvelleTete->precedente = NULL;
          PCk = nouvelleTete;
          courProba = nouvelleTete;
	}
	else{
	  //Si le terme n'a pas ete observé et que son indice est inferieur 
	  //à tous les autres observés, on l'insere en queue
	  if (courProba->suivante == NULL ){
	    struct probaOccurrence* nouvelleQueue = malloc(sizeof(struct probaOccurrence));
	    nouvelleQueue->indice = courMot->indice;
	    nouvelleQueue->proba = 1;
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
                nouvelleProba->proba = 1;
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
		nouvelleQueue->proba = 1;
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
		  (courProba->proba)++;
		}
		else{
		  //sinon, encadrement strict et on insere
		  struct probaOccurrence* nouvelleProba = malloc(sizeof(struct probaOccurrence));
		  nouvelleProba->indice = courMot->indice;
		  nouvelleProba->proba = 1;
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



void determinerParametresBernoulli(double* tabPi,struct probaOccurrence** tabPC, struct document* ensemble_documents, int nbDocuments){

    struct document* docCour = ensemble_documents;
    
    while ( docCour != NULL ){
        
        tabPi[docCour->categorie]++;
        modifTabPCkBernoulli(tabPC[docCour->categorie], docCour->vecteur);
        
        docCour = docCour->suivant;
        
    }
    
    struct probaOccurrence* probaCour = NULL;
    
    for (int k = 0; k < 29 ; k++){
        
        probaCour = tabPC[k];
        int Nk = tabPi[k];
        while(probaCour != NULL){
            probaCour->proba = (probaCour->proba + 1)/(Nk + 2);
            probaCour = probaCour->suivante;
        }
        
        tabPi[k] /= nbDocuments;
          
    } 

}


struct modele* apprentissageBernoulli(int nbClasses, struct document* ensemble_documents, int nbDocuments){

  //tableau de la distribution des classes
  double* tabPi = malloc( nbClasses*sizeof(double) );
  //tableau des probabilites d'occurence des termes pour chaque classe
  struct probaOccurrence** tabPC = malloc(nbClasses*sizeof(struct probaOccurrence*));

  determinerParametresBernoulli(tabPi, tabPC, ensemble_documents, nbDocuments);

  struct modele* modele = malloc( sizeof(struct modele) );
  modele->Pi = tabPi;
  modele->PC = tabPC;

  return modele;

}


int testBernoulli(struct document* doc, int V, int nbClasses, struct modele* modeleApprentissage){
    
    double PiF;
    double PiFMax;
    int kMax = 1;
    
    for(int k = 0; k < nbClasses; k++){
        int i = V;
        PiF = log((modeleApprentissage->Pi)[k]);
        int Nk = 52500*(modeleApprentissage->Pi)[k];
        double probaDefaut = 1/(Nk + 2);
        struct probaOccurrence* probaCour = (modeleApprentissage->PC)[k];
        double probaI;
        struct mot* d = doc->vecteur;
        while (i > 0){
            
            if (probaCour->indice == i){
                probaI= probaCour->proba;
                probaCour = probaCour->suivante;
            }
            else  probaI = probaDefaut;
            
            if(d->indice == i){
                PiF += log(probaI);
                d = d->suivant;
            }
            else PiF += log(1 - probaI);
            
            i--;
        }
        
        if (k == 0){
            PiFMax = PiF;
        }
        else{
            if (PiFMax < PiF){
                PiFMax = PiF;
                kMax = k + 1;
            }
        }
        
        
    }
    
    return kMax;
    
}







