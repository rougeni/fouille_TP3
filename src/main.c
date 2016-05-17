#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parsing.h"
#include "document.h"
#include "bernoulli.h"
#include "multinomial.h"
#include "rand.h"

int main (int argc, char **argv){

  //Creer l'ensemble de documents encodé dans le fichier
  struct document* ensemble_documents = parseBase("../BaseReuters-29");

  int tailleVocabulaire = 0;

  int i = 0;
  //tableau du nombre de documents par catégorie
  int tabDistribution[29];
  for (i = 0; i < 29; i++){
    tabDistribution[i] = 0;
  }

 
  //Pointeur vers document courant pour parcours de l'ensemble de documents
  struct document* cour = ensemble_documents;


  int* tabIndiceRand = tabRand(70703, 18203);
  //Base de test à constituer
  struct document* baseTest = NULL;
  struct document* coursTest = NULL;
  struct document* baseEntrainement = NULL;
  struct document* coursEntrainement = NULL;
  int incrBaseTest = 0;
  int incr = 0;

  while ( cour != NULL ){

    tabDistribution[cour->categorie]++;

    if ( cour->vecteur->indice > tailleVocabulaire ) tailleVocabulaire =  cour->vecteur->indice;

    if (tabIndiceRand[incrBaseTest] == incr){
      if (baseTest == NULL){
          baseTest = cour;
      }
      else {
          coursTest->suivant = cour;
      }
      coursTest = cour;
      incrBaseTest++;
    }
    else{
      if (baseEntrainement == NULL){
          baseEntrainement = cour;
      }
      else {
          coursEntrainement->suivant = cour;
      }
      coursEntrainement = cour;
    }

    cour = cour->suivant;

    incr++;

  }
    
    
  
    
    

}
