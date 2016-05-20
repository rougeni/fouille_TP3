#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parsing.h"
#include "document.h"
#include "bernoulli.h"
#include "multinomial.h"
#include "rand.h"
#include <stdio.h>

int main (int argc, char **argv){

  //Creer l'ensemble de documents encodé dans le fichier
  struct document* ensemble_documents = parseBase("./../BaseReuters-29");

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

    tabDistribution[cour->categorie - 1]++;

    if ( cour->vecteur->indice > tailleVocabulaire ) tailleVocabulaire =  cour->vecteur->indice;

    if ( incrBaseTest < 18203 ){
        if  (tabIndiceRand[incrBaseTest] == incr){
            if (baseTest == NULL){
                baseTest = cour;
            }
            else {
                coursTest->suivant = cour;
            }
            coursTest = cour;
            cour = cour->suivant;
            coursTest->suivant = NULL;
            incrBaseTest++;
        }
    }
    
    else{
      if (baseEntrainement == NULL){
          baseEntrainement = cour;
      }
      else {
          coursEntrainement->suivant = cour;
      }
      coursEntrainement = cour;
      cour = cour->suivant;
      coursEntrainement->suivant = NULL;
    }

    incr++;

  }
  
  free(tabIndiceRand);
  
  /*
  printf("taille baseTest %d\n", incrBaseTest);
  
  printf("nb doc %d et taille voc %d\n", incr, tailleVocabulaire);
  
  for (i = 0; i < 29; i++){
    printf("nb docs classe %d : %d\n", i+1, tabDistribution[i]);
  } 
  
  
  coursEntrainement = baseEntrainement;
  
  incr = 0;
  while( coursEntrainement != NULL ){
      incr++;
      coursEntrainement = coursEntrainement->suivant;
  }
  
  printf("nb docs entrainement %d \n", incr);
  */
  
  
   
  struct modele* modeleBernoulli = apprentissageBernoulli(29, baseEntrainement, 52500);
  //struct modeleMultinomial* modeleMultinomial = apprentissageMultinomial(29, baseEntrainement, 52500, tailleVocabulaire);
  
  /*while( baseEntrainement != NULL ){
      baseEntrainement = supprimer_document(baseEntrainement);
  } */
  
  
  printf("%f", (modeleBernoulli->Pi)[1]);
  supprimerModele(modeleBernoulli);
  //printf("%f", modeleMultinomial->modeleM.Pi[1]);
  //printf("%d", testBernoulli(baseTest, tailleVocabulaire, 29, modeleBernoulli));
 /*
  while( baseTest != NULL ){
      baseTest = supprimer_document(baseTest);
  } */
 

}
