#include "bernoulli.h"
#include <stdlib.h>


void modifTabPCkMultinomial(double* PCk, struct mot* doc){

 struct mot* courMot = doc;
    
    while( courMot != NULL ){
        PCk[courMot->indice - 1] += courMot->nombre_occurence;
        courMot = courMot->suivant;    
    }
  
}



int* determinerParametresMultinomial(double* tabPi,double** tabPC, struct document* ensemble_documents, int nbDocuments, int V){

    struct document* docCour = ensemble_documents;
    int* denomPC = malloc(29*sizeof(int));
    
    while ( docCour != NULL ){
        
        tabPi[docCour->categorie - 1]++;
        modifTabPCkMultinomial(tabPC[docCour->categorie - 1], docCour->vecteur);
        
        docCour = docCour->suivant;
        
    }
    
    for (int k = 0; k < 29 ; k++){
        
        denomPC[k] = V;
        for(int i = 0; i < V; i++){
            denomPC[k] += tabPC[k][i]; 
        }
        

        for(int i = 0; i < V; i++){
            tabPC[k][i] = (tabPC[k][i] + 1)/denomPC[k]; 
        }
        
        tabPi[k] /= nbDocuments;
          
    } 
    
    return denomPC;

}


struct modeleMultinomial* apprentissageMultinomial(int nbClasses, struct document* ensemble_documents, int nbDocuments, int V){

  //tableau de la distribution des classes
  double* tabPi = malloc( nbClasses*sizeof(double) );
  //tableau des probabilites d'occurence des termes pour chaque classe
  double** tabPC = malloc(nbClasses*sizeof(double*));
  
  for(int k = 0; k < nbClasses; k++){
      tabPi[k] = 0;
      tabPC[k] = calloc(sizeof(double), V);
  }

  int* denomPC = determinerParametresMultinomial(tabPi, tabPC, ensemble_documents, nbDocuments, V);

  struct modeleMultinomial* modele = malloc( sizeof(struct modele) );
  modele->modeleM.Pi = tabPi;
  modele->modeleM.PC = tabPC;
  modele->denomPC = denomPC;

  return modele;

}







