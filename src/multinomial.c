#include "multinomial.h"

void remplirListeProbaOcurence(struct probaOccurence* listeProba, struct document* doc, double* D){

  struct mot* courMot = doc->vecteur;
  struct probaOccurence* courProba = listeProba;

  while( courMot != NULL ){
    
    //Si la liste des probas est vide
    if (courProba == NULL){
      courProba = malloc(sizeof(struct probaOccurence));
      courProba->indice = courMot->indice;
      courProba->proba = 1;
      courProba->suivante = NULL;
    }
    else{
      //Si le terme a déjà été observe dans un document de la classe
      //On incremente l'occurence observée
      if( courProba->indice ==  courMot->indice ) (courProba->proba)++;
      else{
	//Si l'indice du terme est superieur à tous les indices des termes 
	//precedemment relevés, on ajoute en tete sa proba d'occurence
	if ( courProba->indice < courMot->indice ){
	  struct probaOccurence* nouvelleTete = malloc(sizeof(struct probaOccurence));
	  nouvelleTete->indice = courMot->indice;
	  nouvelleTete->proba = 1;
	  nouvelleTete->suivante = listeProba;
	  listeProba = nouvelleTete;
	  courProba = listeProba;
	}
	else{
	  //Si le terme n'a pas ete observé et que son indice est inferieur 
	  //à tous les autres observés, on l'insere en queue
	  if (courProba->suivante == NULL ){
	    struct probaOccurence* nouvelleQueue = malloc(sizeof(struct probaOccurence));
	    nouvelleQueue->indice = courMot->indice;
	    nouvelleQueue->proba = 1;
	    nouvelleQueue->suivante = NULL;
	    courProba->suivante = nouvelleQueue;
	    courProba = nouvelleQueue;
	  }
	  else{
	    //Si l'indice du terme est compris entre les indices des termes 
	    //courant et suivant, on l'insere entre les deux
	    if (courProba->suivante->indice < courMot->indice){
	      struct probaOccurence* nouvelleProba = malloc(sizeof(struct probaOccurence));
	    nouvelleProba->indice = courMot->indice;
	    nouvelleProba->proba = 1;
	    nouvelleProba->suivante = courProba->suivante;
	    courProba->suivante = nouvelleProba;
	    courProba = nouvelleProba;

	    }
	    
	    else{
	      //Sinon on va en queue ou jusqu'à se retrouver entre deux indices 
	      //encadrant l'indice actuel
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
		//l'indice suivant est egal à l'indice courant
		//On incremente l'occurence observee
		if (courProba->suivante->indice == courMot->indice){
		  courProba = courProba->suivante;
		  (courProba->proba)++;
		}
		else{
		  //sinon, encadrement strict et on insere
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
    }

    courMot = courMot->suivant;
    
  }
  
}


double determinerParametreClasse(int classe, struct probaOccurence* listeProba, struct document* ensemble_documents,int nbDocuments, double* D){

  //probabilite qu'un document soit de la classe etudiee
  double probaClasse = 0; 

  struct document* cour = ensemble_documents;

  //parcours de l'ensemble des documents
  while ( cour != NULL ){

    //si le document courant est de la classe à étudier
    if(cour->categorie == classe){
      //comptage du nombre de docs dans classe
      probaClasse++;
      //Modification de la liste des probabilites d'occurrence des 
      //mots dans la classe avec le contenu du doc courant
      remplirListeProbaOcurence(listeProba, cour, D);      
    }

    cour = cour->suivant;    
  }


  struct probaOccurence* courProba = listeProba;
  
  //reparcours de la liste des probabilites pour les calculer
  //avec le nombre de documents de docs de la classe  
  while (courProba != NULL){

    courProba->proba = (courProba->proba + 1)/(probaClasse + 2);
    courProba = courProba->suivante;
    
  }

  probaClasse /= nbDocuments;

  return probaClasse;

}


struct modeleMultinomial* determinerParametreModeleMultinomial(int nbClasses, struct document* ensemble_documents, int nbDocuments){

  //tableau de la distribution des classes
  double* tabProbaClasses = calloc(nbClasses,sizeof(double));
  double* Ds = calloc(nbClasses,sizeof(double));
  //tableau des probabilites d'occurence des termes pour chaque classe
  struct probaOccurence** tabProbaOccurences = malloc(nbClasses*sizeof(struct probaOccurence*));

  int i = 0;
  for( i = 0; i < nbClasses; i++ ){
    tabProbaOccurences[i] = NULL;
    //Calcul de la probabilite d'appartenannce à classe i
    //et construction liste probas d'occurence pour classe i
    tabProbaClasses[i] = determinerParametreClasse(i+1, tabProbaOccurences[i], ensemble_documents, nbDocuments, Ds);
  }

  struct modeleMultinomial* modele = malloc( sizeof(struct modeleMultinomial) );
  modele->tabProbaClasse = tabProbaClasses;
  modele->D = Ds;
  modele->tabProbaOccurence = tabProbaOccurences;

  return modele;

}
