#include "bernoulli.h"
#include <stdlib.h>
#include <math.h>


void modifTabPCkMultinomial(double* PCk, struct mot* doc){

 struct mot* courMot = doc;
    
    while( courMot != NULL ){
        PCk[courMot->indice - 1] += courMot->nombre_occurence;
        courMot = courMot->suivant;    
    }
  
}



void determinerParametresMultinomial(double* tabPi,double** tabPC, struct document* ensemble_documents, int nbDocuments, int V){

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
    
    
    free(denomPC);

}


struct modele* apprentissageMultinomial(int nbClasses, struct document* ensemble_documents, int nbDocuments, int V){

  //tableau de la distribution des classes
  double* tabPi = malloc( nbClasses*sizeof(double) );
  //tableau des probabilites d'occurence des termes pour chaque classe
  double** tabPC = malloc(nbClasses*sizeof(double*));
  
  for(int k = 0; k < nbClasses; k++){
      tabPi[k] = 0;
      tabPC[k] = calloc(sizeof(double), V);
  }

  determinerParametresMultinomial(tabPi, tabPC, ensemble_documents, nbDocuments, V);

  struct modele* modeleM = malloc( sizeof(struct modele) );
  modeleM->Pi = tabPi;
  modeleM->PC = tabPC;

  return modeleM;

}


int testMultinomial(struct document* doc, int nbClasses, struct modele* modeleApprentissage){
    
    double PiF;
    double PiFMax;
    int kMax = 1;
    
    for(int k = 0; k < nbClasses; k++){
        PiF = log((modeleApprentissage->Pi)[k]);
        struct mot* d = doc->vecteur;
        while (d != NULL){
            PiF += (d->nombre_occurence)*((modeleApprentissage->PC)[k][d->indice-1]);
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




