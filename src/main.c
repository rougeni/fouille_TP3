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
  //dernier doc courant de baseTest
  struct document* coursTest = NULL;
  //Base d'entrainement à constituer
  struct document* baseEntrainement = NULL;
  //dernier doc courant de baseEntrainement
  struct document* coursEntrainement = NULL;
  //nb de docs dans baseTest
  int incrBaseTest = 0;
  int incr = 0;

  //parcours de ensemble_document a separer entre 
  //baseTest et baseEntrainement
  while ( cour != NULL ){

    //Calcul de Nk
    tabDistribution[cour->categorie - 1]++;

    //Calcul de V
    if ( cour->vecteur->indice > tailleVocabulaire ) tailleVocabulaire =  cour->vecteur->indice;

    //S'il reste encore des elements à mettre dans baseTest
    if ( incrBaseTest < 18203 ){
        //Si le document courant doit etre dans baseTest
        if  (tabIndiceRand[incrBaseTest] == incr){
            //Si c'est le premier element
            if (baseTest == NULL){
                baseTest = cour;
            }
            else {
                coursTest->suivant = cour;
            }
            coursTest = cour;
            cour = cour->suivant;
            coursTest->suivant = NULL;
            //Il y a un document de plus dans baseTest
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
  
  
  //printf("taille baseTest %d\n", incrBaseTest);
  
  /*printf("nb doc %d et taille voc %d\n", incr, tailleVocabulaire);
  
  for (i = 0; i < 29; i++){
    printf("nb docs classe %d : %d\n", i+1, tabDistribution[i]);
  }*/ 
  
  
  coursEntrainement = baseTest;
  
  incr = 0;
  while( coursEntrainement != NULL ){
      incr++;
      coursEntrainement = coursEntrainement->suivant;
  }
  
  printf("nb docs test %d \n", incr);
  
  
  
   
  //struct modele* modeleBernoulli = apprentissageBernoulli(29, baseEntrainement, 52500, tailleVocabulaire);
  struct modele* modeleMultinomial = apprentissageMultinomial(29, baseEntrainement, 52500, tailleVocabulaire);
  
  /*
  while( baseEntrainement != NULL ){
      baseEntrainement = supprimer_document(baseEntrainement);
  }*/
  
  
  struct document* docCour = baseTest;
  double reussites = 0;
  int indiceDoc = 1;
  while(docCour != NULL){
    //int k = testBernoulli(docCour->vecteur, tailleVocabulaire, 29, modeleBernoulli);
    int k = testMultinomial(docCour->vecteur, modeleMultinomial);  
    if ( k  == docCour->categorie ){ reussites += 1;}
    docCour = docCour->suivant;
    indiceDoc++;
  }
  
  reussites /= 18203;
  
  /*while (docCour != NULL){
    if(testMultinomial(baseTest,29,modeleMultinomial) == docCour->categorie) reussites++;
    docCour = docCour->suivant;
  }*/
  
  printf("reussites %f\n", reussites);
  
  //supprimerModele(modeleBernoulli);
  //printf("%f", modeleMultinomial->modeleM.Pi[1]);
  //printf("%d", testBernoulli(baseTest, tailleVocabulaire, 29, modeleBernoulli));
 
  /*while( baseTest != NULL ){
      baseTest = supprimer_document(baseTest);
  }*/
 

}
